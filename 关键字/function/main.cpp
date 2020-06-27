#include <functional>
#include <iostream>

using namespace std;

// 1. 普通函数
int g_Minus(int i, int j)
{
    std::cout << "in g_Minus: " << i << " " << j << std::endl;
    return i - j;
}
 
// 2. 类
class tClass {
    public:
        // 2. 类 成员函数
        void setID(int id) {
            id_ = id;
        }
        int getID() {
            return id_;
        }
         // 2. 类 静态成员函数
        static int wrongID() {
            return 100;
        }
        // 2. 类　成员变量
        int id_ = 5;
    private:
        // 2. 类 私有成员函数
        void psetID(int id) {
            id_ = id;
        }
};
 
// 3. 函数对象
struct Add
{
    int operator()(int i, int j) {
        return i + j;
    }
};
 
// 4. 模板函数对象
template <class T>
struct Sub
{
    T operator()(T i, T j) {
        return i - j;
    }
};
 
template <class T>
T Mul(T i, T j) {
    return i * j;
}
 
 
int main()
{
    // 例子1. 普通函数
    std::function<int(int,int)> f = g_Minus;
    int ret = f(1,2);
    std::cout << ret << std::endl;                    
 
    // 例子2. 类的静态成员函数
    std::function<int(void)> f2 = &tClass::wrongID;
    ret = f2();
 
    // 例子3. 类普通成员函数
    tClass c1;
    std::function<void(int)> f3 = std::bind(&tClass::setID, &c1, std::placeholders::_1);
    std::cout << c1.getID() << std::endl;                       
    f3(10);
    std::cout << c1.getID() << std::endl;                             
 
    // 例子4. 函数对象
    std::function<int(int,int)> f4 = Add();               // 绑定到了一个函数对象，Add()是会返回一个匿名的函数对象
    std::cout << f4(5, 8) << std::endl;                        
 
    // 例子5. 模板函数对象
    std::function<float(float, float)> f5 = Sub<float>();
    std::cout << f5(11.55, 3.33) << std::endl;                           
 
    // 例子6. 模板函数
    std::function<double(double,double)> f6 = Mul<double>;
    std::cout << f6(11.55, 3.33) << std::endl;                                 
 
    // 例子7. 类普通成员函数
    std::function<void(tClass &, int)> f9 = &tClass::setID;
    f9(c1, 150);
    std::cout << c1.getID() << std::endl;                                       
 
    // 例子8. 适配成一个参数，并且将第二个参数设置成固定值5
    std::function<int(int)> f8 = std::bind(g_Minus, std::placeholders::_1, 5);
    std::cout << f8(6) << std::endl;
 
    // 例子9. 调整参数顺序
    std::function<int(int, int)> f10 = std::bind(g_Minus, std::placeholders::_2, std::placeholders::_1);
    std::cout << f10(8, 3) << std::endl;
 
    // 例子10. 类成员
    std::function<int(tClass const&)> n1 = &tClass::id_;
    std::cout << n1(c1) << std::endl;
 
    return 1;
}