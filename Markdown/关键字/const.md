## const

1. 修饰变量：在初始化是必须赋值

2. 修饰引用：

   1. 引用类型必须与其所引用的对象的类型一致。==（但允许一个常量引用绑定到非常量对象上，即：不能通过该引用改变引用对象的值，但是该对象可以被其他途径改变）==

   ```cpp
   // const reference 
   int a=0;
   int &b =a;
   const int &c = a; // 常用引用
   b = 2;
   std::cout<<"a="<<a<<", b="<<b<<", c="<<c<<std::endl; // output 2 2 2
   
   
   const int d = 5;
   int &e = d; // error 
   ```

   

3. 修饰指针：

   - 指向常量的指针：==(1)仅仅要求不能通过该指针去改变对象的值，(2)但没有规定那个对象的值不能被其他途径改变==

   ```cpp
       
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
       
   ```

   - 常量指针（const pointer） ==* 放在const 关键字之前==：是一个常量对象，所以必须要初始化，而且一旦初始化后，他的值就不能改变，他的值就是一个地址，就是说他里面存储的地址不能变，但其他地址里的内容可以改变。

   ```cpp
   int a = 1;
   const int b =2;
   int * const pa = &a;
   int const * const pb = &b;
   
   std::cout <<"a="<<a<<", b="<<b<<std::endl;    
   *pa = 3;
   std::cout <<"a="<<a<<", b="<<b<<std::endl;  
   ```

   

4. ==顶层const（top level const）==：指针本身是一个对象，指针本身是一个const。引申：任意的对象是常量 如：const int a = 0；

5. ==底层const（low level const）：指针对指向的对象是一个const==

```cpp
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
```



## constexpr 常量表达式

1. ==值不会改变，且编译过程中就能得到计算结果的表达式==

   ```cpp
   const int a = 1; //是常量表达式
   const int b = a +1; //是常量表达式
   
   int c = 0; //不是常量表达式
   const int d = get_size(); //不是常量表达式，运行时才知道
   ```

2. C++11的规定，运行将变量声明为constexpr。目的是让编译器来检查验证该变量是不是一个常量表达式。以便虽然你想定义一个常量表达式，但是const int d = get_size(); 确是在运行过程中值才被确定。
3. 





## const 和 constexpr

1. const 变量的初始化可以延迟到运行时，而 constexpr 变量必须在编译时进行初始化。
   所有constexpr对象都是const的，但是不是所有的const对象都是constexpr的。

