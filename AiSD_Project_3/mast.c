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

void _DEBUG_PRINT_MATRIX( match_t* match_thd, node_t* node1, node_t* node2 ) {
    int_fast32_t i, j;
    node_t* current_1;
    node_t* current_2;
    
    _DEBUG_PRINTF("╔════╦");
    for( i = 0; i < match_thd->size[1]; i++ )
        _DEBUG_PRINTF("════");
    _DEBUG_PRINTF("═╗\n");
    
    _DEBUG_PRINTF("║    ║");
    // Label 1st dimension
    if(match_thd->swapped) {
        for( current_1 = node1->child, i = 0;
        current_1 != NULL;
        current_1 = current_1-> sibling, i++ )
            _DEBUG_PRINTF("%4d", current_1->number);
    } else {
        for( current_2 = node2->child, j = 0;
        current_2 != NULL;
        current_2 = current_2->sibling, j++ )
             _DEBUG_PRINTF("%4d", current_2->number);
    }
    _DEBUG_PRINTF(" ║\n");
    
    _DEBUG_PRINTF("╠════╬");
    for( i = 0; i < match_thd->size[1]; i++ )
        _DEBUG_PRINTF("════");
    _DEBUG_PRINTF("═╣\n");
    
    if(match_thd->swapped)
        current_2 = node2->child;
    else
        current_2 = node1->child;
    
    for( i = 0; i < match_thd->size[0]; i++ ) {
        // Label 2nd dimension
        
        _DEBUG_PRINTF("║" "%4d" "║", current_2->number);
        current_2 = current_2->sibling;
        for( j = 0; j < match_thd->size[1]; j++ ) {
            _DEBUG_PRINTF("%4d", MATCH_LOOKUP(match_thd, i, j));
        }
        _DEBUG_PRINTF(" ║\n");
        if( i == match_thd->size[0] - 1 ) break;
        _DEBUG_PRINTF("║    ║" "%*c" " ║\n", 4 * match_thd->size[1], ' ');
    }
    
    _DEBUG_PRINTF("╚════╩");
    for( i = 0; i < match_thd->size[1]; i++ )
        _DEBUG_PRINTF("════");
    _DEBUG_PRINTF("═╝\n");
    
    
}

match_t* match_init( int_fast32_t size_y, int_fast32_t size_x ) {
    match_t* return_match = (match_t*)malloc( sizeof(match_t) );
    
    // Using matrix index notation
    // Important! Number of columns must be greater than number of rows
    if( size_x < size_y ) {
        // Swap rows with collumns
        return_match->swapped = true;
        _DEBUG_PRINTF("Swapping rows and columns...\n")
        
        return_match->size[0] = size_x;
        return_match->size[1] = size_y;
    }
    else {
        return_match->swapped = false;
        
        return_match->size[0] = size_y;
        return_match->size[1] = size_x;
    }
    
    // Initialize banned columns array
    return_match->banned = (bool*)malloc( return_match->size[1] * sizeof(bool) );
    
    for( int_fast32_t i = 0; i < return_match->size[1]; i++ )
        return_match->banned[i] = false;
    
    // Match matrix is in row-major order
    return_match->match_matrix = (int_fast32_t*)malloc( size_x * size_y * sizeof(int_fast32_t) );
    
    return return_match;
}

void match_free( match_t* match_thd ) {
    free(match_thd->match_matrix);
    free(match_thd->banned);
    free(match_thd);
}

void match_opt_sum( match_t* match_thd, int_fast32_t current_row, int_fast32_t* return_value, int_fast32_t sum ) {
    // This algorithm works only when number of collumns >= number of rows
    for( int_fast32_t col = 0; col < match_thd->size[1]; col++ ) {
        if( match_thd->banned[col] ) {
            continue;
        }
        
        if( current_row < match_thd->size[0] - 1) {
            match_thd->banned[col] = true;
            match_opt_sum(match_thd, current_row + 1, return_value, sum + MATCH_LOOKUP(match_thd, current_row, col));
            match_thd->banned[col] = false;
        } else if( sum + MATCH_LOOKUP(match_thd, current_row, col) > *return_value) {
            *return_value = sum + MATCH_LOOKUP(match_thd, current_row, col);
        }
    }
}

