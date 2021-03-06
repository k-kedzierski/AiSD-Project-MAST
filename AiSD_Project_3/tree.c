//
//  tree.c
//  AiSD_Project_3
//
//  Created by Kacper Kędzierski on 01/05/2020.
//  Copyright © 2020 Kacper Kędzierski. All rights reserved.
//

#include "tree.h"

// ===
// Functions definitions
// ===

tree_t* tree_init() {
    tree_t* return_tree = (tree_t*)malloc( sizeof(tree_t ));
    
    return_tree-> root = NULL;
    return_tree->leaf_count = 0;
    return_tree->node_count = 0;
    
    return return_tree;
}

void tree_free( tree_t* tree ) {
    for( int_fast32_t i = 0; i < tree->node_count; i++ )
        free(tree->nodes[i]);
    
    free(tree->nodes);
    free(tree);
}

void tree_label_inner_nodes( tree_t* tree ) {
    node_t*         current = tree->root;
    int_fast32_t    label = tree->leaf_count;
    
    // Labeling using indexes from leaf count up to node count - bottom-up approach
    while (label < tree->node_count) {
        
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
                current = current->sibling;
                tree->node_count++;
                break;
            case ';':
                tree->root = current;
                tree->node_count++;
                return;
            default:
                // Modify leaf value
                if( current->number == UNDEFINED ) {
                    // Decrement leaf for 0...n-1 indexes
                    current->number = (int)(c - 48 - 1);
                    tree->leaf_count++;
                }
                else {
                    current->number += 1;
                    current->number *= 10;
                    current->number += (int)(c - 48 - 1);
                }
                break;
        }
    }
}

void tree_fill_nodes( tree_t* tree ) {
    tree->nodes = (node_t**)malloc( tree->node_count * sizeof(node_t) );
    node_t* current = tree->root;
    
    // Initialize nodes lookup
    for( int_fast32_t i = 0; i < tree->node_count; i++ ) {
        tree->nodes[i] = NULL;
    }
    
    // Fill nodes lookup bottom-up
    while (tree->nodes[tree->root->number] == NULL) {
        
        // Go to unassigned child
        if(     current->child != NULL
           &&   current->child != tree->nodes[current->child->number]) {
            current = current->child;
        }
        
        // Else, proceed to right and go to unassigned sibling
        else if(    current->sibling != NULL
                &&  current->sibling != tree->nodes[current->sibling->number]) {
            current = current->sibling;
        }
        
        // Else, assign to nodes lookup
        else {
            tree->nodes[current->number] = current;
            // ...and go back to parent
            current = current->parent;
        }
    }
}

tree_t* tree_scan() {
    tree_t* return_tree = tree_init();
    
    // Get tree definition
    tree_get_definition(return_tree);
    
    // Label inner nodes
    tree_label_inner_nodes(return_tree);
    
    // Fill nodes lookup
    tree_fill_nodes(return_tree);
    
    return return_tree;
}
