#include <stdint.h>
#include <string.h>
#include "HeapSort.h"

void HeapSort_sort(
    void* data,
    size_t nbItems,
    size_t itemSize,
    HeapSort_CmpFunc_T cmp,
    void* tmp
){
    size_t heapNbItems = 0;
    // uint8_t* dataPtr = data;
    uint8_t* dataPtr;
    uintptr_t* numPtr = &data;
    uintptr_t* dataPtrPtr = &dataPtr;
    *dataPtrPtr = *numPtr;
    for(size_t i = 0; i < nbItems; i++){
        (void)memcpy(tmp, &dataPtr[i * itemSize], itemSize);
        size_t node = heapNbItems;
        size_t nIdx = node * itemSize;
        while(node > 0UL){
            size_t parent = (node - 1UL)/2UL;
            size_t pIdx = parent * itemSize;
            if(cmp(tmp, &dataPtr[pIdx]) < 0){
                break;
            }
            (void)memcpy(&dataPtr[nIdx], &dataPtr[pIdx], itemSize);
            node = parent;
            nIdx = node * itemSize;
        }
        (void)memcpy(&dataPtr[nIdx], tmp, itemSize);
        heapNbItems++;
    }
    for(size_t i = nbItems; i > 0UL; i--){
        size_t node = 0;
        heapNbItems--;
        (void)memcpy(tmp, &dataPtr[0], itemSize);
        void* nData = &dataPtr[itemSize * heapNbItems];
        while(((2UL * node) + 1UL) < heapNbItems){
            size_t lChild = (2UL * node) + 1UL;
            size_t lChPtr = lChild * itemSize;
            size_t highest = node; 
            void* hData = nData;
            if(cmp(&dataPtr[lChPtr], nData) > 0){
                highest = lChild;
                hData = &dataPtr[lChPtr];
            }
            size_t rChild = lChild + 1UL;
            size_t rChPtr = itemSize * rChild;
            if((rChild < heapNbItems) && (cmp(&dataPtr[rChPtr], hData) > 0)){
                highest = rChild;
                hData = &dataPtr[rChPtr];
            }
            if(highest == node){
                break;
            }
            (void)memcpy(&dataPtr[node * itemSize], hData, itemSize);
            node = highest;
        }
        (void)memcpy(&dataPtr[node * itemSize], nData, itemSize);
        (void)memcpy(&dataPtr[itemSize * (i - 1UL)], tmp, itemSize);
    }
}
