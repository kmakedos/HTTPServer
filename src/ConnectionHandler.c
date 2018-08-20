/*
 * =====================================================================================
 *
 *       Filename:  ConnectionHandler.c
 *
 *    Description:  Implementation of ConnectionHandlers 
 *
 *        Version:  1.0
 *        Created:  22/11/2017 11:00:13 μμ
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kostas Makedos (KM), kostas.makedos@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <signal.h>
#include <pthread.h>
#include "Common.h"
#include "ConnectionHandler.h"
#include "ClientHandler.h"
#define MAX_CONN 10

int listener(string service_name, string service_port){
    printf("Core Server Starting...\n");
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1){
        perror("Sigaction error");
        exit(EXIT_FAILURE);
    }

    struct addrinfo *listening_addrs, *addr_p, hints;
    struct sockaddr_in *remote;
    struct in_addr *addr;
    int server_fd;
    char ip_addr[INET6_ADDRSTRLEN];
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    int rc = getaddrinfo(service_name, service_port, &hints, &listening_addrs);
    if (rc != 0){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rc));
        return -1;
    }
    for (addr_p = listening_addrs; addr_p != NULL; addr_p = addr_p->ai_next){
        if ((server_fd = socket(addr_p->ai_family, addr_p->ai_socktype, addr_p->ai_protocol))  == -1 ){
            perror("server: socket");
            continue;
        }
        int ok = 1;
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &ok, sizeof(int)) < 0) {
            perror("setsockopt");
            return -1;
        }
        if (bind(server_fd, addr_p->ai_addr, addr_p->ai_addrlen) == -1){
            close(server_fd);
            perror("server: bind");
            continue;
        }
        break;
    }
    freeaddrinfo(listening_addrs);
    if (addr_p == NULL){
        fprintf(stderr, "server: failed to bind\n");
        return -1;
    }

    if (listen(server_fd, MAX_CONN) == -1){
        perror("Listen error");
        return -1;
    }
    return server_fd;

}


void *acceptor(void* server_ptr){
    size_t server_fd = *((size_t *) server_ptr);
    socklen_t sock_size;
    struct sockaddr_storage client_addr;
    int client_fd;
    int number_clients = 0;
    pthread_t threadpool[10];
    size_t thread_used = 0;
    while(1){
        sock_size = sizeof(client_addr);
        client_fd = accept(server_fd, (struct sockaddr *) &client_addr, &sock_size);
        number_clients++;
        printf("%d connected\n", number_clients);
        if (client_fd == -1){
            exit(EXIT_FAILURE);
        }
        else{
            if (thread_used < 10){
                pthread_create(&threadpool[++thread_used], NULL, (void*) &handle_client, (void *) &client_fd);
                pthread_detach(threadpool[thread_used]);
                printf("Starting thread %ld with client_fd %d\n", thread_used, client_fd);
            }
            else{
                fprintf(stderr, "Could not create any more threads\n");
                close(client_fd);
            }
        }
    }
    close(server_fd);
}


