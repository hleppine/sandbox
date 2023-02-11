#include <stdint.h>
#include <stdio.h>
#include "GenericHeaps.h"

void print(const GenericHeaps_Heap_T* heap){
    for(size_t i = 0; i < heap->nbItems; i++){
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

void testExtract(GenericHeaps_Heap_T* heap){
    uint32_t item;
    extract(heap, &item);
    printf("Extracted %d\n", item);
    print(heap);
}

#define NB_ITEMS(X) (sizeof(X)/sizeof(X[0]))

int main()
{
    
    const uint32_t testData[] = {
        2, 1, 4, 3, 6,
        5, 8, 7, 10, 9,
        98, 89, 96, 87, 94,
        85, 92, 83, 90, 81
    };
    
    uint32_t data[NB_ITEMS(testData)] = {0};
    
    GenericHeaps_Heap_T heap;
    
    heap.data = data;
    heap.maxNbItems = NB_ITEMS(testData);
    heap.nbItems = 0;
    
    print(&heap);
    
    for(size_t i=0; i<heap.maxNbItems; i++){
        insert(&heap, testData[i]);
    }

    print(&heap);
    
    for(size_t i=0; i<heap.maxNbItems; i++){
        testExtract(&heap);
    }
    
    printf("Done");
   
    return 0;
}

