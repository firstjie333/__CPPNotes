#include <functional>
#include <iostream>

void test1(){   std::cout<<"test1"<<std::endl;} //普通函数

template <class T>  
T   test2(T a){ std::cout <<"test2:"<<a<<std::endl; return a;}  // 模板函数

auto test3 = [](int a)->int{ std::cout<<"test3:"<<a<<std::endl;  return a;}; // lamdba


struct B    // 函数对象
{
    int operator()(int a){ return a*2;}
};


template <class T>
struct BT   // 函数模板对象
{
	T operator()(T i){return i*2;}
};


class Computer
{
public:
	static int Add(int i, int j)
	{
		return i + j;
	}
 
	template<class T>
	static T AddT(T i, T j)
	{
		return i + j;
	}
 
	int AddN(int i, int j)
	{
		return i + j;
	}
};

int main()
{
    std::function<void()> ff = test1;
    std::function<int(int)> ff2 = test2<int>;
    std::function<bool(bool)> ff222 = test2<bool>;
    std::function<std::string(std::string)> ff22 = test2<std::string>;
    std::function<int(int)> ff3 = test3;

    ff();
    ff2(5);
    ff222(true);
    ff22("string");
    ff3(5);


    std::function<int(int)> f1 = B();
    std::function<int(int)> f2 = BT<int>();

    f1(10);
    f2(10);


    //1、 类静态函数
	std::function<int(int, int)> f = &Computer::Add;
	std::cout << f(1, 1) << std::endl;
 
	//2、 类静态模板函数
	std::function<int(int, int)> ft = &Computer::AddT<int>;
	std::cout << ft(1, 1) << std::endl;
 
 
 
	//普通函数绑定  需要构造类对象
	Computer c;
    
	//3、 普通函数 需使用bind,将类对象地址 &c 绑定上
	std::function<int(int, int)> fN = std::bind(&Computer::AddN, &c, std::placeholders::_1, std::placeholders::_2);
	std::cout << fN(1, 1) << std::endl;
 
 
	//4、普通函数， 也可以这样调用  个人觉得这个比 bind 麻烦，不建议
	std::function <int(const Computer ＆, int, int)> fN2 = &Computer::AddN;
	std::cout << fN2(c,1, 1) << std::endl;


}