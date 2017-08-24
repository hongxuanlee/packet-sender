#ifndef RAW_H 
#define RAW_H 

#include <iostream> 
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <string.h> //memset
#include <arpa/inet.h>
#include <sys/socket.h>

namespace sender {
   int sendRawPacket(int sork, const char* ip, int port, const char *buffer, int length); 
   int createRawSocket(); 
}

#endif


