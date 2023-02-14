#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Commons.h"
#include "HeapSort.h"

void checkSorted(uint32_t* data, size_t len){
    bool isSorted = true;
    for(size_t i = 0; i < len - 1; i++){
        if(data[i] > data[i+1]){
            isSorted = false;
            break;
        }
    }
    printf("Is sorted: %d\n", isSorted);
}

int cmpfunc (const void * a, const void * b) {
   uint32_t left = *(uint32_t*)a;
   uint32_t right = *(uint32_t*)b;
   return left < right ? -1 : (left > right ? 1 : 0);
}

void test_small_data(void)
{
    uint32_t testData[] = {
        1, 20, 3, 18, 5,
        16, 7, 14, 9, 12,
        11, 10, 13, 8, 15,
        6, 17, 4, 19, 2
    };
    uint32_t tmp;

    const size_t testDataLen = ARRAY_SIZE(testData);

    printf("Test small data\n");
    for(size_t i = 0; i < testDataLen; i++){
        printf("%d ", testData[i]);
    }
    printf("\n");
    HeapSort_sort(testData, testDataLen, sizeof(uint32_t), cmpfunc, &tmp);
    for(size_t i = 0; i < testDataLen; i++){
        printf("%d ", testData[i]);
    }
    printf("\n");

    printf("Done\n");
}

void test_large_data(void)
{
    printf("Test large data vs. qsort\n");
    
    uint32_t testData[100000];
    uint32_t testData2[100000];
    clock_t start;
    clock_t end;
    uint32_t tmp;
    
    const size_t testDataLen = ARRAY_SIZE(testData);
    
    for(size_t i = 0; i < testDataLen; i++){
        testData[i] = (uint32_t)rand();
    }
    
    memcpy(testData2, testData, sizeof(testData[0]) * testDataLen);
    
    checkSorted(testData, testDataLen);
    start = clock();
    HeapSort_sort(testData, testDataLen, sizeof(uint32_t), cmpfunc, &tmp);
    end = clock();
    checkSorted(testData, testDataLen);
    printf("Heap sort: %f\n", ((double)(end - start)) / CLOCKS_PER_SEC );
    
    checkSorted(testData2, testDataLen);
    start = clock();
    qsort(testData2, testDataLen, sizeof(uint32_t), cmpfunc);
    end = clock();
    checkSorted(testData2, testDataLen);
    printf("Quicksort: %f\n", ((double)(end - start)) / CLOCKS_PER_SEC );

    printf("Done");
}

int main(void){
    test_small_data();
    test_large_data();
    return 0;
}
