//
// Created by Administrator on 2018/5/8.
//
#include "alloc.h"
namespace SSRSTL{
    char* alloc::start_free=nullptr;
    char* alloc::end_free=nullptr;
    //贯彻了Cpp的RAII思想，用时资源初始化。
    alloc::obj* alloc::free_list[alloc::SsrFreeLists::NumOfFreeLists]={nullptr};

    void* alloc::allocate(size_t bytes) {
        if(bytes>SsrMaxBytes::Maxbytes)//申请大内存直接调用malloc()
            return malloc(bytes);
        size_t index=FREELIST_INDEX(bytes);
        obj* list=free_list[index];
        if(list){//该内存块存在的话直接返回
            free_list[index]=list->next;
            return list;//注意这里发生了隐式的类型转换，list原本是指向obj类型的指针，返回一个void指针
        }else{//若该块内存不存在，则调用refill()函数来进行相应的处理
            return refill(Round_Up(bytes));
        }
    }
    void alloc::deallocate(void *ptr, size_t bytes) {
        if(bytes>SsrMaxBytes::Maxbytes)//大块内存直接调用free()函数来释放
            //free()函数之所以只需要一个指针便能释放内存，其实是关于该块内存大小的一些信息
            //被存储在该指针前几个字节的内存中，所以free()函数只需要一个指针便可以完成内存释放
            free(ptr);
        else{//小块内存直接返回给内存池
            size_t index=FREELIST_INDEX(bytes);
            //利用static_cast<>()完成强制类型转换
            obj* temp= static_cast<obj*>(ptr);
            temp->next=
            free_list[]

        }
    }
    void* alloc::reallocate(void *ptr, size_t old_sz, size_t new_sz) {

    }
    void* alloc::refill(size_t n) {

    }
    char* alloc::chunk_alloc(size_t size, size_t &nobjs) {

    }
}

