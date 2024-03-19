# Dynamic Memory Management System

## Overview
The Dynamic Memory Management System is a C program that provides functionality for dynamic memory allocation and deallocation using a custom heap management approach. It efficiently handles memory requests, optimizes memory usage, and prevents memory fragmentation.

## Features
- **Custom Heap Management:**
  - Implements a custom heap management system using a fixed-size memory space.
  - Tracks allocated and free memory blocks using metadata structures appended before each block.

- **Memory Allocation:**
  - Provides functions for allocating memory blocks of varying sizes.
  - Implements a first-fit strategy for selecting memory blocks, with splitting and merging optimizations.

- **Memory Deallocation:**
  - Supports deallocation of memory blocks, freeing up space for reuse.
  - Merges adjacent free blocks to prevent memory fragmentation and maximize memory utilization.

## Key Components
- **Metadata Structures:**
  - Metadata structures are appended before each memory block to store information such as block size and free status.
  - Enables efficient tracking and management of memory blocks within the heap.

- **Allocation Algorithm:**
  - Utilizes a first-fit strategy to allocate memory blocks, searching for the first available block that meets the requested size.
  - Implements splitting of blocks when allocating larger sizes to minimize internal fragmentation.

- **Deallocation Mechanism:**
  - Frees memory blocks upon deallocation, updating metadata and merging adjacent free blocks to optimize memory usage. Does this in O(1) time complexity.

## Usage
1. **Compilation:**
   - Compile the program using a C compiler (e.g., gcc).
     ```bash
     gcc heap_management.c -o heap_management
     ```

2. **Execution:**
   - Run the compiled executable.
     ```bash
     ./heap_management
     ```

3. **Allocation and Deallocation:**
   - Use the provided functions `allocate` and `de_allocate` to dynamically manage memory within the heap.
   - Follow the on-screen prompts to allocate and deallocate memory blocks of varying sizes.

## Notes
- Ensure that the maximum heap size is appropriately configured to prevent memory overflow.
- Validate memory allocations and deallocations to prevent memory leaks and access violations.
- Ensure that the C compiler is installed on your system.

