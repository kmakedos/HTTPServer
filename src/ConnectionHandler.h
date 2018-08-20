#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H
#include "Common.h"
int listener(string service_name, string service_port);
void *acceptor(void* server_ptr);
#endif
