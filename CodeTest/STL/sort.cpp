#include <algorithm>
#include <iostream>
#include <vector> 
#include <numeric>
#include <deque>
#include <string>
#include <ostream>
#include <iterator>


using namespace std;

int main()
{
    std::deque<std::string> words { "one", "two", "nine", "nine", "one", "three", "four", "five", "six" };
    std::sort(std::begin(words), std::end(words),[](const string& s1, const string& s2) { return s1.back()> s2.back();});
    std::copy(std::begin(words), std::end(words),
    std::ostream_iterator<string> {std::cout," "});   


    std::map<int>
}
