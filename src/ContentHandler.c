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
#include "ContentHandler.h"


string generate_response_header() {
    string response_head = "HTTP/1.0 200 OK                              \n"
                           "Server: SimpleHTTP/0.6 Python/2.7.14                        \n"
                           "Date: Sun, 03 Dec 2017 23:56:32 GMT                         \n"
                           "Content-type: text/html; charset=UTF-8                      ";
    return response_head;
}

string get_main_content(string path){
    string content_length = "Content-Length:";
    string response_head = generate_response_header();
    FILE *f = fopen("../tst/index.html", "r");
    if (f == NULL){
        perror(("fopen"));
        exit(EXIT_FAILURE);
    }else{
        printf("File opened\n");
    }
    string response_bottom = "";
    string line = NULL;
    ssize_t nread;
    size_t n;
    while ((nread = getline(&line, &n, f)) != -1){
        response_bottom = concat(response_bottom, line);
    }
    printf("Response bottom %s\n", response_bottom);
    printf("Response bottom size %d\n", strlen(response_bottom));

    size_t size = strlen(response_head) + strlen(content_length) + 7 + strlen(response_bottom);
    printf("Response  size %d\n", size);
    string response = malloc(sizeof(size));
    sprintf(response, "%s\n%s %d\n%s", response_head, content_length, size, response_bottom);
    printf("Response generated: %s\n", response);
    return response;
}





string read_request(string buffer){
    /*
     * TODO:  this is very silly way to cast structs onto buffer and cast away info from them
     * A better way would be to create
     * 1. A XOR function for checking standard/default commands and headers (GET, PUT, POST, HTTP/1.0)
     * 2. A stack with a linked list to save all arbitrary data while checking them for validity
     * better way found! A function using standard library strtok and similar functions to split a big stream
     * using line delimeters \n and then whitespace delimeters. So this function will fill a map with key values !!
     */
    string path;
    size_t get_found = 0;
    string line = strtok(buffer, "\n");
    printf("::%s\n", line);
    string word = strtok(line, " ");
    if (strcmp(word, "GET") == 0){
        get_found = 1;
    }
    while (word != NULL){
        printf("Word: %s\n", word);
        word = strtok(NULL, " ");
        if (get_found == 1){
            return word;
        }
    }

    while (line != NULL){
        line = strtok(NULL, "\n");
        string word = strtok(line, " ");
        while (word != NULL){
            printf("Word: %s\n", word);
            word = strtok(NULL, " ");
      }

    }
    return "/";
}
void get_request_header(string request){
    printf("REQUEST HEADER: %s", request);
}
