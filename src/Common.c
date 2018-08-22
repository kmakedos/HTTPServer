/*
 * =====================================================================================
 *
 *       Filename:  Common.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  17/11/2017 12:59:24 πμ
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
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include "Common.h"


string copy(string src){
    size_t src_size = strlen(src);
    string dest = NULL;
    if (src_size > 0){
        dest = (string) malloc(src_size + 1);
        strncpy(dest, src, src_size);
        dest[src_size] = '\0';
    }
    return dest;
}


string concat(string src1, string src2){
    size_t src1_size = strlen(src1);
    size_t src2_size = strlen(src2);
    if ((src1_size * src2_size) < 0){
        perror("Wrong string size in concat\n");
        return NULL;
    }
    size_t src_size = src1_size + src2_size + 1;
    string dest = (string) malloc(src_size);

    if (dest == NULL){
        perror("Could not allocate memory for concat");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i <src1_size; i++){
        dest[i] = src1[i];
    }
    for (int i = src1_size; i < src_size; i++){
        dest[i] = src2[i - src1_size];
    }
    dest[src_size] = '\0';
    return dest;
}

void rc_check(int rc){
    if (rc != 0){
        fprintf(stderr, "Error: %s\n", strerror(rc));
    }
}
void signal_handler(int signal){
    while (waitpid(-1, NULL, WNOHANG) > 0 );
}


size_t equal_s(const string s, const string t){
    size_t size = strlen(s);
    if (strlen(t) != size)
        return -1;
    for (size_t i = 0; i < size; i++){
        if (s[i] ^ t[i] != 0)
            return -1;
    }
    return 0;
}
