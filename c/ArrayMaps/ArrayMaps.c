#include <string.h>
#include "ArrayMaps.h"

static const size_t itemSize = sizeof(ArrayMaps_Item_T);

static inline bool searchInsertion(
    const ArrayMaps_Item_T* items,
    uint32_t key,
    size_t nbItems,
    size_t* index
){
    bool success = false;
    size_t low = 0;
    size_t nbItemsLeft = nbItems;
    size_t ret = 0;
    size_t mid;
    uint32_t keyMid;
    while (nbItemsLeft > 0UL) {
        mid = low + (nbItemsLeft / 2UL);
        keyMid = items[mid].key;
        if (key < keyMid) {
            ret = mid;
        } else if (keyMid < key) {
            low = mid + 1UL;
            nbItemsLeft--;
            ret = low;
        } else {
            success = true;
            ret = mid;
            break;
        }
        nbItemsLeft /= 2UL;
    }
    *index = ret;
    return success;
}

void ArrayMaps_initialize(
    ArrayMaps_Map_T* map,
    ArrayMaps_Item_T* itemBuffer,
    size_t maxNbItems
){
    *map = (ArrayMaps_Map_T){
        .items = itemBuffer,
        .maxNbItems = maxNbItems,
        .nbItems = 0
    };
}

bool ArrayMaps_insert(
    ArrayMaps_Map_T* map,
    uint32_t key,
    uint32_t value
){
    const ArrayMaps_Item_T item = {
        .key = key,
        .value = value
    };
    size_t index;
    bool success;
    bool exists = searchInsertion(
        map->items, 
        key, 
        map->nbItems,  
        &index);
    if(exists){
       //.Replacing an existing item.
       map->items[index] = item;
       success = true; 
    } else {
        // Doesn't exist yet, a new entry needs to be inserted.
        success = map->nbItems < map->maxNbItems;
        if(success){
            if(index < map->nbItems){
                size_t nbItemsAfter = map->nbItems - index;
                (void)memmove(
                    &map->items[index + 1UL],
                    &map->items[index],
                    nbItemsAfter * itemSize);
            }
            map->items[index] = item;
            map->nbItems++;
        }
    }
    return success;
}

bool ArrayMaps_delete(
    ArrayMaps_Map_T* map,
    uint32_t key
){
    size_t index;
    bool success = searchInsertion(
        map->items, 
        key, 
        map->nbItems,  
        &index);
    if(success){
        if(index < (map->nbItems - 1UL)){
            size_t nbItemsAfter = map->nbItems - index - 1UL;
            (void)memmove(&map->items[index], &map->items[index + 1UL], nbItemsAfter * itemSize);
        }
        map->nbItems--;
    }
    return success;
}

bool ArrayMaps_find(
    const ArrayMaps_Map_T* map,
    uint32_t key,
    uint32_t* value
){
    size_t index;
    bool success = searchInsertion(
        map->items,
        key,
        map->nbItems,
        &index);
    if(success){
        *value = map->items[index].value;
    }
    return success;
}
