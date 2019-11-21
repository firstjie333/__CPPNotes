### decltype

1. 推段表达式类型

```cpp
decltype(x) y 编译时，推导x的类型，并且作为y的类型
```

2. 与using/typedef 合用，用于定义类型

```cpp
sing size_t = decltype(sizeof(0));//sizeof(a)的返回值为size_t类型
using ptrdiff_t = decltype((int*)0 - (int*)0);
using nullptr_t = decltype(nullptr);


vector<int >vec;
typedef decltype(vec.begin()) vectype;
for (vectype i = vec.begin; i != vec.end(); i++)
{
  //...
}
```

3. 重用匿名

```cpp
struct 
{
    int d ;
    doubel b;
}anon_s;

decltype(anon_s) as ;//定义了一个上面匿名的结构体
```



4. **==泛型编程中结合auto，用于追踪函数的返回值类型==**(不明白)

这也是decltype最大的用途了

```cpp
template <typename _Tx, typename _Ty>
auto multiply(_Tx x, _Ty y)->decltype(_Tx*_Ty)
{
    return x*y;
}
```

5. 如果表达式是一个变量，会返回该变量的类型，并且包括（顶层const 和 引用在内）
6. 如果使用一个不加括号的变量会得到该变量类型；如果使用的多层括号表示，编译器会把他当做一个表达式，而变量是一种可以作为赋值语句左值的特殊表达式，所以这样的decltype会得到引用类型。 ==即：decltype((variable))永远是引用，而decltype(variable)只有当variable是引用时，才会是引用==

```cpp
const int a = 0;
const int &b = a;

decltype (a) x = 0; // x 是const int
decltype (b) y = x; // y 是const int & 引用，绑定对象为x
decltype (y) z;  // z 是const int &引用，需要要绑定一个对象才行
	
int i = 0;
decltype (i) m; // m是int
decltype((i)) n; // n是int & 引用
```





## decltype推导四规则

1. 如果e是一个没有带括号的标记符表达式或者类成员访问表达式，那么的decltype（e）就是e所命名的实体的类型。此外，如果e是一个被重载的函数，则会导致编译错误。
2. 否则 ，假设e的类型是T，如果e是一个将亡值，那么decltype（e）为T&&
3. 否则，假设e的类型是T，如果e是一个左值，那么decltype（e）为T&。
4. 否则，假设e的类型是T，则decltype（e）为T。

