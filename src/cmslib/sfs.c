/* Driver for SFS files and other CMS files                          */
/*                                John Hartmann 20 Jun 2011 11:21:33 */

/*********************************************************************/
/* Change activity:                                                  */
/*20 Jun 2011  New module.                                           */
/*********************************************************************/

#include "cmspriv.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>
#include <time.h>

#include <cmsbase.h>
#include <csl.h>
#include <exsbuff.h>
#include <adt.h>

#if !defined(DEBUG)
   #define DEBUG 0
#endif

struct fnarg
{
   int fidlen;
   int optlen;
   char filepool[9];                  /* File pool SFS:              */
   char filespace[9];                 /* JOHN.                       */
   char fid[256];                     /* File name &c                */
   char opt[256];                     /* Keywords                    */
   /* Stuff returned by dmsvaldt                                     */
   char dir[153];                     /* Resolved directory path     */
   char slop;                         /* For null                    */
   int alen;                          /* Length of above             */
   char type;             /* '1' file mode, '2' SFS dir, '3' namedef */
   char mode, moden;                  /* Mode letter and number      */
   unsigned int nomode:1;
};

/*********************************************************************/
/* The unix access modes do not map easily to the SFS ones.          */
/*********************************************************************/

enum intent
{
   int_read,                          /* O_RDONLY -> READ            */
   int_update,                        /* O_RDWR -> WRITE             */
   int_create,                        /* O_WRONLY O_CREAT -> NEW     */
   int_replace,                       /* O_WRONLY O_TRUNC -> REPLACE */
};

static const char * const sfsint[] =
{ "READ", "WRITE", "NEW", "REPLACE" };

/* Forward declarations:                                             */
static int devflush(FILE * f);
static int devclose(FILE * f);
static int devstat(FILE * f, struct stat * st);
static ssize_t devread(FILE * f);
static ssize_t devwrite(FILE * f);
static int devextend(FILE * f, size_t add);
static int devopen(FILE * f, const char * name, int oflags, const char * mde);
/* End of forward declarations.                                      */

struct __access _sfsacc=
{
   .type = "SFS",
   open: devopen,
   read: devread,
   write: devwrite,
   extend: devextend,
   flush: devflush,
   close: devclose,
   fstat: devstat,
};

static int
devextend(FILE * f, size_t add)
{
   return _devextend(f, f->byteptr + add);
}

/*********************************************************************/
/* File name contains a dot.  Scan file handle as follows:           */
/*                                                                   */
/* A  leading slash indicates a fully qualified SFS or minidisk file */
/* name, e.g.,                                                       */
/*                                                                   */
/*    /sfs:john/some.file                                            */
/*    /a/load.map                                                    */
/*                                                                   */
/* A leading tilde is expanded as the file space:                    */
/*                                                                   */
/*    ~/some.file                                                    */
/*    ~johnpoul/some.file                                            */
/*                                                                   */
/* A  bare  file  name/type  is  resolved  to any mode or mode a for */
/* write.                                                            */
/*********************************************************************/

