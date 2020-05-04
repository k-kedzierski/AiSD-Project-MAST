//
//  node.c
//  AiSD_Project_3
//
//  Created by Kacper Kędzierski on 01/05/2020.
//  Copyright © 2020 Kacper Kędzierski. All rights reserved.
//

#include "node.h"

// ===
// Functions definitions
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

int_fast32_t node_count_children( node_t* parent ) {
    int_fast32_t    return_value = 0;
    node_t*         current = parent->child;
    
    while(current != NULL) {
        return_value++;
        current = current->sibling;
    }
    
    return return_value;
}
