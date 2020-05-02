//
//  mast.c
//  AiSD_Project_3
//
//  Created by Kacper Kędzierski on 02/05/2020.
//  Copyright © 2020 Kacper Kędzierski. All rights reserved.
//

#include "mast.h"

// ===
// Functions definitions
// ===

void _DEBUG_PRINT_LOOKUP( mast_t* mast_thd ) {
    int_fast32_t i, j;
    
    // Print lookup table - only when _DEBUG is defined in misc.h
    _DEBUG_PRINTF("╔════╦");
    for( i = 0; i < mast_thd->t2->node_count; i++ )
        _DEBUG_PRINTF("════");
    _DEBUG_PRINTF("═╗\n");
    
    _DEBUG_PRINTF("║    ║");
    // Label 1st dimension
    for( i = 0; i < mast_thd->t2->node_count; i++ )
        _DEBUG_PRINTF("%4d", i);
    _DEBUG_PRINTF(" ║\n");
    
    _DEBUG_PRINTF("╠════╬");
    for( i = 0; i < mast_thd->t2->node_count; i++ )
        _DEBUG_PRINTF("════");
    _DEBUG_PRINTF("═╣\n");
    
    for( i = 0; i < mast_thd->t1->node_count; i++ ) {
        // Label 2nd dimension
        _DEBUG_PRINTF("║" "%4d" "║", i);
        for( j = 0; j < mast_thd->t2->node_count; j++ ) {
            _DEBUG_PRINTF("%4d", MAST_LOOKUP(mast_thd, i, j));
        }
        _DEBUG_PRINTF(" ║\n");
        if( i == mast_thd->t1->node_count - 1 ) break;
        _DEBUG_PRINTF("║    ║" "%*c" " ║\n", 4 * mast_thd->t2->node_count, ' ');
    }
    
    _DEBUG_PRINTF("╚════╩");
    for( i = 0; i < mast_thd->t2->node_count; i++ )
        _DEBUG_PRINTF("════");
    _DEBUG_PRINTF("═╝\n");
    
}

mast_t* mast_init( tree_t const* t1, tree_t const* t2 ) {
    mast_t* return_mast = (mast_t*)malloc( sizeof(mast_t) );
    
    return_mast->t1 = t1;
    return_mast->t2 = t2;
    
    return_mast->lookup_size = return_mast->t1->node_count * return_mast->t2->node_count;
    
    // Lookup array is in row-major order
    return_mast->lookup = (int_fast32_t*)malloc( return_mast->lookup_size * sizeof(int_fast32_t) );
    
    // Initialize lookup array
    for( int_fast32_t i = 0; i < return_mast->lookup_size; i++ )
        return_mast->lookup[i] = UNDEFINED;
    
    return return_mast;
}

void mast_eval_leaves( mast_t* mast_thd ) {
    node_t* current;
    
    // Leaf - leaf -> identity matrix
    for( int_fast32_t i = 0; i < mast_thd->t1->leaf_count; i++ ) {
        for( int_fast32_t j = 0; j < mast_thd->t2->leaf_count; j++ ) {
            if( i == j ) MAST_LOOKUP(mast_thd, i, j) = 1;
            else MAST_LOOKUP(mast_thd, i, j) = 0;
        }
    }
    
    // Leaf - Node
    for( int_fast32_t i = 0; i < mast_thd->t1->leaf_count; i++ ) {
        current = mast_thd->t2->nodes[i];
        
        // Initialize row with zeros
        for( int_fast32_t j = mast_thd->t2->leaf_count; j < mast_thd->t2->node_count; j++ ) {
            MAST_LOOKUP(mast_thd, i, j) = 0;
        }
        do {
            // Assign value when node can be accessed
            current = current->parent;
            MAST_LOOKUP(mast_thd, i, current->number) = 1;
        } while(current->parent != NULL);
    }
    
    // Node - Leaf
    for( int_fast32_t i = 0; i < mast_thd->t2->leaf_count; i++ ) {
        current = mast_thd->t1->nodes[i];
        
        // Initialize row with zeros
        for( int_fast32_t j = mast_thd->t1->leaf_count; j < mast_thd->t1->node_count; j++ ) {
            MAST_LOOKUP(mast_thd, j, i) = 0;
        }
        while(current->parent != NULL) {
            // Assign value when node can be accessed
            current = current->parent;
            MAST_LOOKUP(mast_thd, current->number, i) = 1;
        };
    }
    
}

int_fast32_t mast( tree_t const* t1, tree_t const* t2 ) {
    mast_t* mast_thd = mast_init(t1,t2);
    
    // Evaluate MAST for leaves
    mast_eval_leaves(mast_thd);
    
    // Debug print mast lookup state
    _DEBUG_PRINTF("Calling debug lookup...\n");
    _DEBUG_PRINT_LOOKUP(mast_thd);
    
    return UNDEFINED;
}