static int
devopen(FILE * f, const char * name, int oflags, const char * mde)
{
   struct fnarg fna = {0};
   const char * t;
   const char * s=name;
   int len;
   int fnftlen;
   int rv, rsn;
   struct exsbuff exs;
   struct exsbuff * pexs;
   int exsl=sizeof(exs);
   int nofile = 0;                    /* assume file exists          */
   int zero = 0;                      /* For SFS plist               */
   static const char blanks[10] = "          ";
   static const char noc[] = "NOCOMMIT";
   static const int nocl = sizeof(noc) - 1;
   const char * mode = mde;
   enum intent intent;

   #if DEBUG
   __WERROR("Opening %s for mode %s", name, mode);
   #endif
   switch (name[0])
   {
      case '/':
         s += strspn(s, "/");
         t=strpbrk(s, "/:");
         if (!t)
            return _seterr(EINVAL, EINVAL, _einv_rsn_bad_fn_onesl,
               "Leading slash, but no further slash or colon.", name);
         len = t - s;
         if ('/' == *t)              /* Mode letter and maybe number */
         {
            if (2 < len)
               return _seterr(EINVAL, EINVAL, _einv_rsn_bad_fn_modelong,
                  "File mode longer than two characters.", name);
            fna.mode = toupper(0xff & s[0]);
            fna.moden = 2 == len ? s[1] : ' ';
            s = t + 1;
            break;
         }
         /* ':' File pool                                            */
         if (8 < len)
            return _seterr(EINVAL, EINVAL, _einv_rsn_bad_fn_fplong,
               "File pool name longer than 8 characters.", name);
         memcpy(fna.filepool, s, len);
         s = t;
         /* Fall through                                             */
      case '~':                       /* File space                  */
         t = strchr(++s, '/');
         if (!t)
            return _seterr(EINVAL, EINVAL, _einv_rsn_bad_fn_fpfsunterm,
               "File space name not terminated with forward slash (/).", name);
         len = t - s;
         if (len)
         {
            if (8<len)
               return _seterr(EINVAL, EINVAL, _einv_rsn_bad_fn_fslong,
                  "File space name longer than 8 characters.", name);
            memcpy(fna.filespace, s, len);
         }
         for (;;)                     /* Look for directory levels   */
         {
            s += strspn(s, "/");
            t = strchr(s, '/');
            if (!t) break;
            if (fna.alen) fna.dir[fna.alen++] = '.';
            len = t - s;
            if (sizeof(fna.dir) < fna.alen + len)
               return _seterr(EINVAL, EINVAL, _einv_rsn_bad_fn_fslong,
                  "Directory path too long.", name);
            memcpy(fna.dir + fna.alen, s, len);
            fna.alen += len;
            s=t + 1;
         }
         break;
      case '.':
         return _seterr(EINVAL, EINVAL, _einv_rsn_bad_fn_leaddot,
            "File name omitted.", name);
      default:
         fna.mode = (O_RDONLY & f->oflags) ? '*' : 'A';
   }

   t = strchr(s, '.');
   if (!t)
      return _seterr(EINVAL, EINVAL, _einv_rsn_bad_fn_noft,
         "File type omitted.", name);
   len = t - s;
   fnftlen = strlen(s);
   if (17 < fnftlen)
      return _seterr(EINVAL, EINVAL, _einv_rsn_bad_fn_fnftlong,
         "File name and type too long.", name);

   memcpy(fna.fid, s, fnftlen);
   fna.fid[len] = ' ';
   fna.fidlen = fnftlen;

   fna.fid[fna.fidlen++] = ' ';
   #define PSF(x...) fna.fidlen += sprintf(fna.fid + fna.fidlen, x)
   if (fna.filepool[0])
   {
      PSF("%s:", fna.filepool);
      if (!fna.filespace[0])
         return _seterr(EINVAL, EINVAL, _einv_rsn_bad_fn_fsmissing,
            "File space not specified.", name);
   }
   if (fna.alen) PSF("%s.%s", fna.filespace, fna.dir);
   else PSF("%c", fna.mode);
   if (fna.moden) PSF(" %c", fna.moden);
#if DEBUG
   __WERROR("%d >%s<", fna.fidlen, fna.fid);
#endif

   #undef PDF

/*********************************************************************/
/* Now  look  for the file.  If user wants caseless, he will have to */
/* do the uppercasing.  We in turn make no noise.                    */
/*********************************************************************/

   exs.exstype = 0;                   /* Assume not old              */
   rsn = 0;
   nofile = 0;
   tocsl(8, "DMSEXIST", &rv, &rsn, fna.fid, &fna.fidlen,
      &exs, &exsl, noc, &nocl);
   if (rv)
   {
      if (90220 == rsn) nofile = 1;
      else
      {
         char bfr[256];

         sprintf(bfr, "DMSEXIST reason %d file '%.*s'",
            rsn, fna.fidlen, fna.fid);
         return _seterr(EINVAL, EINVAL, _einv_rsn_bad_dmsexist,
            "CMS error locating file", bfr);
      }
   }
   else
   {
      #define M(x, y) f->x = exs.exsf ## y
      M(recform, recf);
      M(lrecl, recl);
      M(numrecs, recs);
      M(numblks, blks);
      #undef M
   }

/*********************************************************************/
/* Figure operation intent and set the keyword accordingly.          */
/*********************************************************************/

   if (nofile)
   {
      if (O_RDONLY & f->oflags) return ENOENT;
      intent = int_create;    /* If it ain't there, surely we create */
   }
   else
   {
      if (O_EXCL & f->oflags) return EEXISTS;
      if (O_RDONLY & f->oflags) intent = int_read;
      else if (O_TRUNC & f->oflags) intent = int_replace;
      else intent = int_update;
   }

   #define POP(x...) fna.optlen += sprintf(fna.opt + fna.optlen, x)

   POP("%s", sfsint[intent]);         /* Intent                      */
   #if DEBUG
   __WERROR("%d %s", fna.optlen, fna.opt);
   #endif

/*********************************************************************/
/* Process remaining part of mode string.                            */
/*                                                                   */
/* It  may  be  a  comma  and  lrecl=nnn, and SFS open options which */
/* should  not  include  new/read/replace, as we construct that word */
/* from the standard type.                                           */
/*********************************************************************/

   s = mode;

   while (s && *s)
   {
      if (0==strncasecmp(s, "lrecl=", 6))
      {
         int got=0;
         int lrecl;

         sscanf(s+6, "%d %n", &lrecl, &got);
         if (0==got)
            return _seterr(EINVAL, EINVAL, _einv_rsn_bad_lrecl,
               "Record length missing.", s);
         if (nofile) f->lrecl = lrecl;
         else
         s += 6 + got;
      }
      else if (0==strncasecmp(s, "recfm=", 6))
      {
         char recfm = toupper(0xff & s[6]);

         if ('F' != recfm && 'V' != recfm)
            return _seterr(EINVAL, EINVAL, _einv_rsn_bad_recfm,
               "Record format not valid.", s);
         if (!nofile && recfm != f->recform)
         {
            char bfr[2] = {f->recform};

            return _seterr(EINVAL, EINVAL, _einv_rsn_recfm_diff,
               "Record format not same as existing file.", bfr);
         }
         if (!(O_RDONLY & f->oflags)) POP(" %c", recfm);
         s += 7;
      }
      else
         return _seterr(EINVAL, EINVAL, _einv_rsn_bad_mode,
            "Unrecognised mode string.", s);

      if (*s && ',' != *s++)
         return _seterr(EINVAL, EINVAL, _einv_rsn_bad_mode_del,
            "Comma expected in mode string.", s);
   }

   /* Supply defaults if create                                      */
   if (int_create == intent)
   {
      if (!f->recform)
      {
         f->recform = 'V';
         POP(" %c", f->recform);
      }
      if (!f->lrecl)
      {
         /* Setting  the LRECL for V files is for the write function */
         /* to know when to cut a record; SFS will ignore the record */
         /* length?                                                  */
         if ('F' == f->recform) f->lrecl = 80;
         else if (O_BINARY & f->oflags) f->lrecl = 255;
      }
   }

   if (sizeof(fna.opt) - fna.optlen <= len)
      return _seterr(EINVAL, EINVAL, _einv_rsn_long_opt,
         "Option string too long.", s);

#if DEBUG
   __WERROR("fd %d mode '%s' options %d '%-*.*s' open flag %x",
      f->fd, mde, fna.optlen, fna.optlen, fna.optlen, fna.opt, f->oflags);
#endif
   #undef POP

/*********************************************************************/
/* And finally.                                                      */
/*********************************************************************/

   tocsl(15, "DMSOPEN ", &rv, &rsn, fna.fid, &fna.fidlen,
      fna.opt, &fna.optlen, f->token,
      &zero,                          /* Work unit                   */
      &zero,                          /* Wu error                    */
      &zero,                          /* Wu error length             */
      &zero,                          /* User data                   */
      &zero,                          /* User data length            */
      blanks,                         /* Create date                 */
      blanks,                         /* Create time                 */
      &f->lrecl                       /* Explicit record length      */
      );
   switch (rv)
   {
      case 0:
         break;
      case 4:
         break;
      case 8:
         switch (rsn)
         {
            case 90310:
               __sayf("fd %d %s bad keyword in list '%s'", f->fd, name, fna.opt);
               break;
            default:
               goto error;
         }
         return EINVAL;
      default:
error:
         __sayf("DMSOPEN fd %d rc=%d reason=%d.", f->fd, rv, rsn);
         return EINVAL;
   }

   if (!fna.mode) f->blksize = 0x1000;
   else
   {
      if (0) __sayf("FIXME " __FILE__ ".%d", __LINE__);
   }

   pexs = f->accwork = malloc(sizeof(struct exsbuff));
   if (!f) return ENOMEM;
   *pexs = exs;

   return 0;
}

