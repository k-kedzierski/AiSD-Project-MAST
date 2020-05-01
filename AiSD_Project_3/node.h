//
//  node.h
//  AiSD_Project_3
//
//  Created by Kacper Kędzierski on 01/05/2020.
//  Copyright © 2020 Kacper Kędzierski. All rights reserved.
//

#ifndef node_h
#define node_h

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include "misc.h"

// ===
// Data Structures
// ===

typedef struct node {
    struct node*    parent;
    struct node*    child;
    struct node*    sibling;
    int_fast32_t    number;
} node_t;

// ===
// Functions declarations
// ===

node_t* node_init( int_fast32_t number );

void node_add_child( node_t* parent );

void node_add_sibling( node_t* child );

#endif /* node_h */
