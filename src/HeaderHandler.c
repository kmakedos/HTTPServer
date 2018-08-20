/*
 * =====================================================================================
 *
 *       Filename:  HeaderHandler.c
 *
 *    Description:  Implementation of Headers
 *
 *        Version:  1.0
 *        Created:  28/11/2017 12:01:14 πμ
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
#include <string.h>
#include "HeaderHandler.h"


string generate_response_header(){
    string response_head = "HTTP/1.0 200 OK                              \n"
            "Server: SimpleHTTP/0.6 Python/2.7.14                        \n"
            "Date: Sun, 03 Dec 2017 23:56:32 GMT                         \n"
            "Content-type: text/html; charset=UTF-8                      ";
    string content_length = "Content-Length:";
    string response_bottom = "\n                                         \n"
            "<html><head></head><body>                                   \n"
            "<h2>Welcome to a brave new world</h2>                      \n"
            "</body></html>";
    size_t size = strlen(response_head) + strlen(content_length) + 7 + strlen(response_bottom);
    string response = malloc(sizeof(size));
    sprintf(response, "%s\n%s %d\n%s", response_head, content_length, size, response_bottom);
    printf("Response generated: %s\n", response);
    return  response;

}


void get_request(string line){
    /*
     * TODO:  this is very silly way to cast structs onto buffer and cast away info from them
     * A better way would be to create
     * 1. A XOR function for checking standard/default commands and headers (GET, PUT, POST, HTTP/1.0)
     * 2. A stack with a linked list to save all arbitrary data while checking them for validity
     * better way found! A function using standard library strtok and similar functions to split a big stream
     * using line delimeters \n and then whitespace delimeters. So this function will fill a map with key values !!
     */
    string comm_part;
    string token = strtok(line, "\n");
    while (token != NULL){
        printf("%s\n", token);
        token = strtok(NULL, "\n");
    }
}
void get_request_header(string request){
    printf("%s", request);
}