int_fast32_t match_eval_matrix( mast_t* mast_thd, node_t* node1, node_t* node2 ) {
    _DEBUG_PRINTF("Called mast(%d,%d)\n",node1->number,node2->number);
    match_t*        match_thd = match_init(node_count_children(node1), node_count_children(node2));
    int_fast32_t    return_value = 0;
    
    // Fill match matrix
    node_t* current_1;
    node_t* current_2;
    int_fast32_t i,j;
    
    // Check if matrix was swapped
    if(match_thd->swapped) {
        for( current_1 = node2->child, i = 0;
            current_1 != NULL;
            current_1 = current_1-> sibling, i++ )
            for( current_2 = node1->child, j = 0;
                current_2 != NULL;
                current_2 = current_2->sibling, j++ )
                MATCH_LOOKUP(match_thd, i, j) = mast_get_lookup(mast_thd, current_2, current_1);
        
    }
    else {
        for( current_1 = node1->child, i = 0;
            current_1 != NULL;
            current_1 = current_1-> sibling, i++ )
            for( current_2 = node2->child, j = 0;
                current_2 != NULL;
                current_2 = current_2->sibling, j++ )
                MATCH_LOOKUP(match_thd, i, j) = mast_get_lookup(mast_thd, current_1, current_2);
    }
    
    // Print match matrix to debug stream
    _DEBUG_PRINT_MATRIX(match_thd, node1, node2);
    
    // Find max sum
    match_opt_sum(match_thd, 0, &return_value, 0);
    
    // Free dynamically allocated memory
    match_free(match_thd);
    
    // Print current state
    _DEBUG_PRINTF("Max matrix sum for mast(%d,%d) = %d\n",node1->number,node2->number,return_value);
    
    
    return return_value;
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

void mast_free( mast_t* mast_thd ) {
    free(mast_thd->lookup);
    free(mast_thd);
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

int_fast32_t mast_eval_nodes( mast_t* mast_thd, node_t* node1, node_t* node2 ) {
    node_t*         current;
    int_fast32_t    cache;
    int_fast32_t    max = UNDEFINED;
    
    // 1st case: consider node1 children
    current = node1->child;
    while( current != NULL ) {
        // Override function cache
        cache = mast_get_lookup(mast_thd,current,node2);
        // Update return value
        max = cache > max ? cache : max;
        // Proceed to sibling
        current = current->sibling;
    }
    
    // 2nd case: consider node2 children
    current = node2->child;
    while( current != NULL ) {
        // Override function cache
        cache = mast_get_lookup(mast_thd,node1,current);
        // Update return value
        max = cache > max ? cache : max;
        // Proceed to sibling
        current = current->sibling;
    }
    
    // 3rd case: matching
    cache = match_eval_matrix(mast_thd, node1, node2);
    max = cache > max ? cache : max;
    
    // Assign value to lookup
    MAST_LOOKUP(mast_thd, node1->number, node2->number) = max;
    
    // Print lookup array to debug stream
    _DEBUG_PRINTF("Calling debug lookup...\n");
    _DEBUG_PRINT_LOOKUP(mast_thd);
    
    return max;
}

int_fast32_t mast_get_lookup( mast_t* mast_thd, node_t* node1, node_t* node2 ) {
    int_fast32_t return_value = MAST_LOOKUP(mast_thd, node1->number, node2->number);
    
    // Check if problem was already evaluated
    // else, evaluate MAST for nodes
    if( return_value == UNDEFINED ) {
        return mast_eval_nodes(mast_thd,node1,node2);
    }
    else return return_value;
}

int_fast32_t mast_get_opt( mast_t* mast_thd ) {
    return mast_get_lookup(mast_thd, mast_thd->t1->root, mast_thd->t2->root);
}

int_fast32_t mast( tree_t const* t1, tree_t const* t2 ) {
    mast_t* mast_thd = mast_init(t1,t2);
    
    // Evaluate MAST for leaves
    mast_eval_leaves(mast_thd);
    
    // Find optimal value
    int_fast32_t return_value = mast_get_opt(mast_thd);
    
    // Free dynamically allocated memory
    mast_free(mast_thd);
    
    // Return
    return return_value;
    
}
