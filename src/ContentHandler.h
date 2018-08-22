#ifndef HEADERHANDLER_H
#define HEADERHANDLER_H
#include "Common.h"

/*
 * Here we define the basic protocol Headers
 */

/*
 * Request Header
 * Format:
 * COMMAND[<5 chars] PATH[<256 chars] PROTOCOL[<9 Chars]
 * COMMANDS EXAMPLE: GET, PUT, POST
 * PATHS EXAMPLE: /, /root/, /index.html
 * PROTOCOLS EXAMPLE: HTTP/1.0, HTTP/1.1, HTTP/2.0
 */



//string commands[HTTP_COMMANDS] = {"GET", "PUT", "POST"};
//string protocols[PROTOCOL_NUMS] = {"HTTP/1.0", "HTTP/1.1", "HTTP/2.0"};


void get_request(string line);
string generate_response_header();
void get_request_header(string request);
#endif
