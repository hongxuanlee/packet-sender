#include "utils.h"

namespace sender {
    unsigned short csum(unsigned short *ptr,int nbytes) 
    {
        register long sum;
        unsigned short oddbyte;

        sum=0;
        while(nbytes>1) {
            sum+=*ptr++;
            nbytes-=2;
        }
        if(nbytes==1) {
            oddbyte=0;
            *((unsigned char*)&oddbyte)=*(unsigned char*)ptr;
            sum+=oddbyte;
        }

        sum = (sum>>16)+(sum & 0xffff);
        sum = sum + (sum>>16);

        return(short)~sum;
    }

    unsigned short ipCheckSum(struct iphdr* iph, struct tcphdr* tcph, char* data, int size)
    {
        iph -> check = 0;
        unsigned int ip_len = iph -> ihl * 4;
        unsigned int tcp_len = tcph -> doff * 4;
        char pseudoData[65536];
        memset(pseudoData, 0, 65536);
        memcpy(pseudoData, data, 20);
        return csum((unsigned short *)pseudoData, 20);
    }

    unsigned short tcpCheckSum(struct iphdr* iph, struct tcphdr* tcph, char* data, int size)
    {
        tcph -> check = 0;
        struct pseudoHeader psd_header;
        psd_header.ip_src = iph -> saddr;
        psd_header.ip_dst = iph -> daddr;
        psd_header.zero = 0;
        psd_header.protocol= IPPROTO_TCP;
        unsigned int tcp_len = tcph -> doff * 4;
        psd_header.tcp_len = htons(tcp_len + size);

        int psize = sizeof(struct pseudoHeader) + tcp_len + size;

        char* tcpBuf = malloc(psize);
        memcpy(tcpBuf, &psd_header, sizeof(struct pseudoHeader));
        memcpy(tcpBuf + sizeof(struct pseudoHeader), tcph, tcp_len + size);
        return csum((unsigned short *)tcpBuf, psize);
    }
}
