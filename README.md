# Binary Search Tree Library in C

This repository contains a robust and memory-safe implementation of a Binary Search Tree (BST) written in C. The project was designed to demonstrate efficient data handling, complex pointer manipulation, and the lifecycle management of dynamically allocated structures. It serves as a comprehensive toolkit for anyone looking to understand how hierarchical data structures function at a low level.

## Core Project Overview

The library provides a full suite of operations for managing data within a search tree. At its foundation, it handles standard tasks such as iterative node insertion and recursive searching. However, the project goes beyond the basics by including advanced features like tree balancing and sophisticated node removal. Every function is built with a focus on stability and performance, ensuring that the tree remains a reliable way to store and retrieve integers.

## Implementation Details

One of the standout features of this library is the balanceTree function. In many BST implementations, the tree can become lopsided over time, turning into a slow linked list. This project solves that by extracting the data into a sorted dynamic array and rebuilding a height-optimal tree from the ground up. This ensures that the tree depth stays as close as possible to the theoretical minimum, keeping operations fast.

The removal logic is another area where the project excels. Deleting a node in a BST is notoriously difficult because you must account for three distinct scenarios: deleting a leaf, deleting a node with one child, and the complex case of deleting a node with two children. This implementation handles these by finding the in-order successor to maintain the structural integrity of the tree without creating memory orphans.

## Memory Management and Safety

Writing in C requires a disciplined approach to memory, and this library is built with that philosophy. It includes a dedicated recursive cleanup function that traverses the tree in post-order to ensure every single node is freed before the program exits. This prevents the common pitfalls of memory leaks and dangling pointers. Additionally, the project uses assert statements to verify post-conditions, ensuring that the tree is in the expected state after every major modification.

## How to Compile and Run

To use this library or run the included test menu, you will need a C compiler like gcc. You can compile the project by running the following command in your terminal:

gcc main.c BSTree.c -o bst_demo -lm

Once the compilation is finished, you can run the demonstration program with this command:

./bst_demo

The demo provides a CLI menu where you can manually add numbers, remove them, view the different traversal orders, and trigger the balancing algorithm to see how it affects the tree depth in real-time.

## Technical Skills and Concepts

By working through this implementation, several key computer science concepts are put into practice. These include the use of double pointers for tree modification, recursive backtracking for traversals, and logarithmic complexity analysis. The project also makes use of the standard math library to calculate theoretical depths, providing a benchmark for the efficiency of the balancing algorithm.
