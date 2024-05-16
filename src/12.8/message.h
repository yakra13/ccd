#pragma once

#define MESSAGE_STDOUT 0x4142 //AB

typedef struct message
{
    uint16_t id;
    uint8_t data_length;
    char* data;
} Message;
