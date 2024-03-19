#include <stdio.h>
#define METADATA_SIZE sizeof(Metadata)
#define FREE_SPACE_SIZE 40000

typedef enum {false, true} bool;

typedef struct Metadata_tag{
    int size;
    bool free;
    struct Metadata_tag* prev;
} Metadata;

char free_space[FREE_SPACE_SIZE];

Metadata* freeListHead;
int InitialisedFlag = 1;

void Initialise(){
    freeListHead = (Metadata*)free_space;
    freeListHead->free = true;
    freeListHead->size = FREE_SPACE_SIZE - METADATA_SIZE;
    freeListHead->prev = NULL;
    printf("The status is size: %d, free: %d\n", freeListHead->size, freeListHead->free);
}

Metadata* split(Metadata* curr, int required_size ){
    Metadata* next = (Metadata*)((void*)curr + METADATA_SIZE + required_size);
    next->free = true;
    next->size = curr->size - required_size - METADATA_SIZE;
    next->prev = curr;
    curr->size = required_size;
    curr->free = false;
    return curr;
}

void* allocate(int required_size){
    if(InitialisedFlag){
        Initialise();
        InitialisedFlag = 0;
    }
    Metadata* curr = freeListHead;
    void* retVal;
    
    while ((void*)curr <= (void*)&free_space[FREE_SPACE_SIZE-1]) { // first-fit
        if (curr->free == true && curr->size >= required_size && curr->size < required_size + METADATA_SIZE) { // internal fragmentation
            curr->free = false;
            retVal = (void*)(curr + 1);
            return retVal;
        } 
        else if (curr->free == true && curr->size >= required_size + METADATA_SIZE) {
            curr = split(curr, required_size);
            retVal = (void*)(curr + 1);
            return retVal;
        } 
        else {
            curr = (Metadata*)((char*)curr + METADATA_SIZE + curr->size);
        }
    }

    printf("No free space for memory allocation\n");
    return NULL;
}

void merge_blocks(Metadata* curr){
    Metadata* prev = curr->prev;
    Metadata* next = (Metadata*)((char*)curr + METADATA_SIZE + curr->size);

    if(prev != NULL && prev->free == true){
        prev->size += METADATA_SIZE + curr->size;
        curr = prev;
    }

    if((void*)next <= (void*)&free_space[FREE_SPACE_SIZE-1] && next->free == true){
        curr->size += METADATA_SIZE + next->size;
    }
}

void de_allocate(void* loc){
    if(loc < (void*)free_space || loc >= (void*)(free_space + FREE_SPACE_SIZE)){
        printf("Out of bounds\n");
    }
    else{
        Metadata* curr = (Metadata*)loc - 1;
        curr->free = true;
        merge_blocks(curr);
    }
}

int main(){
    printf("Metadata Size: %d\n", METADATA_SIZE);
    printf("Heap Size : %d\n", FREE_SPACE_SIZE);
    printf("Start of free_space :\t%p\n", free_space);
    printf("End of free_space :\t%p\n", &free_space[FREE_SPACE_SIZE-1]);

    int* arr1 = (int*)allocate(5 * sizeof(int));
    printf("%p\n", arr1);

    for(int i = 0; i < 5; i++){
        scanf("%d", &arr1[i]);
    }

    for(int i = 0; i < 5; i++){
        printf("%d ", arr1[i]);
    }
    printf("\n");

    int* arr2 = (int*)allocate(9988);
    printf("%p\n", arr2);

    int* arr3 = (int*)allocate(9988);
    printf("%p\n", arr3);

    int* arr4 = (int*)allocate(9968);
    printf("%p\n", arr4);

    de_allocate(arr2);

    int* arr5 = (int*)allocate(sizeof(int)*4);
    printf("%p\n", arr5);

    int* arr6 = (int*)allocate(9968);
    printf("%p\n", arr6);

    de_allocate(arr4);
    
    int* arr7 = (int*)allocate(9968);
    printf("%p\n", arr7);

    return 0;
}
 