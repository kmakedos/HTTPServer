/*
 * =====================================================================================
 *
 *       Filename:  Common.h
 *
 *    Description:  Common functions used to system
 *
 *        Version:  1.0
 *        Created:  15/11/2017 12:30:56 πμ
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kostas Makedos (KM), kostas.makedos@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef _COMMON_H
#define _COMMON_H
#include <sys/queue.h>

typedef char* string;

typedef struct entry{
    SLIST_ENTRY(entry) entries;
}entry;

typedef struct list{
    SLIST_HEAD(_list_head, entry) head;
}list;

string copy(string src);
string concat(string src1, string src2);

void rc_check(int rc);

void signal_handler(int signal); 

size_t equal_s(const string s, const string t);



#endif