/*********************************************************************/
/* Read a record from the underlying file.                           */
/*********************************************************************/

static ssize_t
devread(FILE * f)
{
   int one = 1;
   int rdpt;                          /* SFS does not want size_t    */

   if (f->numrecs <= f->readpointer)
   {
      f->eofInd = 1;
      return 0;
   }

   if (!f->buffer && _allocbuf(f, f->lrecl)) return 1;

   rdpt = f->readpointer++;
   tocsl(8, "DMSREAD ", &f->sfsrc, &f->sfsreason, f->token,
      &one, &f->lrecl,
      f->buffer, &f->buffersize, &f->hiwater, &rdpt);
   if (f->sfsrc)
   {
      f->errorInd = 1;
      __WERROR("SFS read record %zd rc %d reason %d", f->readpointer,
         f->sfsrc, f->sfsreason);
   }
   f->byteptr = 0;
   return 0;
}

/*********************************************************************/
/* Write a line to the underlying file                               */
/*********************************************************************/

static ssize_t
devwrite(FILE * f)
{
   int one=1;

   if (0 == f->byteptr)
   {
      if (O_BINARY & f->oflags) return 0;
      f->buffer[0] = ' ';
      f->byteptr = 1;
   }

   f->writepointer++;
   tocsl(7, "DMSWRITE ", &f->sfsrc, &f->sfsreason, f->token,
      &one, &f->byteptr, f->buffer, &f->byteptr);
   if (4 >= f->sfsrc) return 0;

   switch (f->sfsreason)
   {
      case 10000:
         __sayf("File descriptor %d intent not write.", f->fd);
         break;
      default:
         __sayf("DMSWRITE fd %d, rc=%d reason=%d.",
            f->fd, f->sfsrc, f->sfsreason);
   }
   f->errorInd = 1;
   return 0;
}

