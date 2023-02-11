#include "HeapSort.h"

void HeapSort_sort(
    void* data,
    size_t nbItems,
    size_t itemSize,
    HeapSort_CmpFunc_T cmp,
    void* tmp
){
    size_t heapNbItems = 0;
    unsigned char* dataPtr = data;
    for(size_t i = 0; i < nbItems; i++){
        memcpy(tmp, &dataPtr[i * itemSize], itemSize);
        size_t node = heapNbItems;
        size_t nIdx = node * itemSize;
        while(node > 0){
            size_t parent = (node - 1)/2;
            size_t pIdx = parent * itemSize;
            if(cmp(&tmp, &dataPtr[pIdx]) < 0){
                break;
            }
            memcpy(&dataPtr[nIdx], &dataPtr[pIdx], itemSize);
            node = parent;
            nIdx = node * itemSize;
        }
        memcpy(&dataPtr[nIdx], tmp, itemSize);
        heapNbItems++;
    }
    for(size_t i = nbItems; i > 0; i--){
        size_t node = 0;
        heapNbItems--;
        memcpy(tmp, &dataPtr[0], itemSize);
        void* nData = &dataPtr[itemSize * heapNbItems];
        while(1){
            size_t lChild = 2 * node + 1;
            size_t lChPtr = lChild * itemSize;
            if(lChild >= heapNbItems){
                break;
            }
            size_t highest = node; 
            void* hData = nData;
            if(cmp(&dataPtr[lChPtr], nData) > 0){
                highest = lChild;
                hData = &dataPtr[lChPtr];
            }
            size_t rChild = lChild + 1;
            size_t rChPtr = itemSize * rChild;
            if((rChild < heapNbItems) && (cmp(&dataPtr[rChPtr], hData) > 0)){
                highest = rChild;
                hData = &dataPtr[rChPtr];
            }
            if(highest == node){
                break;
            }
            memcpy(&dataPtr[node * itemSize], hData, itemSize);
            node = highest;
        }
        memcpy(&dataPtr[node * itemSize], nData, itemSize);
        memcpy(&dataPtr[itemSize*(i-1)], tmp, itemSize);
    }
}
