/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Main executable of C HTTP server
 *
 *        Version:  1.0
 *        Created:  13/11/2017 12:30:46 πμ
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kostas Makedos (KM), kostas.makedos@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include "Common.h"
#include "CoreServer.h"

int main(int argc, char *argv[]){
    string service_name = argc > 1 ? argv[1] : "0.0.0.0";
    string service_port = argc > 2 ? argv[2] : "8000";
    printf("Starting server at address: %s:%s\n", service_name, service_port);
    coreserver(service_name, service_port);
}
