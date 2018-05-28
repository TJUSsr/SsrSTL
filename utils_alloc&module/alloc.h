//
// Created by monster on 18-5-3.
//
#ifndef SSRSTL_ALLOC_H
#define SSRSTL_ALLOC_H

#include <cstdlib>
#include <iostream>
#include "../utils_logs/logger.h"

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
        /*
         * 这个联合体理解较为困难，但是最终应用起来可以按照如下的意思去理解
         * obj* ptr
         * 则ptr，(void*)ptr, ptr->client, &ptr->next都是当前的内存块
         * ptr->next, (void*)(ptr->next) 是下一个内存块
         * 写了如下一段程序可以帮助理解
         *
int main() {
    union obj{
        obj* free_list_link;
        char client_data[1];
    };
    char mem[100] = { 0 };
    char mem1[100] = { 0 };

    //现在是每一块内存的开始均是一个union node结构
    //----------------------------------
    //| union obj | ....................
    // ----------------------------------
    union obj *p1 = (union obj *)mem; //用一个变量表示这个结构

    //p1->free_list_link 设置为下一个内存的起始段
    p1->free_list_link = (union obj *)mem1 ;

    //以下五个值的结果都是一样的
    cout <<"mem                        = " << (void *)mem << endl;
    cout <<"p1                         = " << p1 << endl;
    cout <<"(void*)p1                  = " << (void *)p1 << endl;
    cout <<"p1->client_data            = " << (void *)p1->client_data << endl;
    cout <<"&p1->free_list_link        = " << &(p1->free_list_link) << endl;

    cout<<endl;

    cout <<"p1->free_list_link         = " << p1->free_list_link << endl;
    cout <<"(void *)p1->free_list_link = " << (void *)p1->free_list_link << endl;
    cout <<"mem1                       = " << (void *)mem1 << endl;

    return 0;
}
         */
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
