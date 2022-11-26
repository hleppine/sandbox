#include <stdlib.h>
#include <string.h>

#include "BoundedQueues.h"

/* Local functions */

static inline bool inRangeU32(uint32_t value, uint32_t min, uint32_t max) {
    return (min <= value && value <= max);
}

static inline bool inRangePtr(const void* ptr,
                              const void* begin,
                              const void* end) {
    return (begin <= ptr && ptr <= end);
}

static inline bool isConsistent(const BoundedQueues_Queue_T* queue) {
    assert(queue != NULL);
    assert(inRangeU32(queue->nbItems, 0, queue->maxNbItems));
    assert(inRangePtr(queue->frontPtr, queue->startPtr, queue->endPtr));
    assert(inRangePtr(queue->backPtr, queue->startPtr, queue->endPtr));
    assert((queue->frontPtr - queue->startPtr) % queue->itemNbOctets == 0);
    assert((queue->backPtr - queue->startPtr) % queue->itemNbOctets == 0);
    (void)queue;
    return true;
}

/* Public functions */

void BoundedQueues_initialize(BoundedQueues_Queue_T* queue,
                              uint8_t* buffer,
                              uint32_t buffer_nb_octets,
                              uint32_t maxNbItems,
                              uint32_t itemNbOctets) {
    assert(queue != NULL);
    assert(buffer != NULL);
    assert(maxNbItems > 0);
    assert(itemNbOctets > 0);
    assert(buffer_nb_octets == maxNbItems * itemNbOctets);

    *queue = (BoundedQueues_Queue_T){
        .maxNbItems = maxNbItems,
        .itemNbOctets = itemNbOctets,
        .nbItems = 0,
        .startPtr = buffer,
        .endPtr = buffer + (size_t)(buffer_nb_octets - itemNbOctets),
        .frontPtr = buffer,
        .backPtr = buffer + (size_t)(buffer_nb_octets - itemNbOctets),
    };

    assert(isConsistent(queue));
}

bool BoundedQueues_put(BoundedQueues_Queue_T* queue, const void* item) {
    assert(isConsistent(queue));
    assert(item != NULL);

    bool success = false;

    if (!BoundedQueues_isFull(queue)) {
        success = true;
        queue->nbItems++;
        queue->backPtr += queue->itemNbOctets;
        if (queue->backPtr > queue->endPtr) {
            queue->backPtr = queue->startPtr;
        }
        memcpy(queue->backPtr, item, queue->itemNbOctets);
    }

    assert(isConsistent(queue));

    return success;
}

bool BoundedQueues_putToFront(BoundedQueues_Queue_T* queue, const void* item) {
    assert(isConsistent(queue));
    assert(item != NULL);

    bool success = false;

    if (!BoundedQueues_isFull(queue)) {
        success = true;
        queue->nbItems++;
        queue->frontPtr -= queue->itemNbOctets;
        if (queue->frontPtr < queue->startPtr) {
            queue->frontPtr = queue->endPtr;
        }
        memcpy(queue->frontPtr, item, queue->itemNbOctets);
    }

    assert(isConsistent(queue));

    return success;
}

bool BoundedQueues_get(BoundedQueues_Queue_T* queue, void* item) {
    assert(isConsistent(queue));
    assert(item != NULL);

    bool success = false;

    if (!BoundedQueues_isEmpty(queue)) {
        success = true;
        queue->nbItems--;
        memcpy(item, queue->frontPtr, queue->itemNbOctets);
        queue->frontPtr += queue->itemNbOctets;
        if (queue->frontPtr > queue->endPtr) {
            queue->frontPtr = queue->startPtr;
        }
    }

    assert(isConsistent(queue));

    return success;
}

bool BoundedQueues_getFromBack(BoundedQueues_Queue_T* queue, void* item) {
    assert(isConsistent(queue));
    assert(item != NULL);

    bool success = false;

    if (!BoundedQueues_isEmpty(queue)) {
        success = true;
        queue->nbItems--;
        memcpy(item, queue->backPtr, queue->itemNbOctets);
        queue->backPtr -= queue->itemNbOctets;
        if (queue->backPtr < queue->startPtr) {
            queue->backPtr = queue->endPtr;
        }
    }

    assert(isConsistent(queue));

    return success;
}

extern inline uint32_t BoundedQueues_nbItems(
    const BoundedQueues_Queue_T* queue);

extern inline bool BoundedQueues_isFull(const BoundedQueues_Queue_T* queue);

extern inline bool BoundedQueues_isEmpty(const BoundedQueues_Queue_T* queue);