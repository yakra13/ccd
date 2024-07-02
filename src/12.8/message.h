#pragma once

#include <netinet/in.h>

#define MESSAGE_HEADER_SIZE 2
#define MESSAGE_STDOUT 0x41 //A

typedef struct message
{
    uint8_t id;
    uint8_t data_length;
    char* data;
} Message;

void handle_message(Message*, struct sockaddr_in*);
void message_to_buffer(char* buffer, Message* message);
void reset_message(Message*);