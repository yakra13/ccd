/*8.2 Demonstrate skill in creating and using a circularly linked list that accepts any data type
### Objectives

- [x] Removing selected items from the circularly linked list
- [x] Creating a circularly linked list with n number of items
- [x] Navigating through a circularly linked list
- [x] Finding the first occurrence of an item in a circularly linked list
- [x] Sorting the circularly linked list alphanumerically using a function pointer
- [x] Destroying a circularly linked list
- [x] Inserting an item into a specific location in a circularly linked list
- [x] Removing all items from the circularly linked list
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "circular_link_list.h"

// typedef void (*sort_func)(struct circularLinkedList*);

// typedef enum {
//     CHAR_NODE,
//     INT_NODE,
//     FLOAT_NODE,
//     DOUBLE_NODE
// } NODE_TYPE;

// typedef struct node
// {
//     struct node* next_node;
//     void* data;
//     NODE_TYPE type;
// } Node;

// typedef struct circularLinkedList
// {
//     Node* current_node;
//     size_t length;
//     Node* (*AddNode)(struct circularLinkedList*, void*, NODE_TYPE);
//     Node* (*FindNode)(struct circularLinkedList*, void*);
//     Node* (*NextNode)(struct circularLinkedList*);
//     void (*FreeCurrentNode)(struct circularLinkedList*);
//     void (*FreeAllNodes)(struct circularLinkedList*);
//     bool (*InsertNodeAfter)(struct circularLinkedList*, void*, void*, NODE_TYPE);
//     bool (*InsertNodeBefore)(struct circularLinkedList*, void*, void*, NODE_TYPE);
//     void (*Sort)(struct circularLinkedList*, sort_func);
    
// } CircularLinkedList;

// CircularLinkedList* CreateCircularLinkList();
// Node* AddNode(CircularLinkedList*, void*, NODE_TYPE);
// Node* RemoveCurrentNode(CircularLinkedList*);
// Node* FindNode(CircularLinkedList*, void*);
// Node* NextNode(CircularLinkedList*);
// void FreeCurrentNode(CircularLinkedList*);
// void FreeAllNodes(CircularLinkedList*);
// void PrintNodes(CircularLinkedList*);
// bool InsertNodeAfter(CircularLinkedList*, void*, void*, NODE_TYPE);
// bool InsertNodeBefore(CircularLinkedList*, void*, void*, NODE_TYPE);
// void FreeList(CircularLinkedList*);
// void AlphanumericSort(CircularLinkedList*);
// void SortList(CircularLinkedList* list, sort_func f);

int main(void)
{
    printf("Create circular list.\n");

    CircularLinkedList* cll = CreateCircularLinkList();
    
    int* x = (int*)malloc(sizeof(int));
    *x = 5;
    float* y = (float*)malloc(sizeof(float));
    *y = 6.5f;
    char* z = (char*)malloc(sizeof(char));
    *z = 'z';
    double* w = (double*)malloc(sizeof(double));
    *w = 1.23456789;
    float* t = (float*)malloc(sizeof(float));
    *t = 69.96f;

    cll->AddNode(cll, x, INT_NODE);
    cll->AddNode(cll, y, FLOAT_NODE);
    cll->AddNode(cll, z, CHAR_NODE);

    PrintNodes(cll);
    
    printf("Find the char node.\n");
    cll->FindNode(cll, z);
    printf("Node (chr) = %c\n", *(char*)(cll->current_node->data));

    printf("Remove char node.\n");
    cll->FreeCurrentNode(cll);
    PrintNodes(cll);

    printf("Insert node after the int.\n");
    cll->InsertNodeAfter(cll, x, w, DOUBLE_NODE);
    PrintNodes(cll);

    printf("Insert node before the int.\n");
    cll->InsertNodeBefore(cll, x, t, FLOAT_NODE);
    PrintNodes(cll);

    printf("Empty the list.\n");
    cll->FreeAllNodes(cll);
    PrintNodes(cll);

    FreeList(cll);

    printf("Create alphanumeric list.\n");
    CircularLinkedList* sortList = CreateCircularLinkList();

    for (size_t i = 0; i < 35; i++)
    {
        //48 - 57
        //97 - 122
        char* c = (char*)malloc(sizeof(char));
        // printf("address : %p\n", c);
        *c = 48 + i;
        if (*c >= 58 && *c <= 96) { *c += 40; }

        sortList->AddNode(sortList, c, CHAR_NODE);
    }

    PrintNodes(sortList);

    printf("Sort list\n");
    sortList->Sort(sortList, AlphanumericSort);
    //Move to the 'beginning' of the list as the sort lands you on the last item
    sortList->NextNode(sortList);
    printf("Print sorted list\n");
    PrintNodes(sortList);
}

CircularLinkedList* CreateCircularLinkList()
{
    CircularLinkedList* c = (CircularLinkedList*)malloc(sizeof(CircularLinkedList));
    c->current_node = NULL;
    c->length = 0;
    c->AddNode = AddNode;
    c->FindNode = FindNode;
    c->NextNode = NextNode;
    c->FreeCurrentNode = FreeCurrentNode;
    c->FreeAllNodes = FreeAllNodes;
    c->InsertNodeAfter = InsertNodeAfter;
    c->InsertNodeBefore = InsertNodeBefore;
    // c->RemoveCurrentNode = RemoveCurrentNode;
    c->Sort = SortList;
    return c;
}

//- [ ] Creating a circularly linked list with n number of items
Node* AddNode(CircularLinkedList* list, void* data, NODE_TYPE type)
{
    //Create a new node with provided data
    Node* n = (Node*)malloc(sizeof(Node));
    n->next_node = NULL;
    n->data = data;
    n->type = type;

    //If the list is empty add the node and point the next ndoe to itself
    if(!list->current_node)
    {
        list->current_node = n;
        n->next_node = n;
    }
    else
    {
        //Insert the new node as the next node and point the new node
        //to the old next node
        Node* on = list->current_node->next_node;
        list->current_node->next_node = n;
        n->next_node = on;
    }

    list->length++;

    return n;
}

//- [ ] Finding the first occurrence of an item in a circularly linked list
Node* FindNode(CircularLinkedList* list, void* data, NODE_TYPE type)
{
    Node* n = list->current_node;
    do
    {
        if (list->current_node->data == data)
        {
            return list->current_node;
        }
        
    } while (list->NextNode(list) != n);
    
    return NULL;
}

//- [ ] Navigating through a circularly linked list
Node* NextNode(CircularLinkedList* list)
{
    list->current_node = list->current_node->next_node;
    return list->current_node;
}

//- [ ] Removing selected items from the circularly linked list
void FreeCurrentNode(CircularLinkedList* list)
{
    Node* cur = list->current_node;
    Node* n = list->NextNode(list);

    if (list->length == 1)
    {
        list->current_node = NULL;
    }
    else
    {
        while (list->current_node->next_node != cur)
        {
            list->NextNode(list);
        }

        list->current_node->next_node = n;
    }

    free(cur->data);
    free(cur);

    list->length--;
}

//- [ ] Removing all items from the circularly linked list
void FreeAllNodes(CircularLinkedList* list)
{
    while (list->current_node != NULL)
    {
        FreeCurrentNode(list);
    }
}

void PrintNodes(CircularLinkedList* list)
{
    if (list->current_node == NULL)
    {
        if (list->length == 0)
        {
            printf("List is empty.\n");
            return;
        }

        printf("Error: current node is null but length is %d.\n", (int)list->length);
    }
    else if (list->length == 0)
    {
        printf("length is zero\n");
        return;
    }

    for (int i = 0; i < (int)list->length; i++)
    {
        switch (list->current_node->type)
        {
            case CHAR_NODE:
                printf("Node %d (chr) = %c\n", i, *(char*)(list->current_node->data));
                break;
            case INT_NODE:
                printf("Node %d (int) = %d\n", i, *(int*)(list->current_node->data));
                break;
            case FLOAT_NODE:
                printf("Node %d (flt) = %f\n", i, *(float*)(list->current_node->data));
                break;
            case DOUBLE_NODE:
                printf("Node %d (dbl) = %lf\n", i, *(double*)(list->current_node->data));
                break;
            default:
                printf("Unsupported node type.\n");
                continue;
        }

        list->NextNode(list);
    }

    printf("Finished printing list.\n");
}

//- [ ] Destroying a circularly linked list
void FreeList(CircularLinkedList* list)
{
    list->FreeAllNodes(list);
    free(list);
}

//- [ ] Inserting an item into a specific location in a circularly linked list
bool InsertNodeAfter(CircularLinkedList* list, void* find_data, void* new_data, NODE_TYPE type)
{
    if(list->FindNode(list, find_data) == NULL)
        return false;

    list->AddNode(list, new_data, type);

    return true;
}

//- [ ] Inserting an item into a specific location in a circularly linked list
bool InsertNodeBefore(CircularLinkedList* list, void* find_data, void* new_data, NODE_TYPE type)
{
    Node* n = list->FindNode(list, find_data);
    
    if (n == NULL)
        return false;

    do
    {
       list->NextNode(list);
    } while(n != list->current_node->next_node);

    list->AddNode(list, new_data, type);

    return true;
}

void SortList(CircularLinkedList* list, sort_func f)
{
    printf("Sorting the list.\n");
    f(list);
}

// - [ ] Sorting the circularly linked list alphanumerically using a function pointer
void AlphanumericSort(CircularLinkedList* list)
{
    CircularLinkedList* newList = CreateCircularLinkList();

    Node* lowest;
    
    while (list->length > 0)
    {
        //Find the next lowest
        lowest = list->current_node;
        for (size_t i = 0; i < list->length - 1; i++)
        {
            list->NextNode(list);

            if (*(char*)list->current_node->data > *(char*)lowest->data)
            {
                lowest = list->current_node;
            }
        }

        //copy the lowest node
        char* data = (char*)malloc(sizeof(char));
        memcpy(data, lowest->data, sizeof(char));
        newList->AddNode(newList, data, CHAR_NODE);
        //remove the original
        list->current_node = lowest;
        list->FreeCurrentNode(list);
    }

    list->length = newList->length;
    list->current_node = newList->current_node;
    newList->current_node = NULL;

    free(newList);
    printf("Done sorting\n");
}
