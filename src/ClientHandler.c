/*
 * =====================================================================================
 *
 *       Filename:  ClientHandler.c
 *
 *    Description:  Implementation of ClientHandler
 *
 *        Version:  1.0
 *        Created:  22/11/2017 10:43:50 μμ
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
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "HeaderHandler.h"
void *handle_client(void *clientfd_p){
    printf("Client Handler started");
    int client_fd = *((int *)clientfd_p);
    char buff[1024];
    int buff_size;
    int send_bytes;
    memset(buff, 0, sizeof(buff));
    while((buff_size = recv(client_fd, &buff, sizeof(buff), MSG_DONTWAIT)) > 0){
        buff[buff_size] = '\0';
        get_request(buff);
        printf("Data received");
    }
    if (buff_size < 0){
        if (errno == EAGAIN || errno == EWOULDBLOCK){
            fprintf(stderr, "No more data to read\n");
        }
        else
            perror("Receive error");
    }
    string response = generate_response_header();
    size_t response_size = strlen(response);
    send_bytes = send(client_fd, response, ++response_size, 0);
    if (send_bytes < 0){
        perror("Send Error");
    }
    else{
        printf("Bytes send: %d\n", send_bytes);
    }
    close(client_fd);
    pthread_exit(NULL);
}


