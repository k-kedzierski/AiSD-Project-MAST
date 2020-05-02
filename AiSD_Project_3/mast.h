//
//  mast.h
//  AiSD_Project_3
//
//  Created by Kacper Kędzierski on 02/05/2020.
//  Copyright © 2020 Kacper Kędzierski. All rights reserved.
//

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

// ===
// Data Structures
// ===

typedef struct {
    int_fast32_t* lookup;
    int_fast32_t lookup_size;
    tree_t const* t1;
    tree_t const* t2;
} mast_t;

// ===
// Functions declarations
// ===

void _DEBUG_PRINT_LOOKUP( mast_t* mast_thd );

mast_t* mast_init( tree_t const* t1, tree_t const* t2 );

void mast_eval_leaves( mast_t* mast_thd );

int_fast32_t mast( tree_t const* t1, tree_t const* t2 );

#endif /* mast_h */
