//
// Created by Administrator on 2018/5/8.
//
#include <iostream>
#include "alloc.h"
namespace SSRSTL{
    char* alloc::start_free=0;
    char* alloc::end_free=0;
    size_t alloc::heap_size=0;
    //贯彻了Cpp的RAII思想，用时资源初始化。
    alloc::obj* alloc::free_list[alloc::SsrFreeLists::NumOfFreeLists]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    void* alloc::allocate(size_t bytes) {
        if(bytes>SsrMaxBytes::Maxbytes)//申请大内存直接调用malloc()
            return malloc(bytes);
        size_t index=FREELIST_INDEX(bytes);
        obj* list=free_list[index];

        if(list!=0){//该内存块存在的话直接返回
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
            temp->next=free_list[index];
            free_list[index]=temp;
        }
    }
    void* alloc::reallocate(void *ptr, size_t old_sz, size_t new_sz) {
        //当容器需要扩容时会调用reallocate()函数
        deallocate(ptr,old_sz);
        ptr=allocate(new_sz);
        return ptr;
    }
    void* alloc::refill(size_t n) {
        size_t nobjs=SsrObjs ::NumOfObjs;
        //从内存池取内存
        char* ptr=chunk_alloc(n,nobjs);
        obj** my_free_list= 0;
        obj* res= 0;
        obj* current_obj= 0;
        obj* next_obj= 0;
        if(nobjs==1){
            return ptr;
        }else{
            my_free_list=free_list+FREELIST_INDEX(n);
            res=(obj *) ptr;
            *my_free_list=next_obj=(obj*)(ptr+n);
            //将多余的内存放入free_list
            for(int i=1;;++i){
                current_obj=next_obj;
                next_obj=(obj*)((char*)next_obj+n);
                if(i==nobjs-1){
                    current_obj->next= 0;
                    break;
                }else{
                    current_obj->next=next_obj;
                }
            }
            return res;
        }
    }
    //第二个参数之所以为引用是因为建议申请20个内存块，但是不一定能够申请到20个，利用直接过参数来
    //告知调用者最终申请了多少内存块
    //chunk_alloc()函数十分关键，是理解整个内存池的关键
    /*现在假如要分配一块32B的内存，但free_list[3]所指向的指针为NULL，即空闲链表free_list中没有32B的内存，
     * 这时候就需要通过下面的_chunk_alloc来分配内存给free_list了。
     * 默认每次分配是分配20个大小为32B的内存。
     * 即_chunk_alloc第二个参数传入值为20，但系统不一定能分配20个，所以用的是引用。
     * _chunk_malloc主要分三种情况来处理：
     * 1、现有内存池容量满足你的需求：32B * 20个，直接返回给你这么大一块内存；
     * 2、现有内存池容量不能满足这么多个，即20个，但可以满足1个，那先给你free_list对应项分配一个32B再说；
     * 3、现有内存池容量连一个都满足不了，那只能利用malloc从堆中分配内存。
     * 从堆中分配内存时，首先把当前内存池中剩余的一些零碎内存赋给free_list中；
     * 然后从堆中malloc内存，修改内存池的_start_free、_end_free指针。
     * (这两个指针分别指向内存池的起始地址和结束地址)。
     * 再然后递归调用_chunk_malloc函数。
     */
    char* alloc::chunk_alloc(size_t bytes, size_t &nobjs) {
        char* res= 0;
        size_t totalbytes=bytes*nobjs;
        size_t bytes_left=end_free-start_free;
        if(bytes_left>=totalbytes){
            //内存池剩余空间满足需求
            res=start_free;
            start_free+=totalbytes;
            return res;
        }else if(bytes_left>=bytes){
            //内存池剩余内存无法满足全部需求
            //只能满足一个或以上的内存块需求
            nobjs=bytes_left/bytes;
            totalbytes=nobjs*bytes;
            res=start_free;
            start_free+=totalbytes;
            return res;
        }else{
            //内存池剩余内存一个内存块都无法满足
            size_t bytes_to_get=2*totalbytes+Round_Up(heap_size>>4);
            if(bytes_left>0){
                obj** my_free_list=free_list+FREELIST_INDEX(bytes_left);
                ((obj*)start_free)->next=*my_free_list;
                *my_free_list=(obj*) start_free;
            }
            start_free=(char*) malloc(bytes_to_get);
            if(!start_free){
                //malloc()申请内存失败
                obj** my_free_list= 0;
                obj* p= 0;
                for(int i=0;i<=SsrMaxBytes::Maxbytes;i+=SsrSize::Size){
                    my_free_list=free_list+FREELIST_INDEX(i);
                    p=*my_free_list;
                    if(p!= 0){
                        *my_free_list=p->next;
                        start_free=(char*)p;
                        end_free=start_free+i;
                        return chunk_alloc(bytes,nobjs);
                    }
                }
            }
            heap_size+=bytes_to_get;
            end_free=start_free+bytes_to_get;
            return chunk_alloc(bytes,nobjs);
        }
    }
}