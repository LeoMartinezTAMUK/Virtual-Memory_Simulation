# Virtual Memory Simulation in C (Paging):

**Author:** Leo Martinez III

**Contact:** [leo.martinez@students.tamuk.edu](mailto:leo.martinez@students.tamuk.edu)

**Created:** Spring 2024

---

## Overview:

This repository hosts a C program simulating virtual memory management using paging techniques. Virtual memory is a crucial concept in modern computer systems, allowing programs to operate as if they have more memory than physically available by utilizing disk storage as an extension of RAM. This simulation provides insights into how virtual memory systems manage memory allocation and swapping between physical memory (RAM) and disk storage.

## Features:

- **Randomized Process Simulation:** The program simulates processes with randomized virtual memory addresses, demonstrating address translation and page fault handling.
- **Page Fault Handling:** When a process accesses a page not currently in physical memory, a page fault occurs. The program handles page faults by swapping pages between memory and disk.
- **User Interface:** Users can input virtual addresses to see corresponding physical addresses, illustrating the address translation process.

## Repository Structure:

- **src:** Contains the C source code for the virtual memory simulation program.
- **bin:** Houses the compiled executable file generated from the C source code.
- **README.md:** Provides context and information about the project (you're currently reading it!).
- **LICENSE:** Includes license information (MIT) for the GitHub repository.

## Usage:

1. **Compilation:**
   - Ensure you have GCC (GNU Compiler Collection) installed on your system.
   - Navigate to the `src` directory.
   - Compile the `virtual_memory.c` file using the following command:
     ```bash
     gcc virtual_memory.c -o virtual_memory.exe
     ```

2. **Execution:**
   - After compilation, navigate to the `bin` directory.
   - Run the compiled executable:
     ```bash
     ./virtual_memory
     ```

3. **Simulation:**
   - Follow the on-screen prompts or explore the code to understand the virtual memory simulation process.
   - Input virtual addresses to see corresponding physical addresses and observe how page faults are handled.

## Note:

- The C source code was written in VS Code.
- Compilation was performed using GCC in a UNIX-based terminal environment.