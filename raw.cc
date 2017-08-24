#include "raw.h"

namespace sender{

    using namespace std;

    int sendRawPacket(int sork, const char* ip, int port, const  char *buffer, int length) {
        struct sockaddr_in dest;
        dest.sin_family = AF_INET;
        dest.sin_port = htons(port);
        dest.sin_addr.s_addr = inet_addr(ip);
        if (sendto (sork, buffer, length,  0, (struct sockaddr *) &dest, sizeof (dest)) < 0)
        {
            cerr << "sendto failed" << endl;
            return -1;
        }
        else
        {
            return length;
        }
    }

    int createRawSocket() {
        int s = socket (AF_INET, SOCK_RAW, IPPROTO_TCP);
        if(s == -1)
        {
            cerr << "Failed to create socket" << endl;
        }
        int one = 1;
        const int *val = &one;
        struct sockaddr_in serverProxy;
        serverProxy.sin_family = AF_INET;
        serverProxy.sin_addr.s_addr = INADDR_ANY;
        struct sockaddr saddr;
        if (setsockopt (s, IPPROTO_IP, IP_HDRINCL, val, sizeof (one)) < 0)
        {
            cerr << "Error setting IP_HDRINCL" << endl;
        }
        return s;
    }
}

