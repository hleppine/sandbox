#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// TODO: Not yet actually generic
typedef struct {
   uint32_t* data;
   size_t maxNbItems;
   size_t nbItems;
} GenericHeaps_Heap_T;

static inline bool insert(GenericHeaps_Heap_T* heap, uint32_t item){
    bool success = heap->nbItems < heap->maxNbItems;
    if(success){
        size_t node = heap->nbItems;
        while(node > 0UL){
            size_t parent = (node - 1UL)/2UL;
            if(item < heap->data[parent]){
                break;
            }
            heap->data[node] = heap->data[parent];
            node = parent;
        }
        heap->data[node] = item;
        heap->nbItems++;
    }
    return success;
}

static inline bool extract(GenericHeaps_Heap_T* heap, uint32_t* item){
    bool success = heap->nbItems > 0UL;
    if(success){
        size_t node = 0;
        heap->nbItems--;
        uint32_t* data = heap->data;
        *item = data[node];
        uint32_t* nData = &data[heap->nbItems];
        while(((2UL * node) + 1UL) < heap->nbItems){
            size_t lChild = (2UL * node) + 1UL;
            size_t highest = node; 
            uint32_t* hData = nData;
            if(data[lChild] > *nData){
                highest = lChild;
                hData = &data[lChild];
            }
            size_t rChild = lChild + 1UL;
            if((rChild < heap->nbItems) && (data[rChild] > *hData)){
                highest = rChild;
                hData = &data[rChild];
            }
            if(highest == node){
                break;
            }
            data[node] = *hData;
            node = highest;
        }
        heap->data[node] = *nData;
    }
    return success;
}
