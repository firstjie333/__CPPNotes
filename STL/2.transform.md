## transfrom

- std::transform在指定的范围内应用于给定的操作，并将结果存储在指定的另一个范围内。
- 要使用std::transform函数需要包含==<algorithm>头文件。==
- 两个声明：一个是对应于一元操作，一个是对应于二元操作
- op可以是==【函数指针】或【函数对象】或【lambda表达式】==
- std::transform支持in place，即result和first1指向的位置可以是相同的

```cpp

template <class InputIterator, class OutputIterator, class UnaryOperation>
  OutputIterator transform (InputIterator first1, InputIterator last1,
                            OutputIterator result, UnaryOperation op);
	
template <class InputIterator1, class InputIterator2,
       class OutputIterator, class BinaryOperation>
  OutputIterator transform (InputIterator1 first1, InputIterator1 last1,
                            InputIterator2 first2, OutputIterator result,
                            BinaryOperation binary_op);

```

### 一元操作

```cpp
#include <algorithm>
#include <iostream>
#include <vector> 


int doubleMulti(int a){ return a*2; };

int main()
{   
    std::vector<int> vecB = {1,2,3,4,5};
    std::vector<int> vecC(5);
    
  	// 函数指针
    std::transform(vecB.begin(),vecB.end(),vecC.begin(), doubleMulti );
    for(auto &c : vecB) std::cout <<c<<", ";
    for(auto &c : vecC) std::cout <<c<<", ";
  
  	// lambda
  	std::transform(vecB.begin(), vecB.end(), vecB.begin(), [](int d)->int {return d * 3; });
    for(auto &c : vecB) std::cout <<c<<", ";
}



```



二元操作

```cpp
int main()
{ 
		// 二元操作
    std::vector<int> foo;
		std::vector<int> bar;
 
    // set some values:
    for (int i = 1; i<6; i++)
      foo.push_back(i * 10); 
    bar.resize(foo.size()); 
    std::transform(foo.begin(), foo.end(), bar.begin(), doubleMulti);
      for(auto &c : bar) std::cout <<c<<", ";

    std::transform(foo.begin(), foo.end(), bar.begin(), foo.begin(), std::plus<int>());
      for(auto &c : foo) std::cout <<c<<", ";
  
  	// 即：bar开始的每个元素与foo 起止范围内的元素进行操作 ，结果放在foo begin开始的范围内
}
```



----



## for_each



```cpp
{
    // for_each :遍历
    std::vector<int> D = {1,2,3,4,5};
    std::for_each(D.begin(),D.end(), [&](int a)-> int { return a*2;});
    for(auto &d : D)    std::cout <<d<<std::endl;


    // for_each : 改变
    std::for_each(D.begin(),D.end(), [](int &a)-> int { a=a*2;});
    for(auto &d : D)    std::cout <<d<<std::endl;


    // transform : 改变
    std::transform(D.begin(),D.end(), D.begin(),[](int a)-> int { return a*2;});
    for(auto &d : D)    std::cout <<d<<std::endl;
  
  
  	// for_each_n
  	// start from c++17
    std::for_each_n(D.begin(), 3, [](int& n){ n *= 2; });
    for(auto &d : D)    std::cout <<d<<std::endl;
}
```



----



## accumulate

- accumulate定义在  ==#include<numeric>==
- 功能1：累加求和（begin，end，初始值）； 
- 功能2： 给定一个区间和初值init以及一个可选的操作函数op，返回一个和init一样类型的结果，该结果是通过对给定区间内的每个元素逐个累积用op操作作用于init而得到的。==op是一个二元操作函数，默认的op是 `+` 运算, 这就是功能1执行累加的原因.==

```cpp
// 1. 无op
template <class InputIterator, class T>
   T accumulate (InputIterator first, InputIterator last, T init);

// 2. 有op
template <class InputIterator, class T, class BinaryOperation>
   T accumulate (InputIterator first, InputIterator last, T init,
                 BinaryOperation binary_op);
```

功能1：

```cpp
#include <iostream>
#include <vector> 
#include <numeric>

int main()
{
    int sum = std::accumulate(D.begin() , D.end() , 0);
    std::cout<< "sum="<<sum <<std::endl;
  
  	//其实等价于功能2
  	// 显示指定op为二元操作符 ： plus<int>()
    std::cout <<"sum="<< std::accumulate(D.begin(), D.end(), 0, std::plus<int>()); 

    std::vector<std::string> E = {"1","2","3","4","5"};
    std::string sumString = std::accumulate(E.begin() , E.end() , std::string("--")); 
    std::cout<< "sumString="<<sumString <<std::endl; // sumString=--12345
}
```



功能2：

带有操作符的：可以是**函数、函数对象、lambda、bind函数组合**

```cpp
std::accumulate(D.begin(), D.end(), 0, [](int a, int b) -> int {return a+b+2;}); 
```

==注意：因为是相加，入参必须是两个==

