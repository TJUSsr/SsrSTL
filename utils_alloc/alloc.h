//
// Created by monster on 18-5-3.
//
#ifndef SSRSTL_ALLOC_H
#define SSRSTL_ALLOC_H

#include <cstdlib>

namespace SSRSTL{
    class alloc{
    public:
        static void* allocate(size_t bytes);
        static void deallocate(void* ptr,size_t bytes);
        static void *reallocate(void* ptr, size_t old_sz, size_t new_sz);
    private:

    };
}


#endif //SSRSTL_ALLOC_H
