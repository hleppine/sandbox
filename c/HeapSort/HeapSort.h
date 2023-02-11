#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <stddef.h>

typedef int (*HeapSort_CmpFunc_T)(const void* left, const void* right);

void HeapSort_sort(
    void* data, 
    size_t nbItems, 
    size_t itemSize,
    HeapSort_CmpFunc_T cmp,
    void* tmp);

#endif /* HEAPSORT_H */
