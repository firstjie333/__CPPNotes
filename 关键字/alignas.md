### alignas

1. 计算机会做字节对齐，一般都是8位但有的机器不是
2. 指定了alignas 后，会根据数据的实际大小分配字节 N*分配的数





### alignof

### 对齐

每个[对象类型](https://zh.cppreference.com/w/cpp/language/type)都具有被称为*对齐要求（alignment requirement）*的性质，它是一个整数（类型为 [std::size_t](https://zh.cppreference.com/w/cpp/types/size_t)，总是 2 的幂），表示这个类型的不同对象所能分配放置的连续相邻地址之间的字节数。可以使用 [alignof](https://zh.cppreference.com/w/cpp/language/alignof) 或 [std::alignment_of](https://zh.cppreference.com/w/cpp/types/alignment_of) 来查询类型的对齐要求。可以使用指针对齐函数 [std::align](https://zh.cppreference.com/w/cpp/memory/align) 来获取某个缓冲区中经过适当对齐的指针，还可以使用 [std::aligned_storage](https://zh.cppreference.com/w/cpp/types/aligned_storage) 来获取经过适当对齐的存储区。

对象类型会强制该类型的所有对象实行这个类型的对齐要求；可以使用 [alignas](https://zh.cppreference.com/w/cpp/language/alignas) 来要求更严格的对齐（更大的对齐要求）。

为了使[类](https://zh.cppreference.com/w/cpp/language/class)中的所有非静态成员都符合对齐要求，会在一些成员后面插入一些*填充*。

运行此代码

```cpp
#include <iostream>
 
// S 类型的对象可以在任何地址上分配
// 因为 S.a 和 S.b 都可以在任何地址上分配
struct S {
  char a; // 大小：1，对齐：1
  char b; // 大小：1，对齐：1
}; // 大小：2，对齐：1
 
// X 类型的对象只能在 4 字节边界上分配
// 因为 X.n 必须在 4 字节边界上分配
// 因为 int 的对齐要求（通常）就是 4
struct X {
  int n;  // 大小：4，对齐：4
  char c; // 大小：1，对齐：1
  // 三个填充字节
}; // 大小：8，对齐：4
 
int main()
{
    std::cout << "sizeof(S) = " << sizeof(S)
              << " alignof(S) = " << alignof(S) << '\n';
    std::cout << "sizeof(X) = " << sizeof(X)
              << " alignof(X) = " << alignof(X) << '\n';
}
```

可能的输出：

```cpp
sizeof(S) = 2 alignof(S) = 1
sizeof(X) = 8 alignof(X) = 4
```

最弱的对齐（最小的对齐要求）是 char 、 signed char 和 unsigned char 的对齐，等于 1 ；所有类型中最大的*基础对齐（fundamental alignment）*是 [std::max_align_t](https://zh.cppreference.com/w/cpp/types/max_align_t) 的对齐。当使用 [alignas](https://zh.cppreference.com/w/cpp/language/alignas) 使某个类型的对齐比 [std::max_align_t](https://zh.cppreference.com/w/cpp/types/max_align_t) 的更严格（更大）时，称其为具有*扩展对齐（extended alignment）*要求的类型。具有扩展对齐的类型或包含具有扩展对齐的非静态成员的类，称为*过对齐（over-aligned）类型*。 [new 表达式](https://zh.cppreference.com/w/cpp/language/new)、 [std::allocator::allocate](https://zh.cppreference.com/w/cpp/memory/allocator/allocate) 和 [std::get_temporary_buffer](https://zh.cppreference.com/w/cpp/memory/get_temporary_buffer) 是否支持过对齐类型是由实现定义的。以过对齐类型实例化的[*分配器* (*Allocator*) ](https://zh.cppreference.com/w/cpp/named_req/Allocator)，允许在编译期发生实例化失败，在运行时抛出 [std::bad_alloc](https://zh.cppreference.com/w/cpp/memory/new/bad_alloc) 异常，安静地忽略不支持的对齐要求，也允许正确的处理它们。