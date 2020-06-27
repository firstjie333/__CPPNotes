

###  std::function、std::bind、std::placeholders

1.  三个特性都在functional文件中定义，故使用时需要“#include<functional>”

2. 类模版`std::function`是一种通用、多态的函数封装。

- 普通函数

- lambda表达式
- 函数指针
- 仿函数(functor 重载括号运算符实现)
- 类成员函数
- 静态成员函数

3. std::bind 函数将可调用对象(用法中所述6类)和可调用对象的参数进行绑定，==返回新的可调用对象(std::function类型==，参数列表可能改变)，返回的新的std::function可调用对象的参数列表根据bind函数实参中std::placeholders::_x从小到大对应的参数确定。

```cpp
void XXXXX::updateBounds(const Eigen::Vector3d &pt)
{
    typedef std::function<double(const double &, const double &)> Comp;
    auto updater = [](const Eigen::Vector3d &inPt, Eigen::Vector3d &outPt, Comp cmp)
    {
        outPt[0] = cmp(inPt[0], outPt[0]);
        outPt[1] = cmp(inPt[1], outPt[1]);
        outPt[2] = cmp(inPt[2], outPt[2]);
    };

    if (gridAnchor_ == Eigen::Vector3d{0, 0, 0} && gridUpBound_ == Eigen::Vector3d{0, 0, 0})
    {
        gridAnchor_ = pt;
        gridUpBound_ = gridAnchor_;
    }
    else
    {
        updater(pt, gridAnchor_,  [](const double &l, const double &r) -> double { return l < r ? l : r; });
        updater(pt, gridUpBound_, [](const double &l, const double &r) -> double { return l < r ? r : l; });
    }
}
```



### 函数对象

1. 如果一个类将`()`运算符重载为成员函数，这个类就称为函数对象类，这个类的对象就是函数对象。函数对象是一个对象，但是使用的形式看起来像函数调用，实际上也执行了函数调用，因而得名。
2. C++中，只要实现了`operator()`的类或者结构体，都可以称为函数对象，这样可以直接调用

```cpp
#include <iostream>
using namespace std;
class CAverage
{
public:
    double operator()(int a1, int a2, int a3)
    {  //重载()运算符
        return (double)(a1 + a2 + a3) / 3;
    }
};
int main()
{
    CAverage average;  //能够求三个整数平均数的函数对象
    cout << average(3, 2, 3);  //等价于 cout << average.operator(3, 2, 3);
    return 0;
}
```

```cpp
struct cmp {
    bool operator()(const int& a, const int& b) {
        return a > b;
    }
};

int main()
{
    int a[] = {2, 3, 5, 4, 2, 8, 9, 0};
    std::sort(a, a + 5, cmp());    // 算法中的使用
    std::priority_queue<int, std::vector<int>, cmp>que;  // 定义中的使用
    return 0;
}
```





模板函数

模板函数对象





### 函数指针

函数指针不能绑定到类的成员变量上面

1. 函数指针基础：

- 声明一个函数指针
- 获取函数的地址

- 使用函数指针来调用函数

```cpp
double cal(int);      //  函数声明
double (*pf)(int);    // 指针pf指向的函数， 输入参数为int,返回值为double 
pf = cal;             // 指针赋值
void estimate(int lines, double (*pf)(int));  // 函数指针作为参数传递 


double y = cal(5);   // 通过函数调用
double y = (*pf)(5);   // 通过指针调用 推荐的写法 
double y = pf(5);     // 这样也对， 但是不推荐这样写 
```

https://www.cnblogs.com/lvchaoshun/p/7806248.html