static int
devflush(FILE * f)
{
   return 0;
}

static int
devclose(FILE * f)
{
   int rv, rsn;
   static const char commit[]="COMMIT";
   int clen=strlen(commit);
   struct exsbuff * xb = f->accwork;

   if (xb) free(xb);
   tocsl(5, "DMSCLOSE", &rv, &rsn, f->token, commit, &clen);
   return rv ? -1 : 0;
}

static int
devstat(FILE * f, struct stat * st)
{
   struct exsbuff * xb = f->accwork;
   struct adt * ap;
   static unsigned char zeros[3];

   if (!xb)
   {
      __WERROR("accwork not there\n");
      return (errno = ENOENT), -1;
   }

   switch (f->recform)
   {
      case 0:
      case 'F':
         st->st_size = f->numrecs * (f->lrecl +1);
         break;
      case 'V':
         if (!f->numblks) break;
         if (!f->blksize)             /* Unknown minidisk            */
         {
            ap = __adtlkp(&xb -> exsfrfm);
            if (ap) f->blksize = ap -> adtdbsiz;
         }
         st->st_size = f->numblks * f->blksize;
   }

   st->st_mode = S_IFREG;
   st->st_blksize = f->blksize;
   st->st_blocks = f->numblks;
   if (xb->exsfdrxd) st->st_atime = __pkts2t(xb->exsfdrxd, zeros);
   if (xb->exsfdcxd) st->st_mtime = __pkts2t(xb->exsfdcxd, xb->exsftlcd);
   if (xb->exsfcdxd) st->st_ctime = __pkts2t(xb->exsfcdxd, xb->exsfctmd);
   return 0;
}
