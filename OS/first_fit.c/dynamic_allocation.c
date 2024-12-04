#include <stdio.h>
#include <stdlib.h>

typedef struct MemoryBlock {
    int size;               
    int is_allocated;       
    struct MemoryBlock *next;
} MemoryBlock;

typedef struct Process {
    int size;               
    int is_allocated;       
} Process;

MemoryBlock* create_memory_block(int size) {
    MemoryBlock *new_block = (MemoryBlock *)malloc(sizeof(MemoryBlock));
    new_block->size = size;
    new_block->is_allocated = 0;  
    new_block->next = NULL;
    return new_block;
}

MemoryBlock* initialize_memory_pool(int sizes[], int n) {
    MemoryBlock *head = create_memory_block(sizes[0]);
    MemoryBlock *temp = head;
    for (int i = 1; i < n; i++) {
        temp->next = create_memory_block(sizes[i]);
        temp = temp->next;
    }
    return head;
}

void display_memory_blocks(MemoryBlock *head) {
    MemoryBlock *temp = head;
    while (temp != NULL) {
        printf("Block Size: %d, Status: %s\n", temp->size, temp->is_allocated ? "Allocated" : "Free");
        temp = temp->next;
    }
    printf("\n");
}

int first_fit(MemoryBlock *head, int process_size) {
    MemoryBlock *temp = head;
    while (temp != NULL) {
        if (!temp->is_allocated && temp->size >= process_size) {
            temp->is_allocated = 1;
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

int best_fit(MemoryBlock *head, int process_size) {
    MemoryBlock *best_fit_block = NULL;
    MemoryBlock *temp = head;
    int min_diff = __INT_MAX__;
    
    while (temp != NULL) {
        if (!temp->is_allocated && temp->size >= process_size) {
            int diff = temp->size - process_size;
            if (diff < min_diff) {
                min_diff = diff;
                best_fit_block = temp;
            }
        }
        temp = temp->next;
    }

    if (best_fit_block != NULL) {
        best_fit_block->is_allocated = 1;
        return 1;
    }
    return 0;  
}

void deallocate_memory(MemoryBlock *head, int process_size) {
    MemoryBlock *temp = head;
    while (temp != NULL) {
        if (temp->size == process_size && temp->is_allocated) {
            temp->is_allocated = 0;
            break;
        }
        temp = temp->next;
    }
}

int main() {
    int memory_sizes[] = {100, 500, 200, 300, 600};  
    int process_sizes[] = {212, 417, 112, 426};      

    int num_memory_blocks = sizeof(memory_sizes) / sizeof(memory_sizes[0]);
    int num_processes = sizeof(process_sizes) / sizeof(process_sizes[0]);

    MemoryBlock *memory_pool = initialize_memory_pool(memory_sizes, num_memory_blocks);

    printf("First Fit Allocation:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Allocating process of size %d\n", process_sizes[i]);
        if (first_fit(memory_pool, process_sizes[i])) {
            printf("Process %d allocated successfully!\n", process_sizes[i]);
        } else {
            printf("Process %d could not be allocated.\n", process_sizes[i]);
        }
    }
    display_memory_blocks(memory_pool);

    printf("\nDeallocating memory for testing Best Fit...\n");
    deallocate_memory(memory_pool, process_sizes[0]);
    deallocate_memory(memory_pool, process_sizes[1]);

    memory_pool = initialize_memory_pool(memory_sizes, num_memory_blocks);
    
    printf("Best Fit Allocation:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Allocating process of size %d\n", process_sizes[i]);
        if (best_fit(memory_pool, process_sizes[i])) {
            printf("Process %d allocated successfully!\n", process_sizes[i]);
        } else {
            printf("Process %d could not be allocated.\n", process_sizes[i]);
        }
    }
    display_memory_blocks(memory_pool);

    return 0;
}
