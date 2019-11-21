#include <iostream>
#include <stdalign.h>


// 测试alignas 分配内存
struct alignas(32) Data1
{
    char a;
    short b;
    int c;
    float d;
    double e;
};


struct Data2
{
    char a;
    short b;
    int c;
    float d;
    double e;
};

#include <iostream>
#include <memory>
 
template <std::size_t N>
struct MyAllocator
{
    char data[N];
    void* p;
    std::size_t sz;
    MyAllocator() : p(data), sz(N) {}
    template <typename T>
    T* aligned_alloc(std::size_t a = alignof(T))
    {
        if (std::align(a, sizeof(T), p, sz))
        {
            T* result = reinterpret_cast<T*>(p);
            p = (char*)p + sizeof(T);
            sz -= sizeof(T);
            return result;
        }
        return nullptr;
    }
};
 
int main()
{
    // !step1 : Test alignas 
    Data1 data1;
    std::cout << sizeof(Data1) << std::endl;
    std::cout << alignof(Data1) << std::endl;

    std::cout << sizeof(Data2) << std::endl;
    std::cout << alignof(Data2) << std::endl;


    // !Test2 : 
    MyAllocator<64> a;

    // 分配一个 char
    char* p1 = a.aligned_alloc<char>();
    if (p1)
        *p1 = 'a';
    std::cout << "allocated a char at " << (void*)p1 << '\n';
    std::cout << sizeof( *p1) <<std::endl;
 
    // 分配一个 int
    int* p2 = a.aligned_alloc<int>();
    if (p2)
        *p2 = 1;
    std::cout << "allocated an int at " << (void*)p2 << '\n';
    std::cout << sizeof( *p2) <<std::endl;


    // 分配一个 int ，对齐于 32 字节边界
    int* p3 = a.aligned_alloc<int>(32);
    if (p3)
        *p3 = 2;
    std::cout << "allocated an int at " << (void*)p3 << " (32 byte alignment)\n";
    std::cout << sizeof( *p3) <<std::endl;


    // !Test3: 
    {
        int i = 10;
        int &j = i;
        auto a = j;
        a = 20;
        std::cout <<"a="<<a<<", j="<<j<<", i="<<i<<std::endl;


        auto &b = j;
        b = 30; 
        std::cout <<"b="<<b<<", j="<<j<<", i="<<i<<std::endl;
    }


    //! Test 4
    {
        const int a = 10;
        auto b = a;
        b = 20; 
        std::cout <<"a="<<", b="<<b<<std::endl; 

        const auto c = a;
        std::cout <<"can't change c"<<std::endl;
     
    }


    // !Test5 
    {
        int a[10];
        auto b = a;
        std::cout << typeid(b).name()<<std::endl;
        auto &c = a;
        std::cout << typeid(c).name()<<std::endl;
    }
    

    // const reference 
    {
        int a=0;
        int &b =a;
        const int &c = a;
        b = 2;
        std::cout<<"a="<<a<<", b="<<b<<", c="<<c<<std::endl;
    }


    {
        int a = 2;
        const int aa = 3;
        int *pa = &a;
        const int *pb = &a;
        const int *pbb = &aa;
        std::cout <<"pb="<<*pb<<", pbb="<<*pbb<<std::endl; 


        int c = 4;
        pb = &c;
        pbb = &c;
        std::cout <<"pb="<<*pb<<", pbb="<<*pbb<<std::endl; 


        c = 5;
        std::cout <<"pb="<<*pb<<", pbb="<<*pbb<<std::endl;    
    }



    {
        int a = 1;
        const int b =2;
        int * const pa = &a;
        int const * const pb = &b;

        std::cout <<"a="<<a<<", b="<<b<<std::endl;    
        *pa = 3;
        std::cout <<"a="<<a<<", b="<<b<<std::endl;   
    }


    
    {   
        int a = 0;
        const int b = 1; // 顶层

        int * const pa = &a; //顶层
        const int *  pa2 = &a;  //底层
        const int * const pb = &b; // 顶层 + 底层

        const int &ra = a; //底层
        const int &rb = b; //底层


        // 对于顶层const, 拷贝对象没关系
        a = b; //把顶层const b 拷贝给 非顶层const a

        pa2 = pb; // 把pb的地址赋值给pa2, pa2是底层的，pb可以忽略顶层，只考虑底层


        // 对于底层const, 必须具有相同的底层const资格，同时两个对象的数据类型必须要能转换
        // int *n = pa2; //错误
        

    }
    

}
