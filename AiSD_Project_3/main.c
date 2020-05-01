//
//  main.c
//  AiSD_Project_3
//
//  Created by Kacper Kędzierski on 29/04/2020.
//  Copyright © 2020 Kacper Kędzierski. All rights reserved.
//

#define _DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include "misc.h"
#include "node.h"
#include "tree.h"

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
