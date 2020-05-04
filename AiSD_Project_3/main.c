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
#include "misc.h"
#include "node.h"
#include "tree.h"
#include "mast.h"

// ===
// Main
// ===

int main() {
    
    DEBUG_PRINTF("Debug stream initialized\n");
    
    int_fast32_t tree_set_size;
    
    // Initialize tree definitions
    scanf("%" SCNdFAST32, &tree_set_size);
    tree_t** tree_set = (tree_t**)malloc( tree_set_size * sizeof(tree_t) );
    for( int_fast32_t i = 0; i < tree_set_size; i++ ) {
        tree_set[i] = tree_scan();
    }
    
    // Compute all n(n-1)/2 input trees comparisons
    for( int_fast32_t i = 0; i < tree_set_size; i++ ) {
        for( int_fast32_t j = i + 1; j < tree_set_size; j++ ) {
            printf("%" SCNdFAST32 "\n", tree_set[i]->leaf_count - mast(tree_set[i], tree_set[j]));
        }
    }
    
    // Free dynamically allocated memory
    for( int_fast32_t i = 0; i < tree_set_size; i++ )
        tree_free(tree_set[i]);
    free(tree_set);
    
    return 0;
}
