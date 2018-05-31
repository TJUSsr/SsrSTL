//
// Created by Monster on 2018/5/29.
//
#include "string_ssr.h"

namespace SSRSTL {
    /*
     * 首先定义string_ssr的私有函数
     */
    void string_ssr::moveData(string_ssr& str){
        start_=str.start_;
        finish_=str.finish_;
        endOfStorage_=str.endOfStorage_;
        str.start_=str.finish_=str.endOfStorage_=0;
    }
    
    string_ssr::size_type string_ssr::getNewCapacity(size_type len) const{
        auto oldCapacity=capacity();
        auto lengthAppend=SSRSTL::max(len,oldCapacity);
        return oldCapacity+lengthAppend;
    }
    
    string_ssr::iterator string_ssr::insert_aux_filln(iterator position, size_type n, const_reference value){
        auto newCapacity=getNewCapacity(n*sizeof(value_type));
        auto newStart=dataAlloc::allocate(newCapacity);
        auto newFinish=SSRSTL::uninitialized_copy(start_,position,newStart);
        newFinish=SSRSTL::uninitialized_fill_n(newFinish, n, value);
        auto res=newFinish;
        newFinish=SSRSTL::uninitialized_copy(position, finish_, newFinish);
        
        destroyAndDeallocate();
        start_=newStart;
        finish_=newFinish;
        endOfStorage_=start_+newCapacity;
        return res;
    }
    
    void string_ssr::allocateAndFillN(size_type n, value_type c){
        start_=dataAlloc::allocate(n*sizeof(value_type));
        finish_=SSRSTL::uninitialized_fill_n(start_, n, c);
        endOfStorage_=start_+n*sizeof(value_type);
    }
    
    void string_ssr::string_ssr_aux(size_type n, value_type c, std::true_type){
        allocateAndFillN(n,c);
        
    }
    
    string_ssr::size_type string_ssr::find_aux(const_iterator it, size_type position, size_type lengthOfS,int cond) const {
        size_type i, j;
        for(i=position;i!=cond;++i){
            for(j=0;j!=lengthOfS;++j){
                if(*(begin()+i+j)!=it[j])
                    break;
            }
            if(j==lengthOfS)
                return i;
        }
        return npos;
    }
    
    string_ssr::size_type string_ssr::rfind_aux(const_iterator cit, size_type position, size_type lengthOfS, int cond) const{
        int i,j;
        for(i=position+lengthOfS;i>=cond;--i){
            for(j=0;j!=lengthOfS;++j){
                if(*(begin()+i+j)!=cit[j])
                    break;
            }
            if(j==lengthOfS)
                return i;
        }
        return npos;
    }
    
    int string_ssr::compare_aux(size_type position, size_type len, const_iterator cit, size_type subpos, size_type sublen) const{
        size_t i,j;
        for(i=0,j=0;i!=len&&j!=sublen;++i,++j){
            if((*this)[position+i]<cit[subpos+j])
                return -1;
            else if((*this)[position+i]>cit[subpos+j])
                return 1;
        }
        //如果某一序列已到达结尾，更长的序列有更大的字典序
        if(i==len&&j==sublen)
            return 0;
        else if(i==len)
            return -1;
        else
            return 1;
    }
    
    bool string_ssr::isContained(value_type ch, const_iterator first, const_iterator last) const{
        for(auto cit=first;cit!=last;++cit){
            if(*cit==ch)
                return true;
        }
        return false;
    }
    
    void string_ssr::destroyAndDeallocate(){
        dataAlloc::destroy(start_,finish_);
        dataAlloc::deallocate(start_,capacity());
    }
    
    //因为有的函数含有npos，所以利用这个函数来进行判断输入的参数为缺省的npos还是真实参数
    string_ssr::size_type string_ssr::changeVarWhenEqualNPOS(size_type var, size_type minuend, size_type minue) const{
        return (var==npos?minuend-minue:var);
    }
    
    /*
     * 有参数的构造函数
     */
    string_ssr::string_ssr(const string_ssr& str,size_type position, size_type len){
        len=changeVarWhenEqualNPOS(len, str.size(), position);
        allocateAndCopy(str.begin()+position, str.begin()+position+len);
    }
    
    string_ssr::string_ssr(const_iterator s){
        allocateAndCopy(s, s+strlen(s));
    }
    
    string_ssr::string_ssr(const_iterator s, size_type n){
        allocateAndCopy(s, s+n);
    }
    
    string_ssr::string_ssr(size_type n, value_type c){
        allocateAndFillN(n, c);
    }
    
    /*
     * 复制构造函数
     */
    string_ssr::string_ssr(const string_ssr& str){
        allocateAndCopy(str.start_, str.finish_);
    }
    /*
     * 移动构造函数
     */
    string_ssr::string_ssr(string_ssr&& str){
        moveData(str);
    }
    /*
     * 重栽=运算符
     */
    string_ssr& string_ssr::operator=(const string_ssr& str){
        if(this!=&str){
            destroyAndDeallocate();
            allocateAndCopy(str.start_, str.finish_);
        }
        return *this;
    }
    string_ssr& string_ssr::operator=(string_ssr&& str){
        if(this!=&str){
            moveData(str);
        }
        return *this;
    }
    string_ssr& string_ssr::operator=(const_iterator s){
        destroyAndDeallocate();
        allocateAndCopy(s, s+strlen(s));
        return *this;
    }
    string_ssr& string_ssr::operator=(value_type c){
        destroyAndDeallocate();
        allocateAndFillN(1, c);
        return *this;
    }
    
    //析构函数
    string_ssr::~string_ssr(){
        destroyAndDeallocate();
    }
    
    /*
     * 容量相关的函数，clear(), resize(), reserve(), shrink_to_fit()
     */
    void string_ssr::clear(){
        dataAlloc::destroy(start_,finish_);
        start_=finish_;
    }
    void string_ssr::resize(size_type n){
        resize(n,value_type());
    }
    void string_ssr::resize(size_type n, value_type c){
        if(n<size()){
            dataAlloc::destroy(start_+n,finish_);
            finish_=start_+n;
        }else if(n>size()&&n<=capacity()){
            
        }else if(n>capacity()){
        }
    }
    
    
}

