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
#include <stdbool.h>
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

void tree_label_inner_nodes( tree_t* tree ) {
    node_t*         current = tree->root;
    int_fast32_t    label = tree->leaf_count;
    
    // Labeling using indexes from leaf count up to node count - bottom-up approach
    while (label <= tree->node_count) {
        
        // Go to unlabeled child
        if( current->child != NULL && current->number == UNDEFINED) {
            current = current->child;
        }
        
        // Else, proceed to right and go to sibling
        else if( current->sibling != NULL ) {
            current = current->sibling;
        }
        
        // Else, go back to parent
        else {
            do
                current = current->parent;
            while (current->number != UNDEFINED);
            // ...and assign label
            current->number = label++;
        }
    }
}

tree_t* tree_init() {
    tree_t* return_tree = (tree_t*)malloc( sizeof(tree_t ));
    
    return_tree-> root = NULL;
    return_tree->leaf_count = 0;
    return_tree->node_count = 0;
    
    return return_tree;
}

void tree_get_definition( tree_t* tree ) {
    node_t* current = node_init(UNDEFINED);
    char    c;
    
    // Skip '\0' and '\n'
    fgetc(stdin);
    
    while (scanf("%c",&c)) {
        switch(c) {
            case ')':
                // Go back to parent
                current = current->parent;
                break;
            case '(':
                // Add child and move current position
                node_add_child(current);
                current = current->child;
                tree->node_count++;
                break;
            case ',':
                // Add sibling and move current position
                node_add_sibling(current);
                // Decrement leaf for 0...n-1 indexes
                if( current->number != UNDEFINED ) current->number--;
                current = current->sibling;
                tree->node_count++;
                break;
            case ';':
                tree->root = current;
                return;
            default:
                // Modify leaf value
                if( current->number == UNDEFINED ) {
                    current->number = (int)(c - 48);
                    tree->leaf_count++;
                }
                else {
                    current->number *= 10;
                    current->number += (int)(c - 48);
                }
                break;
        }
    }
}

tree_t* tree_scan() {
    tree_t* return_tree = tree_init();
    
    // Get tree definition
    tree_get_definition(return_tree);
    
    // Label inner nodes
    tree_label_inner_nodes(return_tree);
    
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
