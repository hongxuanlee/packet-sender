#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct pseudoHeader
{
    u_int32_t  ip_src;
    u_int32_t  ip_dst;
    u_int8_t zero;   //always zero
    u_int8_t protocol;  //for tcp
    u_int16_t tcp_len;
};

int ip_match(u_int32_t addr1, u_int32_t addr2);
    
unsigned short csum(unsigned short *ptr,int nbytes);

unsigned short ipCheckSum(struct iphdr* iph, struct tcphdr* tcph, char* data, int size);

unsigned short tcpCheckSum(struct iphdr* iph, struct tcphdr* tcph, char* data, int size);

