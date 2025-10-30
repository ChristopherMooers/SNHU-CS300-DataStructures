# CS 300: Data Structures and Algorithms

## Project Overview
This project focused on implementing and analyzing fundamental data structures to evaluate their efficiency in terms of **runtime** and **memory usage**.  
The goal was to design and compare multiple data structures capable of storing, sorting, and printing a list of **Computer Science courses in alphanumeric order**.  
This repository contains both the performance analysis document and the working C++ code implementation.

---

## Reflection

**What was the problem you were solving in this course?**  
The main challenge was to determine which data structures—**vector**, **binary search tree (BST)**, or **hash table**—were best suited for managing and sorting large datasets efficiently. The goal was to load and output course information quickly while minimizing memory use.

**How did you approach the problem?**  
I implemented separate versions of the course-sorting program using different data structures, then measured each structure’s runtime and space complexity. I analyzed the trade-offs between **O(n)**, **O(log n)**, and **O(1)** operations, using theoretical and practical testing.

**How did you overcome any roadblocks?**  
Debugging pointer and memory-management issues was a major learning point. I used step-through debugging in **Visual Studio**, along with `cout` tracing and logical checks, to isolate where traversal logic failed in the BST and where memory wasn’t being freed correctly.

**How has your work expanded your approach to designing software?**  
This project helped me recognize that data-structure selection impacts every part of system design. I now prioritize designing around algorithmic efficiency, modularity, and clean abstraction to improve scalability.

**How has your work evolved the way you write programs?**  
I’ve grown more deliberate about separating functionality into clear header (`.hpp`) and implementation (`.cpp`) files, using consistent naming conventions and commenting. I also write programs that are more maintainable, readable, and adaptable for future extension.

---

## Files Included
- [`docs/Runtime_Memory_Analysis.pdf`](docs/Runtime_Memory_Analysis.pdf) – Report analyzing time and space complexity for vector, BST, and hash table implementations.  
- [`src/ABCU_Advising_Program.cpp`](src/ABCU_Advising_Program.cpp) – C++ program that loads, sorts, and prints course data in alphanumeric order.  
- [`src/CS 300 ABCU_Advising_Program_Input.csv`](src/CS%20300%20ABCU_Advising_Program_Input.csv) – Input dataset for the advising program.

---
