#include <iostream>


const int N = 5; 
int Count[N] = {5,2,2,3,5};//每一张纸币的数量 
int Value[N] = {1,5,10,50,100};
int solve(int money) {
    int num = 0;
    for(int i = N-1;i>=0;i--) 
    {
        int c = std::min(money/Value[i],Count[i]);//每一个所需要的张数 
        money = money-c*Value[i];
        num += c;//总张数 
    }
    if(money>0) 
        num=-1;
    return num;
}

int main()
{
    int a = solve(341);
    std::cout<< a << std::endl; 
}