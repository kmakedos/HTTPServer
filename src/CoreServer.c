/*
 * =====================================================================================
 *
 *       Filename:  CoreServer.c
 *
 *    Description:  Core Server routines implementation 
 *
 *        Version:  1.0
 *        Created:  14/11/2017 11:06:44 μμ
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
#include <sys/wait.h>
#include <pthread.h>
#include "Common.h"
#include "ConnectionHandler.h"
#include "CoreServer.h"

void coreserver(string service_name, string service_port){
    int server_fd;    
    pthread_t acceptor_thread;
    if ((server_fd = listener(service_name, service_port)) == -1){
        fprintf(stderr, "Error initializing server\n");
        exit(EXIT_FAILURE);
    }
    pthread_create(&acceptor_thread, NULL, acceptor, (void*) &server_fd);
    pthread_join(acceptor_thread, NULL);
}

