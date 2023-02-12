#include <assert.h>
#include <stdio.h>
#include "ArrayMaps.h"

static void printMap(const ArrayMaps_Map_T* map){
    printf("Map:\n");
    for(size_t i = 0; i < map->nbItems; i++){
        printf("k=%d v=%d\n", map->items[i].key, map->items[i].value);
    }
}

int main() {
   
    ArrayMaps_Item_T buffer[10];
   
    ArrayMaps_Map_T map;
    
    bool success;
   
    ArrayMaps_initialize(
        &map,
        buffer,
        10);
        
    const uint32_t keys[] = {
        11, 100, 3, 90, 5,
        80, 7, 60, 9, 40
    };
    
    printMap(&map);
   
    for(int i=0; i<10; i++){
        uint32_t value = (uint32_t)i;
        success = ArrayMaps_insert(&map, keys[i], value);
        assert(success);
    }
    
    printMap(&map);
    
    for(int i=0; i<10; i++){
        uint32_t value;
        success = ArrayMaps_find(&map, keys[i], &value);
        assert(success);
    }
    
    success = ArrayMaps_delete(&map, 3);
    assert(success);
    
    success = ArrayMaps_delete(&map, 40);
    assert(success);
    
    success = ArrayMaps_delete(&map, 100);
 
    const uint32_t remainingKeys[] = {
        11, 90, 5,
        80, 7, 60, 9
    };
    
    for(int i=0; i<7; i++){
        uint32_t value;
        success = ArrayMaps_find(&map, remainingKeys[i], &value);
        assert(success);
    }
    
    printMap(&map);
    
    printf("Done\n");

    return 0;
}
