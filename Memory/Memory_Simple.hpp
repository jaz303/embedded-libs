#ifndef MEMORY_SIMPLE_HPP
#define MEMORY_SIMPLE_HPP

class Memory_Simple {
public:
    static void fill(void *ptr, int value, size_t num) {
        char *data = (char*)ptr;
        while (num--) {
            *(data++) = value;
        }
    }

    static void zero(void *ptr, size_t num) {
        char *data = (char*)ptr;
        while (num--) {
            *(data++) = 0;
        }
    }
};

#endif