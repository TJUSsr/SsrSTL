//
// Created by monster on 18-5-3.
//
#ifndef SSRSTL_ALLOC_H
#define SSRSTL_ALLOC_H

#include <cstdlib>

/*
 * alloc基本思想，大于128字节的内存利用malloc，小于128字节的内存用维护一个内存池，每块内存的字节数差值为SsrSize::Size
*/
namespace SSRSTL{
    class alloc{
    public:
        static void* allocate(size_t bytes);
        static void deallocate(void* ptr,size_t bytes);
        static void *reallocate(void* ptr, size_t old_sz, size_t new_sz);
    private:
        //内存池所维护的小块内存的每块之间的差值
        enum SsrSize{Size=8};
        //小块内存的内存上限
        enum SsrMaxBytes{Maxbytes=128};
        //共有SsrFreeLists::NumOfFreeLists种类型的小块内存
        enum SsrFreeLists{ NumOfFreeLists = (SsrMaxBytes::Maxbytes / SsrSize::Size)};
        //小块内存不够时所增加的内存块数
        enum SsrObjs{NumOfObjs=20};
        union obj{
            obj* next;
            char client[1];
        };
        static obj* free_list[SsrFreeLists::NumOfFreeLists];
        static char* start_free;
        static char* end_free;
        static size_t heap_size;

        //Round_Up()函数，根据所需bytes的内存来分配相应的小块内存，即向上取最近值
        static size_t Round_Up(size_t bytes){
            return ((bytes+SsrSize::Size-1)&~(SsrSize::Size-1));
        }
        //FREELIST_INDEX()函数，根据所需的内存大小bytes得到相应的free_list上的index
        static size_t FREELIST_INDEX(size_t bytes){
            return ((bytes+SsrSize::Size-1)/(SsrSize::Size-1));
        }

        //refill()函数，当free_list上的某块大小的内存没有时，利用该函数申请
        static void* refill(size_t n);
        static char* chunk_alloc(size_t size, size_t& nobjs);
    };
}
#endif //SSRSTL_ALLOC_H
