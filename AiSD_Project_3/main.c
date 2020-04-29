//
//  main.c
//  AiSD_Project_3
//
//  Created by Kacper Kędzierski on 29/04/2020.
//  Copyright © 2020 Kacper Kędzierski. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#define _DEBUG
#define UNDEFINED -1

// Debug stream
#ifdef _DEBUG
  #define _DEBUG_PRINTF(...) fprintf(stderr, __VA_ARGS__ );
#else
  #define _DEBUG_PRINTF(...)
#endif

// ===
// Data Structures
// ===

typedef struct node {
    struct node*    parent;
    struct node*    child;
    struct node*    sibling;
    int_fast32_t    number;
} node_t;

typedef struct {
    node_t*         root;
    node_t**        nodes;
    int_fast32_t    leaf_count;
    int_fast32_t    node_count;
} tree_t;


// ===
// Functions
// ===

node_t* node_init( int_fast32_t number ) {
    node_t* return_node = (node_t*)malloc( sizeof(node_t) );
    
    return_node->parent = NULL;
    return_node->child = NULL;
    return_node->sibling = NULL;
    return_node->number = number;
    
    return return_node;
}

void node_add_child( node_t* parent ) {
    node_t* child = node_init(UNDEFINED);
    child->parent = parent;
    parent->child = child;
}

void node_add_sibling( node_t* child ) {
    node_t* sibling = node_init(UNDEFINED);
    sibling->parent = child->parent;
    child->sibling = sibling;
}

tree_t* tree_init() {
    tree_t* return_tree = (tree_t*)malloc( sizeof(tree_t ));
    
    return_tree-> root = NULL;
    return_tree->leaf_count = 0;
    return_tree->node_count = 0;
    
    return return_tree;
}


tree_t* tree_scan() {
    tree_t* return_tree = tree_init();
    node_t* current = node_init(UNDEFINED);
    char    c;
    
    // Skip '\0' and '\n'
    fgetc(stdin);
    
    while(scanf("%c",&c)) {
        switch(c) {
            case ')':
                // Go back to parent
                current = current->parent;
                break;
            case '(':
                // Add child and move current position
                node_add_child(current);
                current = current->child;
                return_tree->node_count++;
                break;
            case ',':
                // Add sibling and move current position
                node_add_sibling(current);
                // Decrement leaf for 0...n-1 indexes
                if( current->number != UNDEFINED ) current->number--;
                current = current->sibling;
                return_tree->node_count++;
                break;
            case ';':
                return_tree->root = current;
                return return_tree;
            default:
                // Modify leaf value
                if( current->number == UNDEFINED ) {
                    current->number = (int)(c - 48);
                    return_tree->leaf_count++;
                }
                else {
                    current->number *= 10;
                    current->number += (int)(c - 48);
                }
                break;
        }
    }
    return return_tree;
}

// ===
// Main
// ===

int main() {
    
    _DEBUG_PRINTF("Debug stream initialized\n");
    
    int_fast32_t tree_set_size;
    
    // Initialize tree definitions
    scanf("%" SCNdFAST32, &tree_set_size);
    tree_t** tree_set = (tree_t**)malloc( tree_set_size * sizeof(tree_t) );
    for( int_fast32_t i = 0; i < tree_set_size; i++ ) {
        tree_set[i] = tree_scan();
    }
    return 0;
}
