#ifndef MEMORY_STDLIB_HPP
#define MEMORY_STDLIB_HPP

#include <cstdlib>

class Memory_Stdlib {
public:
    static void fill(void *ptr, int value, size_t num) {
        memset(ptr, value, num);
    }

    static void zero(void *ptr, size_t num) {
        memset(ptr, 0, num);
    }
};

#endif