#ifndef BoundedQueues_H
#define BoundedQueues_H

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    size_t maxNbItems;
    size_t itemNbOctets;
    size_t nbItems;
    uint8_t* startPtr;
    uint8_t* endPtr;
    uint8_t* frontPtr;
    uint8_t* backPtr;
} BoundedQueues_Queue_T;

void BoundedQueues_initialize(BoundedQueues_Queue_T* queue,
                              uint8_t* buffer,
                              size_t bufferNbOctets,
                              size_t maxNbItems,
                              size_t itemNbOctets);

bool BoundedQueues_put(BoundedQueues_Queue_T* queue, const void* item);

bool BoundedQueues_putToFront(BoundedQueues_Queue_T* queue, const void* item);

bool BoundedQueues_get(BoundedQueues_Queue_T* queue, void* item);

bool BoundedQueues_getFromBack(BoundedQueues_Queue_T* queue, void* item);

static inline uint32_t BoundedQueues_nbItems(
    const BoundedQueues_Queue_T* queue) {
    assert(queue != NULL);
    return queue->nbItems;
}

static inline bool BoundedQueues_isFull(const BoundedQueues_Queue_T* queue) {
    assert(queue != NULL);
    return queue->nbItems == queue->maxNbItems;
}

static inline bool BoundedQueues_isEmpty(const BoundedQueues_Queue_T* queue) {
    assert(queue != NULL);
    return queue->nbItems == 0UL;
}

#endif /* BoundedQueues_H */
