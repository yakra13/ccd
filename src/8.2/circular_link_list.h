#pragma once

typedef void (*sort_func)(struct circularLinkedList*);

typedef enum {
    CHAR_NODE,
    INT_NODE,
    FLOAT_NODE,
    DOUBLE_NODE
} NODE_TYPE;

typedef struct node
{
    struct node* next_node;
    void* data;
    NODE_TYPE type;
} Node;

typedef struct circularLinkedList
{
    Node* current_node;
    size_t length;
    Node* (*AddNode)(struct circularLinkedList*, void*, NODE_TYPE);
    Node* (*FindNode)(struct circularLinkedList*, void*);
    Node* (*NextNode)(struct circularLinkedList*);
    void (*FreeCurrentNode)(struct circularLinkedList*);
    void (*FreeAllNodes)(struct circularLinkedList*);
    bool (*InsertNodeAfter)(struct circularLinkedList*, void*, void*, NODE_TYPE);
    bool (*InsertNodeBefore)(struct circularLinkedList*, void*, void*, NODE_TYPE);
    void (*Sort)(struct circularLinkedList*, sort_func);
    
} CircularLinkedList;

CircularLinkedList* CreateCircularLinkList();
Node* AddNode(CircularLinkedList*, void*, NODE_TYPE);
Node* RemoveCurrentNode(CircularLinkedList*);
Node* FindNode(CircularLinkedList*, void*);
Node* NextNode(CircularLinkedList*);
void FreeCurrentNode(CircularLinkedList*);
void FreeAllNodes(CircularLinkedList*);
void PrintNodes(CircularLinkedList*);
bool InsertNodeAfter(CircularLinkedList*, void*, void*, NODE_TYPE);
bool InsertNodeBefore(CircularLinkedList*, void*, void*, NODE_TYPE);
void FreeList(CircularLinkedList*);
void AlphanumericSort(CircularLinkedList*);
void SortList(CircularLinkedList* list, sort_func f);
