/*                                                                   */
/*                                John Hartmann 11 Jun 2011 15:53:50 */

/*********************************************************************/
/* Change activity:                                                  */
/*11 Jun 2011  New header file.                                      */
/*********************************************************************/


#if !defined(_JPH_IN_H)
   #define _JPH_IN_H

typedef struct in_addr {
    unsigned int s_addr;  // load with inet_aton()
} in_addr_t;

struct sockaddr {
    unsigned short    sa_family;    // address family, AF_xxx
    char              sa_data[14];  // 14 bytes of protocol address
};

struct sockaddr_in {
    short            sin_family;   // e.g. AF_INET
    unsigned short   sin_port;     // e.g. htons(3490)
    struct in_addr   sin_addr;     // see struct in_addr, below
    char             sin_zero[8];  // zero this if you want to
};

#endif
