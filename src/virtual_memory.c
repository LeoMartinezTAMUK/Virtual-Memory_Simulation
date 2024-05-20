// Virtual Memory Aspect Simulation
// Created in Spring 2024 by Leo Martinez III

// Necessary include statements
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// example values, real memory and disc would be significantly more complex and larger
const int NUM_PROCESSES = 10;
const int NUM_PAGES = 100;
const int PAGE_SIZE = 10;
const int FRAME_SIZE = 10;
const int NUM_FRAMES = 20;
const int MEMORY_SIZE = 200; // 20 frames * 10 size of each frame 
const int DISC_SIZE = 1000; // disc large enough to hold all processes (and pages) to be swapped to memory

// create two arrays to simulate both memory and disc
char memory[200];
char disc[1000]; // main memory is always much smaller than disc (secondary storage) size

// page table data structure to store the mappings
// between virtual and physical pages
typedef struct{
    int virtual_page_num;   // Virtual page number (0-9)
    int physical_page_num;  // Corresponding physical frame number (0-20)
    int process_num; // Corresponding process number (0-9)
    bool valid;
} PageTableEntry;

void initialize_memory()
{
    for(int i = 0; i < MEMORY_SIZE; i++){
        memory[i] = '0'; // fill memory with zeroes
    }
}

void initialize_disc(PageTableEntry disc[NUM_PROCESSES][(NUM_PAGES/NUM_PROCESSES)]) {
    // initialize the page table entries on the disc
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < (NUM_PAGES/NUM_PROCESSES); j++) {
            // set the virtual page number for each entry
            disc[i][j].virtual_page_num = j;  // virtual page numbers start from 0 within each process
            // initialize other fields
            disc[i][j].physical_page_num = -1;  // initialize physical page number to -1 indicating it's not mapped yet
            disc[i][j].process_num = i; // process numbers start from 0 for every row
            disc[i][j].valid = false;           // initialize valid flag to false
        }
    }
}

// page fault handling: 
void page_fault_handler(int frame_num,PageTableEntry disc_page_table[NUM_PROCESSES][(NUM_PAGES/NUM_PROCESSES)], int i, int j){
    if (memory[frame_num] == '0') {}
    else{
        memory[(rand() % 20)] = '0';
        disc_page_table[i][j].physical_page_num = -1;
        disc_page_table[i][j].valid = false;
    }
}

// address translation (virtual (page) to physical (frame))
int address_translation(int virtual_address, int i,PageTableEntry disc_page_table[NUM_PROCESSES][(NUM_PAGES/NUM_PROCESSES)])
{
    int process_num = virtual_address / (DISC_SIZE / NUM_PROCESSES);
    int page_num = (virtual_address / PAGE_SIZE) % 10;
    int frame_num = rand() % 20;
    int j = page_num % 10;
    if (memory[frame_num] == '0') {
        printf("page: %d is now in frame %d\n",page_num, frame_num);
        memory[frame_num] = '1';
        disc_page_table[process_num][page_num].physical_page_num = frame_num;
        disc_page_table[process_num][page_num].valid = true;
    }
    else {
       page_fault_handler(frame_num,disc_page_table,i,j);
       disc_page_table[i][j].valid = true;
       disc_page_table[i][j].physical_page_num = frame_num;
       printf("page fault handled => page: %d is now in frame %d\n",page_num, frame_num);
    }
    return(frame_num);
}

// randomized process simulation
void process_simulation(PageTableEntry disc[NUM_PROCESSES][(NUM_PAGES/NUM_PROCESSES)])
{
    int j = 0;
    for(int i=0;i<NUM_PROCESSES;i++){
        int virtual_address = (rand() % (DISC_SIZE/NUM_PROCESSES))+j;
        printf("process %d is stored in virtual address: %d\n => ", i,virtual_address );
        int physical_address = address_translation(virtual_address, i,disc);
        printf("physical address is: %d\n\n",physical_address * FRAME_SIZE);
        j = j + 100;
    }
}

// user-friendly interface for inputting virtual addresses and displaying the corresponding physical addresses
void user_interface(PageTableEntry disc_page_table[NUM_PROCESSES][(NUM_PAGES/NUM_PROCESSES)]) { 
    int virtual_address;
    printf("\n\nEnter -1 to exit\n");
    int i = 0;
    // can add error checking for input outside of disc size
    while(i<1){
        printf("\nEnter a virtual address (0-%i): ", DISC_SIZE - 1);
        scanf("%i", &virtual_address);
        if(virtual_address == -1){
            i=1;
            exit(0);
        }else if (virtual_address > (DISC_SIZE - 1) || virtual_address < -1) {
            printf("Error Virtual Address '%i' out of Memory Range!", virtual_address);
            user_interface(disc_page_table);
        }else if(virtual_address < (DISC_SIZE - 1) || virtual_address > 0){
        // calculate what process, page, and frame (if any)
        int process_num = virtual_address / (DISC_SIZE / NUM_PROCESSES);
        int page_num = (virtual_address / PAGE_SIZE) % 10;
        int frame_num = disc_page_table[process_num][page_num].physical_page_num;

        if (frame_num == -1) { // -1 means it is still on the disc, not main memory
            printf("The page virtual address '%i' resides in is currently not in main memory.\n", virtual_address);
        } 
        // the frame number * size of a frame is the address in main memory
        else { 
            int physical_address = frame_num * FRAME_SIZE;
            printf("Physical address corresponding to virtual address %d is: %d\n", virtual_address, physical_address);
        }
        }
    }
}

int main() // all methods are invoked here
{
    
    // seed a random number generator with the current time
    srand(time(NULL));
    
    PageTableEntry disc_page_table[NUM_PROCESSES][(NUM_PAGES/NUM_PROCESSES)];

    // initialize your main memory and disc space
    initialize_memory();
    initialize_disc(disc_page_table);
	
	// page has had a physical frame number generated and valid is now equal to true so it is in memory
    process_simulation(disc_page_table);

    // allow a user to enter any virtual address
    user_interface(disc_page_table);    
}