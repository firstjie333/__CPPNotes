#include <algorithm>
#include <iostream>
#include <vector>


int main()
{

    std::vector<int> v{5, 6, 4, 3, 2, 6, 7, 9, 3};
 
    std::nth_element(v.begin(), v.begin() + 4, v.begin()+5);
    std::cout << "The median is " << v[v.size()/2] << '\n';

    for(auto &a : v)
        std::cout <<a <<",";
 
    std::nth_element(v.begin(), v.begin()+1, v.end(), std::greater<int>());
    std::cout << "The second largest element is " << v[1] << '\n';

    for(auto &a : v)
        std::cout <<a <<",";


    std::vector<double> values {2.7, 2.7, 2.7, 3.14, 3.14, 2.7, 2.7};
    double value {3.14};
    int times {3};
    auto iter = std::search_n(std::begin(values), std::end(values), times, value);
    std::cout <<"\ndistance="<<std::distance(values.begin(),iter ) <<std::endl;

}