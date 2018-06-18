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
    void string_ssr::reserve(size_type n){
        if(n<=capacity())
            return;
        iterator newStart=dataAlloc::allocate(n);
        iterator newFinish=SSRSTL::uninitialized_copy(begin(), end(), newStart);
        destroyAndDeallocate();
        start_=newStart;
        finish_=newFinish;
        endOfStorage_=newStart+n;
    }
    void string_ssr::shrink_to_fit(){
        dataAlloc::deallocate(finish_,endOfStorage_-finish_);
        endOfStorage_=finish_;
    }
    /*
     * 重栽的各种运算符[],=,+=,<,<=,>,>=,!=,==,<<,>>
     */
    string_ssr::reference string_ssr::operator[](size_type position){
        return *(start_+position);
    }
    string_ssr::const_reference string_ssr::operator[](size_type position) const{
        return *(start_+position);
    }
    string_ssr& string_ssr::operator+=(const string_ssr& str){
        insert(size(),str);
        return *this;
    }
    string_ssr& string_ssr::operator+=(const_iterator s){
        insert(size(), s);
        return *this;
    }
    string_ssr& string_ssr::operator+=(value_type c){
        insert(end(),c);
        return *this;
    }
    //重栽输出运算符
    std::ostream& operator<<(std::ostream& out, const string_ssr& str){
        for(const auto c:str)
            out<<c;
        return out;
    }
    //重栽输入运算符
    std::istream& operator>>(std::istream& in, string_ssr& str){
        char c;
        string_ssr::size_type oldsize=str.size(), index=0;
        bool hasPrevBlank =false;
        while(in.get(c)){
            if(c==' '||c=='\n')
                hasPrevBlank=true;
            else
                break;
        }
        in.putback(c);
        str.clear();
        while(in.get(c)){
            if(c!=EOF&&!isblank(c)&&c!='\n') {
                str.push_back(c);
            }else
                break;
        }
        return in;
    }
    //重栽加号运算符
    string_ssr operator+(const string_ssr&lhs, const string_ssr&rhs){
        auto res=string_ssr(lhs);
        return res+=rhs;
    }
    string_ssr operator+(const string_ssr &lhs, string_ssr::const_iterator rhs) {
        auto res=string_ssr(lhs);
        return res+=rhs;
    }
    string_ssr operator+(string_ssr::const_iterator lhs, const string_ssr &rhs) {
        auto res=string_ssr(lhs);
        return res+=rhs;
    }
    string_ssr operator+(const string_ssr &lhs, string_ssr::value_type rhs) {
        auto res=string_ssr(lhs);
        return res+=rhs;
    }
    string_ssr operator+(string_ssr::value_type lhs, const string_ssr &rhs) {
        auto res=string_ssr(1,lhs);
        return res+=rhs;
    }
    //重栽==运算符
    bool operator==(const string_ssr& lhs, const string_ssr& rhs){
        if(lhs.size()==rhs.size()){
            for(auto lit=lhs.begin(),rit=rhs.begin();lit!=lhs.end()&&rit!=rhs.end();++lit,++rit){
                if(*lit!=*rit)
                    return false;
            }
            return true;
        }
        return false;
    }
    bool operator==(const string_ssr &lhs, string_ssr::const_iterator rhs) {
        string_ssr::size_type len=strlen(rhs);
        if(lhs.size()==len){
            auto p=rhs;
            for(auto lit=lhs.begin();lit!=lhs.end()&&p!=rhs+len;++lit,++p){
                if(*lit!=*p)
                    return false;
            }
            return true;
        }
        return false;
    }
    bool operator==(string_ssr::const_iterator lhs, const string_ssr& rhs){
        return rhs==lhs;
    }
    //重栽!=运算符
    bool operator!=(const string_ssr& lhs, const string_ssr& rhs){
        return !(lhs==rhs);
    }
    bool operator!=(const string_ssr &lhs, string_ssr::const_iterator rhs) {
        return !(lhs==rhs);
    }
    bool operator!=(string_ssr::const_iterator lhs, const string_ssr& rhs){
        return !(lhs==rhs);
    }
    namespace {
        template <class Iterator1, class Iterator2>
        bool lessEqual_aux(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2){
            for(;first1!=last1&&first2!=last2;++first1,++first2){
                if(*first1<*first2)
                    return true;
                else if(*first1>*first2)
                    return false;
            }
            if(first1==last1)
                return true;
            else
                return false;
        };
    }
    //重栽<,>,<=,>=运算符
    bool operator<=(const string_ssr& lhs, const string_ssr& rhs){
        return lessEqual_aux(lhs.begin(),lhs.end(),rhs.begin(),rhs.end());
    }
    bool operator<=(const string_ssr& lhs, string_ssr::const_iterator rhs){
        return lessEqual_aux(lhs.begin(),lhs.end(),rhs,rhs+strlen(rhs));
    }
    bool operator<=(string_ssr::const_iterator lhs, const string_ssr& rhs){
        return lessEqual_aux(lhs,lhs+strlen(lhs),rhs.begin(),rhs.end());
    }
    bool operator>(const string_ssr &lhs, const string_ssr &rhs) {
        return !(lhs<=rhs);
    }
    bool operator>(const string_ssr &lhs, string_ssr::const_iterator rhs) {
        return !(lhs<=rhs);
    }
    bool operator>(string_ssr::const_iterator lhs, const string_ssr& rhs){
        return !(lhs<=rhs);
    }
    namespace {
        template <class Iterator1, class Iterator2>
        bool greatEqual_aux(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2){
            for(;first1!=last1&&first2!=last2;++first1,++first2){
                if(*first1>*first2)
                    return true;
                else if(*first1<*first2)
                    return false;
            }
            if(first2==last2)
                return true;
            else
                return false;
        };
    }
    bool operator>=(const string_ssr& lhs, const string_ssr& rhs){
        return greatEqual_aux(lhs.begin(),lhs.end(),rhs.begin(),rhs.end());
    }
    bool operator>=(const string_ssr& lhs, string_ssr::const_iterator rhs){
        return greatEqual_aux(lhs.begin(),lhs.end(),rhs,rhs+strlen(rhs));
    }
    bool operator>=(string_ssr::const_iterator lhs, const string_ssr& rhs){
        return greatEqual_aux(lhs,lhs+strlen(lhs),rhs.begin(),rhs.end());
    }
    bool operator<(const string_ssr &lhs, const string_ssr &rhs) {
        return !(lhs>=rhs);
    }
    bool operator<(const string_ssr &lhs, string_ssr::const_iterator rhs) {
        return !(lhs>=rhs);
    }
    bool operator<(string_ssr::const_iterator lhs, const string_ssr& rhs){
        return !(lhs>=rhs);
    }
    //insert()函数
    string_ssr &string_ssr::insert(string_ssr::size_type position, const string_ssr &str) {
        insert(start_+position,str.begin(),str.end());
        return *this;
    }
    string_ssr &string_ssr::insert(string_ssr::size_type position, const string_ssr &str, string_ssr::size_type subpos, string_ssr::size_type sublen) {
        sublen = changeVarWhenEqualNPOS(sublen, str.size(), subpos);
        insert(start_+position,str.begin()+subpos,str.begin()+subpos+sublen);
        return *this;
    }
    string_ssr& string_ssr::insert(size_type position, const_iterator s) {
        insert(start_+position,s,s+strlen(s));
        return *this;
    }
    string_ssr& string_ssr::insert(size_type position, const_iterator s,size_type n) {
        insert(start_+position,s,s+n);
        return *this;
    }

    string_ssr &string_ssr::insert(string_ssr::size_type position, string_ssr::size_type n, string_ssr::value_type c) {
        insert(start_+position,n,c);
        return *this;
    }
    string_ssr::iterator string_ssr::insert(string_ssr::iterator p, string_ssr::size_type n, string_ssr::value_type c) {
        auto lengthOfleft=capacity()-size();
        if(n<=lengthOfleft){
            for(auto it=finish_-1;it>=p;--it){
                *(it+n)=*it;
            }
            SSRSTL::uninitialized_fill_n(p,n,c);
            finish_+=n;
            return p+n;
        }else{
            return insert_aux_filln(p,n,c);
        }
    }
    string_ssr::iterator string_ssr::insert(string_ssr::iterator p, string_ssr::value_type c) {
        return insert(p,1,c);
    }

    //append()函数
    string_ssr &string_ssr::append(const string_ssr &str) {
        *this+=str;
        return *this;
    }
    string_ssr &string_ssr::append(const string_ssr &str, string_ssr::size_type subpos, string_ssr::size_type sublen) {
        sublen=changeVarWhenEqualNPOS(sublen,str.size(),subpos);
        insert(size(),str,subpos,sublen);
        return *this;
    }
    string_ssr &string_ssr::append(string_ssr::const_iterator s) {
        *this+=s;
        return *this;
    }
    string_ssr &string_ssr::append(string_ssr::const_iterator s, string_ssr::size_type n) {
        insert(size(),s,n);
        return *this;
    }
    string_ssr &string_ssr::append(string_ssr::value_type c) {
        *this+=c;
        return *this;
    }
    string_ssr &string_ssr::append(string_ssr::size_type n, string_ssr::value_type c) {
        insert(size(),n,c);
        return *this;
    }
    //erase()函数
    //此处为前闭后开区间
    string_ssr::iterator string_ssr::erase(iterator first, iterator last) {
        size_type lengthTomove=finish_-last;
        for(auto i=0;i<lengthTomove;++i){
            *(first+i)=*(last+i);
        }
        dataAlloc::destroy(first+lengthTomove,finish_);
        finish_=first+lengthTomove;
        return first;
    }
    string_ssr& string_ssr::erase(size_type pos, size_type len) {
        len=changeVarWhenEqualNPOS(len,size(),pos);
        erase(begin()+pos,begin()+pos+len);
        return *this;
    }
    string_ssr::iterator string_ssr::erase(string_ssr::iterator p) {
        return erase(p,p+1);
    }
    //replace()函数
    string_ssr &string_ssr::replace(string_ssr::size_type position, string_ssr::size_type len, const string_ssr &str) {
        return replace(begin()+position,begin()+position+len,str.begin(),str.end());
    }

    string_ssr &string_ssr::replace(string_ssr::iterator it1, string_ssr::iterator it2, const string_ssr &str) {
        return replace(it1,it2,str.begin(),str.end());
    }

}

