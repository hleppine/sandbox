#include <stdlib.h>
#include <string.h>

#include "BoundedQueues.h"

/* Local functions */

static inline bool inRangeU32(uint32_t value, uint32_t min, uint32_t max) {
    return ((min <= value) && (value <= max));
}

static inline bool inRangePtr(const void* ptr,
                              const void* begin,
                              const void* end) {
    return ((begin <= ptr) && (ptr <= end));
}

static inline bool isConsistent(const BoundedQueues_Queue_T* queue) {
    assert(queue != NULL);
    assert(inRangeU32(queue->nbItems, 0, queue->maxNbItems));
    assert(inRangePtr(queue->frontPtr, queue->startPtr, queue->endPtr));
    assert(inRangePtr(queue->backPtr, queue->startPtr, queue->endPtr));
    (void)queue;
    return true;
}

/* Public functions */

void BoundedQueues_initialize(BoundedQueues_Queue_T* queue,
                              uint8_t* buffer,
                              size_t bufferNbOctets,
                              size_t maxNbItems,
                              size_t itemNbOctets) {
    assert(queue != NULL);
    assert(buffer != NULL);
    assert(maxNbItems > 0UL);
    assert(itemNbOctets > 0UL);
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

    assert(isConsistent(queue));
}

bool BoundedQueues_put(BoundedQueues_Queue_T* queue, const void* item) {
    assert(isConsistent(queue));
    assert(item != NULL);

    bool success = false;

    if (!BoundedQueues_isFull(queue)) {
        success = true;
        queue->nbItems++;
        queue->backPtr = &queue->backPtr[queue->itemNbOctets];
        if (queue->backPtr > queue->endPtr) {
            queue->backPtr = queue->startPtr;
        }
        (void)memcpy(queue->backPtr, item, queue->itemNbOctets);
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
        queue->frontPtr = &queue->frontPtr[-queue->itemNbOctets];
        if (queue->frontPtr < queue->startPtr) {
            queue->frontPtr = queue->endPtr;
        }
        (void)memcpy(queue->frontPtr, item, queue->itemNbOctets);
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
        (void)memcpy(item, queue->frontPtr, queue->itemNbOctets);
        queue->frontPtr = &queue->frontPtr[queue->itemNbOctets];
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
        (void)memcpy(item, queue->backPtr, queue->itemNbOctets);
        queue->backPtr = &queue->backPtr[-queue->itemNbOctets];
        if (queue->backPtr < queue->startPtr) {
            queue->backPtr = queue->endPtr;
        }
    }

    assert(isConsistent(queue));

    return success;
}
