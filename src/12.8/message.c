#include "common.h"

void handle_message(Message* m, struct sockaddr_in* c)
{
    switch (m->id)
    {
        case MESSAGE_STDOUT:
            printf("%s:%d message=\"%s\"\n", inet_ntoa(c->sin_addr), ntohs(c->sin_port), m->data);
            break;        
        default:
            printf("ERROR: %s:%d sent invalid message id: %d ", inet_ntoa(c->sin_addr), ntohs(c->sin_port), m->id);
            printf("{message=\"%s\"}\n", m->data);
            break;
    }
}

void message_to_buffer(char* buffer, Message* message)
{
    memcpy(buffer, &message->id, sizeof(message->id));
    memcpy(buffer + 1, &message->data_length, sizeof(message->data_length));
    strncpy(buffer + 2, message->data, message->data_length);
}

void reset_message(Message* m)
{
    m->id = 0;
    m->data_length = 0;
    if (m->data != NULL)
        free(m->data);
    m->data = NULL;
}