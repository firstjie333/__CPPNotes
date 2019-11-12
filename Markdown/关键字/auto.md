## auto

1. 必须有初值
2. 编译器==会动忽略顶层const==

```cpp
const int a = 10;
auto b = a;
b = 20; 
std::cout <<"a="<<", b="<<b<<std::endl; 

const auto c = a;
std::cout <<"can't change c"<<std::endl;
```



3. ==数组类型 会推断为指针类型，除非被声明为引用==

```cpp
int a[10];
auto b = a;
std::cout << typeid(b).name()<<std::endl;
auto &c = a;
std::cout << typeid(c).name()<<std::endl;
```



4. ==不能自动推导出顶层的CV-qualifiers和引用类型，==除非显示声明

```cpp
int i = 10;
int &j = i;
auto a = j;
a = 20;
std::cout <<"a="<<a<<", j="<<j<<", i="<<i<<std::endl;


auto &b = j;
b = 30; 
std::cout <<"b="<<b<<", j="<<j<<", i="<<i<<std::endl;
```





## typeid

1. ==是操作符，不是函数==。
2. ==有虚函数，返回的是运行时的类型==
3. ==没有虚函数，返回的是编译时的类型==

运行时获知变量类型名称，可以使用 typeid(变量).name()，但是不同机器输出结果不一定一致

## RTTI（Run-Time Type Identification)-运行时类型识别

1. 它使程序能够获取由基指针或引用所指向的对象的实际派生类型，即允许“用指向基类的指针或引用来操作对象”的程序能够获取到“这些指针或引用所指对象”的实际派生类型。

在揭开typeid神秘面纱之前，我们先来了解一下RTTI（Run-Time Type Identification，运行时类型识别），它使程序能够获取由基指针或引用所指向的对象的实际派生类型，即允许“用指向基类的指针或引用来操作对象”的程序能够获取到“这些指针或引用所指对象”的实际派生类型。

2. 在C++中，为了支持RTTI提供了两个操作符：dynamic_cast和typeid

- ==如果表达式的类型是类类型且至少包含有一个虚函数，则typeid操作符返回表达式的动态类型，需要在运行时计算；== 
- ==否则，typeid操作符返回表达式的静态类型，在编译时就可以计算。==

ISO C++标准并没有确切定义type_info，它的  确切定义编译器相关的，但是标准却规定了其实现必需提供如下四种操作（在之后的章节中我会来分析type_info类文件的源码）

```cpp
t1 == t2	如果两个对象t1和t2类型相同，则返回true；否则返回false
t1 != t2	如果两个对象t1和t2类型不同，则返回true；否则返回false
t.name()	返回类型的C-style字符串，类型名字用系统相关的方法产生1
t1.before(t2)	返回指出t1是否出现在t2之前的bool值
```

**type_info的name成员函数返回C-style的字符串，用来表示相应的类型名，但务必注意这个返回的类型名与程序中使用的相应类型名并不一定一致（往往如此，见后面的程序），这具体由编译器的实现所决定的，标准只要求实现为每个类型返回唯一的字符串。**


###  示例1-基本数据类型

下表列出了使用typeid操作符的表达式的值

```cpp
int a;
double b;
char * c;
long d;
运算	描述
typeid(a) == typeid(int)	true
typeid(a) == typeid(float)	false
typeid(a) == typeid(int *)	false
typeid(b) == typeid(double)	true
typeid(b) == typeid(float)	false
typeid(b) == typeid(long double)	false
typeid(c) == typeid(char *)	true
typeid(c) == typeid(char)	false
typeid(c) == typeid(string)	false
typeid(d) == typeid(long)	true
typeid(d) == typeid(int)	false
```



==操作符typeid返回的是一个type_info类（用于描述数据类型的一个系统类）对象的引用。这个操作符可以用于表达式和类型名（包括自定的数据类型，比如类）==。

### 示例2-类对象

```cpp
class base
{
public :
    void m(){cout<<"base"<<endl;}
};
class derived : public base
{
public:
    void m(){cout<<"derived"<<endl;}
};
```


假设我们根据例2中定义的两个类来定义如下指针：

base * p = new derived;

下表将给出使用typeid操作符的结果。

```cpp
typeid(p) == typeid(base)	true
typeid(p) == typeid(derived)	false
typeid(p) == typeid(base)	true
typeid(p) == typeid(derived)	false
```



对于表达式typeid(p)，同样，因为p是base*类型的指针，因此typeid(p) == typeid(base*)为真，而typeid(p) == typeid(derived*)为假。而对于表达式typeid(*p)，由于此时的基类不具有多态性，因而*p将会采用编译期类型来计算，编译期*p是base对象，因此表达式typeid(*p) == typeid(derived)为假，typeid(*p) == typeid(base)为真。

### 示例3-带虚函数的基类

```cpp
class base
{
public :
    virtual void m(){cout<<"base"<<endl;}
};
class derived : public base
{
public:
    void m(){cout<<"derived"<<endl;}
};
```


假设我们如本例所示定义了两个类base类和derived类，基于这两个类定义，我们定义指针如下：

base * p = new derived;

下表将给出使用typeid操作符的结果。

```
typeid(p) == typeid(base)	true
typeid(p) == typeid(derived)	false
typeid(p) == typeid(base)	false
typeid(p) == typeid(derived)	true
```

对于表达式typeid(p)，因为p是base*类型的指针，因此typeid(p) == typeid(base*)为真，而typeid(p) == typeid(derived*)为假。而对于表达式typeid(*p)，因为base类具有多态性，因而在计算typeid(*p)时会根据运行时p所指向的实际类型去计算，而本例中p指向的是派生类对象，因此表达式typeid(*p) == typeid(derived)为真，typeid(*p) == typeid(base)为假。

