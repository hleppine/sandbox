#ifndef BoundedQueues_H
#define BoundedQueues_H

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    size_t maxNbItems;
    size_t itemNbOctets;
    size_t nbItems;
    uint8_t* startPtr;
    uint8_t* endPtr;
    uint8_t* frontPtr;
    uint8_t* backPtr;
} BoundedQueues_Queue_T;

static inline void BoundedQueues_initialize(BoundedQueues_Queue_T* queue,
                                            uint8_t* buffer,
                                            size_t bufferNbOctets,
                                            size_t maxNbItems,
                                            size_t itemNbOctets) {
    assert(queue != NULL);
    assert(buffer != NULL);
    assert(bufferNbOctets == (maxNbItems * itemNbOctets));
    *queue = (BoundedQueues_Queue_T){
        .maxNbItems = maxNbItems,
        .itemNbOctets = itemNbOctets,
        .nbItems = 0,
        .startPtr = buffer,
        .endPtr = &buffer[itemNbOctets * (maxNbItems - 1UL)],
        .frontPtr = buffer,
        .backPtr = &buffer[itemNbOctets * (maxNbItems - 1UL)],
    };
}

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

static inline bool BoundedQueues_put(BoundedQueues_Queue_T* queue,
                                     const void* item) {
    assert(queue != NULL);
    assert(item != NULL);
    bool success = !BoundedQueues_isFull(queue);
    if (success) {
        queue->nbItems++;
        // Move back pointer one item to the right, or wrap around.
        queue->backPtr = (queue->backPtr == queue->endPtr)
                             ? queue->startPtr
                             : &queue->backPtr[queue->itemNbOctets];
        (void)memcpy(queue->backPtr, item, queue->itemNbOctets);
    }
    return success;
}

static inline bool BoundedQueues_putToFront(BoundedQueues_Queue_T* queue,
                                            const void* item) {
    assert(queue != NULL);
    assert(item != NULL);
    bool success = !BoundedQueues_isFull(queue);
    if (success) {
        queue->nbItems++;
        // Move front pointer one item to the left, or wrap around.
        queue->frontPtr = (queue->frontPtr == queue->startPtr)
                              ? queue->endPtr
                              : &queue->frontPtr[-queue->itemNbOctets];
        (void)memcpy(queue->frontPtr, item, queue->itemNbOctets);
    }
    return success;
}

static bool BoundedQueues_get(BoundedQueues_Queue_T* queue, void* item) {
    assert(queue != NULL);
    assert(item != NULL);
    bool success = !BoundedQueues_isEmpty(queue);
    if (success) {
        queue->nbItems--;
        (void)memcpy(item, queue->frontPtr, queue->itemNbOctets);
        // Move front pointer one item to the right, or wrap around.
        queue->frontPtr = (queue->frontPtr == queue->endPtr)
                              ? queue->startPtr
                              : &queue->frontPtr[queue->itemNbOctets];
    }
    return success;
}

static bool BoundedQueues_getFromBack(BoundedQueues_Queue_T* queue,
                                      void* item) {
    assert(queue != NULL);
    assert(item != NULL);
    bool success = !BoundedQueues_isEmpty(queue);
    if (success) {
        queue->nbItems--;
        (void)memcpy(item, queue->backPtr, queue->itemNbOctets);
        // Move back pointer one item to the left, or wrap around.
        queue->backPtr = (queue->backPtr == queue->startPtr)
                             ? queue->endPtr
                             : &queue->backPtr[-queue->itemNbOctets];
    }
    return success;
}

#endif /* BoundedQueues_H */
