#include <algorithm>
#include <iostream>
#include <vector> 
#include <numeric>


int doubleMulti(int a){ return a*2; };

int main()
{   
    // 1. transform 

    // 一元操作
    std::vector<int> vecB = {1,2,3,4,5};
    std::vector<int> vecC(5);
    
    std::transform(vecB.begin(),vecB.end(),vecC.begin(), doubleMulti );
    for(auto &c : vecB) std::cout <<c<<", ";
    for(auto &c : vecC) std::cout <<c<<", ";



    std::transform(vecB.begin(), vecB.end(), vecB.begin(), [](int d)->int {return d * 3; });
    for(auto &c : vecB) std::cout <<c<<", ";



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




    // 2.
    // for_each :遍历
    std::vector<int> D = {1,2,3,4,5};
    std::for_each(D.begin(),D.end(), [&](int a)-> int { return a*2;});
    for(auto &d : D)    std::cout <<d<<std::endl;


    // for_each : 改变
    std::for_each(D.begin(),D.end(), [](int &a)-> int { a=a*2;});
    for(auto &d : D)    std::cout <<d<<std::endl;


    // // transform : 改变
    // std::transform(D.begin(),D.end(), D.begin(),[](int a)-> int { return a*2;});
    // for(auto &d : D)    std::cout <<d<<std::endl;

    // // start from c++17
    // std::for_each_n(D.begin(), 3, [](int& n){ n *= 2; });
    // for(auto &d : D)    std::cout <<d<<std::endl;



    // 3. accumulate
    int sum = std::accumulate(D.begin() , D.end() , 0);
    std::cout<< "sum="<<sum <<std::endl;

    std::vector<std::string> E = {"1","2","3","4","5"};
    std::string sumString = std::accumulate(E.begin() , E.end() , std::string("--")); // sumString=--12345
    std::cout<< "sumString="<<sumString <<std::endl;


    // 显示指定op为二元操作符 ： plus<int>()
    std::cout <<"newSum="<< std::accumulate(D.begin(), D.end(), 0, std::plus<int>()); 


    std::cout << "newSum="<< std::accumulate(D.begin(), D.end(), 0, [](int a, int b) -> int {return a+b+2;}); 
}