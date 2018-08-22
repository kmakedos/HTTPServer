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

#include "ContentHandler.h"
void *handle_client(void *clientfd_p){
    printf("Client Handler started\n");
    int client_fd = *((int *)clientfd_p);
    char buff[1024];
    int buff_size;
    int send_bytes;
    string path;
    memset(buff, 0, sizeof(buff));
    while((buff_size = recv(client_fd, &buff, sizeof(buff), MSG_DONTWAIT)) > 0){
        buff[buff_size] = '\0';
        path = read_request(buff);
        printf("Path asked: %s\n", path);
        printf("\nAll Data received\n");
    }
    if (buff_size < 0){
        if (errno == EAGAIN || errno == EWOULDBLOCK){
            fprintf(stderr, "No more data to read\n");
        }
        else
            perror("Receive error");
    }
    string response = get_main_content(path);
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


