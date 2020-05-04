//
//  mast.h
//  AiSD_Project_3
//
//  Created by Kacper Kędzierski on 02/05/2020.
//  Copyright © 2020 Kacper Kędzierski. All rights reserved.
//
#pragma once
#ifndef mast_h
#define mast_h

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include "misc.h"
#include "node.h"
#include "tree.h"

#define MAST_LOOKUP(MAST_THD, I, J) ( (MAST_THD)->lookup[((I)*((MAST_THD)->t2->node_count))+(J)] )

#define MATCH_LOOKUP(MATCH, I, J) ( (MATCH)->match_matrix[((I)*((MATCH)->size[1]))+(J)] )

// ===
// Data Structures
// ===

typedef struct {
    int_fast32_t*   match_matrix;
    int_fast32_t    size[2];
    bool            swapped;
    int*           banned;
} match_t;

typedef struct {
    int_fast32_t*   lookup;
    int_fast32_t    lookup_size;
    tree_t*         t1;
    tree_t*         t2;
} mast_t;

// ===
// Functions declarations
// ===

match_t* match_init( int_fast32_t size_y, int_fast32_t size_x );

void match_opt_sum( match_t* match_thd, int_fast32_t current_row, int_fast32_t* return_value, int_fast32_t sum );

int_fast32_t match_eval_matrix( mast_t* mast_thd, node_t* node1, node_t* node2 );

mast_t* mast_init( tree_t* t1, tree_t* t2 );

void mast_free( mast_t* mast_thd );

void mast_eval_leaves( mast_t* mast_thd );

int_fast32_t mast_eval_nodes( mast_t* mast_thd, node_t* node1, node_t* node2 );

int_fast32_t mast_get_lookup( mast_t* mast_thd, node_t* node1, node_t* node2 );

int_fast32_t mast_get_opt( mast_t* mast_thd );

int_fast32_t mast( tree_t* t1, tree_t* t2 );

#endif /* mast_h */
