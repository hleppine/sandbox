#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint32_t key;
    uint32_t value;
} ArrayMaps_Item_T;

typedef struct {
    ArrayMaps_Item_T* items;
    size_t maxNbItems;
    size_t nbItems;
} ArrayMaps_Map_T;


void ArrayMaps_initialize(
    ArrayMaps_Map_T* map,
    ArrayMaps_Item_T* itemBuffer,
    size_t maxNbItems
);

bool ArrayMaps_insert(
    ArrayMaps_Map_T* map,
    uint32_t key,
    uint32_t value
);
    
bool ArrayMaps_delete(
    ArrayMaps_Map_T* map,
    uint32_t key
);

bool ArrayMaps_find(
    const ArrayMaps_Map_T* map,
    uint32_t key,
    uint32_t* value
);
