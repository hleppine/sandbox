#ifndef COMMONS_H
#define COMMONS_H

#define ARRAY_SIZE(X) (sizeof((X))/sizeof((X)[0]))

#define COMMONS__JOIN(A, B) A##B // cppcheck-suppress misra-c2012-20.10

static inline uint8_t* Commons_toBytePtr(void* ptr){
    // No alignment issues possible when using a byte pointer.
    return (uint8_t*)ptr; // cppcheck-suppress misra-c2012-11.5
}

#endif /* COMMONS_H */
