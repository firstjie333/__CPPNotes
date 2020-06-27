#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>
#include <map>


using namespace std;

int main()
{
    std::vector<double> v;
    for(size_t i=0;i<6;i++)
        v.push_back( i*0.1);  
    auto a = std::accumulate(v.begin(), v.end() ,0);
    auto b = std::accumulate(v.begin(), v.end() ,0.0);
    std::cout << "a="<<a <<",b="<<b;

    
    std::vector<int> v{ 0, -1, 2, -3, 4, -5, 6, -7, 8, -9};
    std::vector<int> m;
    std::copy_if(v.begin(),v.end(), std::back_inserter(m),[](const int x)->bool{return x>0;});


    std::map<int,int> mapExample;

    for(size_t i=0; i<10; i++)
        mapExample[i]=i;
    
    std::map<int,int> mapSecond;
}

