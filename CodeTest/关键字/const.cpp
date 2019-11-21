#include <iostream>
#include <stdalign.h>


class B
{
public:
    // explicit B(int a){std::cout <<"a="<<a <<std::endl;}

    // explicit B(int a, int b){std::cout <<"a="<<a <<std::endl; }

    // explicit B(bool a, bool b=false, bool c=true ){std::cout <<"a="<<a <<std::endl; }

    B(){std::cout <<"a="<<10 <<std::endl;}

    void f() const
    {
         {std::cout <<"B const ";}
    }
};

class C : public B
{
public:
    C(){std::cout <<"a="<<20 <<std::endl;}

    void f() const
    {
        std::cout <<"C const ";
        B::f();
    }
};

int main()
{   
    C* c = new C();
    c->f();

}