#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "function.h"

Node* Address(Node* dummy_head, int x) {
    Node *cur = dummy_head;
    for(int i = 0; i < x; i++) {
        cur = cur->next;
    }
    return cur;
}

Node* ReadOneList() {
    Node *new = (Node*) malloc(sizeof(Node));
    scanf("%d", &new->size);
    getchar();
    new->next = NULL;
    new->data = (int*) malloc(sizeof(int) * new->size);
    for(int i = 0; i < new->size; i++) {
        scanf(" %d", &new->data[i]);
    }
    return new;
}

void PrintList(Node* dummy_head) {
    Node *cur = dummy_head->next;
    while(cur != NULL) {
        for(int i = 0; i < cur->size; i++) {
            if(i != cur->size-1) {
                printf("%d ", cur->data[i]);
            }else {
                printf("%d", cur->data[i]);
            }
        }
        printf("\n");
        cur = cur->next;
    }
}

void Merge(Node* dummy_head, int x, int y) {
    //Concatenate arrays
    Node *node_x = Address(dummy_head, x);
    Node *node_y = Address(dummy_head, y);
    int new_size = node_x->size + node_y->size;
    int *new_array = (int*) malloc(sizeof(int) * new_size);
    for(int i = 0; i < node_y->size; i++) {
        new_array[i] = node_y->data[i];
    }
    for(int i = 0; i < node_x->size; i++) {
        new_array[node_y->size+i] = node_x->data[i];
    }
    free(node_y->data);
    node_y->data = new_array;
    node_y->size = new_size;

    //Delete Node x
    Node *prev = Address(dummy_head, x-1);
    prev->next = node_x->next;
    free(node_x);
}

void Cut(Node* dummy_head, int x, int y) {
    //Create a new Node after Node x
    Node *node_x = Address(dummy_head, x);
    Node *new_node = (Node*) malloc(sizeof(Node));

    //Create a new array for x
    int *new_array = (int*) malloc(sizeof(int) * y);
    for(int i = 0; i < y; i++) {
        new_array[i] = node_x->data[i];
    }

    //Create a new array for new Node
    new_node->size = node_x->size - y;
    new_node->data = (int*) malloc(sizeof(int) * new_node->size);
    for(int i = 0; i < new_node->size; i++) {
        new_node->data[i] = node_x->data[y+i];
    }

    //Link and Free
    free(node_x->data);
    node_x->size = y;
    node_x->data = new_array;
    new_node->next = node_x->next;
    node_x->next = new_node;
}

/*
4 3
4: 1 2 3 4
2: 8 7
2: 5 6
1: 9
Merge 4 2
Cut 1 2
Cut 3 1
*/