#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include "Commons.h"

/*
 * Usage: define the macros (see examples below):
 *  - GENERIC_STACKS__ITEM_T
 *  - GENERIC_STACKS__TAG
 * and include this file.
 */

#ifndef GENERIC_STACKS__ITEM_T
#define GENERIC_STACKS__ITEM_T int
#endif

#ifndef GENERIC_STACKS__TAG
#define GENERIC_STACKS__TAG Int
#endif

// Define helper macros:

#define GENERIC_STACKS__IDENT(ROOT, NAME) COMMONS__JOIN(ROOT, NAME)

#define GENERIC_STACKS__ROOT GENERIC_STACKS__IDENT(Stacks, GENERIC_STACKS__TAG)

#define GENERIC_STACKS__STACK_T \
    GENERIC_STACKS__IDENT(GENERIC_STACKS__ROOT, _Stack_T)
#define GENERIC_STACKS__INITIALIZE \
    GENERIC_STACKS__IDENT(GENERIC_STACKS__ROOT, _initialize)
#define GENERIC_STACKS__NB_ITEMS \
    GENERIC_STACKS__IDENT(GENERIC_STACKS__ROOT, _nbItems)
#define GENERIC_STACKS__PUSH GENERIC_STACKS__IDENT(GENERIC_STACKS__ROOT, _push)
#define GENERIC_STACKS__POP GENERIC_STACKS__IDENT(GENERIC_STACKS__ROOT, _pop)
#define GENERIC_STACKS__PEEK GENERIC_STACKS__IDENT(GENERIC_STACKS__ROOT, _peek)

// Generic stack implementation:

typedef struct {
    GENERIC_STACKS__ITEM_T* buffer;
    size_t max_nb_items;
    size_t nb_items;
} GENERIC_STACKS__STACK_T;

static inline void GENERIC_STACKS__INITIALIZE(GENERIC_STACKS__STACK_T* stack,
                                              GENERIC_STACKS__ITEM_T buffer[],
                                              size_t max_nb_items) {
    assert(stack != NULL);
    assert(buffer != NULL);
    *stack = (GENERIC_STACKS__STACK_T){
        .buffer = buffer, .max_nb_items = max_nb_items, .nb_items = 0};
}

static inline size_t GENERIC_STACKS__NB_ITEMS(
    const GENERIC_STACKS__STACK_T* stack) {
    assert(stack != NULL);
    return stack->nb_items;
}

static inline bool GENERIC_STACKS__PUSH(GENERIC_STACKS__STACK_T* stack,
                                        const GENERIC_STACKS__ITEM_T* item) {
    assert(stack != NULL);
    assert(item != NULL);
    bool success = stack->nb_items < stack->max_nb_items;
    if (success) {
        stack->buffer[stack->nb_items] = *item;
        stack->nb_items++;
    }
    return success;
}

static inline bool GENERIC_STACKS__POP(GENERIC_STACKS__STACK_T* stack,
                                       GENERIC_STACKS__ITEM_T* item) {
    assert(stack != NULL);
    assert(item != NULL);
    bool success = stack->nb_items > 0UL;
    if (success) {
        stack->nb_items--;
        *item = stack->buffer[stack->nb_items];
    }
    return success;
}

static inline bool GENERIC_STACKS__PEEK(const GENERIC_STACKS__STACK_T* stack,
                                        GENERIC_STACKS__ITEM_T* item) {
    assert(stack != NULL);
    assert(item != NULL);
    bool success = stack->nb_items > 0UL;
    if (success) {
        *item = stack->buffer[stack->nb_items - 1UL];
    }
    return success;
}
