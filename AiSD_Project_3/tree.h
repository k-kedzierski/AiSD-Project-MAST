//
//  tree.h
//  AiSD_Project_3
//
//  Created by Kacper Kędzierski on 01/05/2020.
//  Copyright © 2020 Kacper Kędzierski. All rights reserved.
//

#ifndef tree_h
#define tree_h

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include "misc.h"
#include "node.h"

// ===
// Data Structures
// ===

typedef struct {
    node_t*         root;
    node_t**        nodes;
    int_fast32_t    leaf_count;
    int_fast32_t    node_count;
} tree_t;

// ===
// Functions declarations
// ===

tree_t* tree_init( void );

void tree_free( tree_t* tree );

void tree_label_inner_nodes( tree_t* tree );

void tree_get_definition( tree_t* tree );

void tree_fill_nodes( tree_t* tree );

tree_t* tree_scan( void );

#endif /* tree_h */
