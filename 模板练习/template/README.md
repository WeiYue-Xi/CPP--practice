# C++ 模板专题练习

本练习配合 `template` 目录的 CMake 工程使用，工程标准为 C++20。

共 22 题，当前保留部分题目的作答，未附完整参考答案。前 18 题练习概念、代码阅读和输出判断，第 19～21 题为编程题，第 22 题为选做。难度以初学者巩固为主：会写简单的函数模板和类模板，能根据调用推断模板实参，理解全特化与偏特化即可。不涉及 SFINAE、模板元编程和完美转发。

## 使用说明

- 使用 C++17 或更新标准；本工程已设置为 C++20。
- 题目中的完整程序可以直接粘贴到同目录的 `main.cpp` 运行；第 16 题按三个文件阅读，不需要真的拆分当前工程。
- 阅读题先手写输出或结论，再编译核对。
- 编程题按题目给出的输出顺序验证，不要求使用 `std::` 算法，可以用普通循环。
- 题目中的类模板和数据成员都很小，不需要考虑动态内存、异常安全和移动语义。
- 第 17 题稍难，可以先跳过；第 22 题是选做。

## 一、函数模板

### 第 1 题：第一个函数模板

知识点：函数模板的定义、类型参数、模板实例化。

```cpp
#include <iostream>

template <typename T>
T bigger(T a, T b) {
    return a > b ? a : b;
}

int main() {
    std::cout << bigger(3, 8) << ' ';
    std::cout << bigger(2.5, 1.5) << ' ';
    std::cout << bigger('a', 'z') << '\n';
    return 0;
}
```

1. 程序输出什么？

   8 2.5 z

2. 三次调用中 `T` 分别被推断为什么类型？

   int float char

3. 编译器为这个函数模板生成了几个函数？这些函数是在什么时候生成的？

   3个 调用时生成

4. 如果把第三次调用改成 `bigger('a', 1)`，还能编译吗？为什么？

   不能，因为调用模版时只能运行一种类型

### 第 2 题：推断冲突与显式模板实参

知识点：模板实参推断、显式指定模板实参、类型转换。

```cpp
template <typename T>
T maxValue(T a, T b) {
    return a > b ? a : b;
}
```

以下语句相互独立，分别判断能否通过编译；能通过的，写出返回值以及 `T` 是什么类型。

1. `maxValue(3, 7)` 7
2. `maxValue(3, 7.0)` 不能通过
3. `maxValue<double>(3, 7.0)` 7.0
4. `maxValue(3.0, 7)` 不能通过
5. `maxValue<int>(3.9, 7.2)` 7

补充问题：

- 第 5 条中两个实参都是小数，为什么结果仍然是整数 `7`？

  类型转换

- 不修改函数模板，让第 2 条语句合法，至少写出两种写法。

### 第 3 题：函数模板与普通函数重载

知识点：重载决议、模板与非模板函数的优先级、显式空模板实参列表。

```cpp
#include <iostream>

template <typename T>
void show(T value) {
    std::cout << "template\n";
}

void show(int value) {
    std::cout << "ordinary\n";
}

template <typename T>
void show(T* value) {
    std::cout << "pointer\n";
}

int main() {
    int n = 5;
    show(n);
    show(5);
    show<>(5);
    show(&n);
    return 0;
}
```

1. 程序输出什么？

   ordinary

   ordinary

   template

   pointer

2. `show(5)` 为什么没有选择第一个函数模板？

   编译器会优先选择普通函数

3. `show<>(5)` 中的 `<>` 起了什么作用？

   调用模版

4. 删除普通函数 `show(int)` 后，`show(5)` 输出什么？

   template

5. 对于 `show(&n)`，两个函数模板都能匹配，为什么最终选择 `show(T*)`？

   优先调用普通函数

### 第 4 题：按值传递与按引用传递

知识点：函数模板形参、值传递与引用传递、左值。

```cpp
#include <iostream>

template <typename T>
void addOne(T value) {
    ++value;
}

template <typename T>
void addOneRef(T& value) {
    ++value;
}

int main() {
    int n = 5;
    addOne(n);
    std::cout << n << ' ';
    addOneRef(n);
    std::cout << n << '\n';
    return 0;
}
```

1. 程序输出什么？

   5 6

2. 为什么 `addOne` 没有改变 `n`？

   因为没有将n的引用传过去

3. `addOneRef(5)` 能否编译？为什么？

   不能，因为必须要传一个变量。

4. 如果把 `addOneRef` 的参数改成 `const T&`，函数体仍然写 `++value`，会怎样？

   无法改变value

### 第 5 题：带容器的函数模板

知识点：`const` 引用参数、模板实参推断、值初始化。

```cpp
#include <iostream>
#include <string>
#include <vector>

template <typename T>
T sum(const std::vector<T>& values) {
    T total{};
    for (const T& value : values) {
        total += value;
    }
    return total;
}

int main() {
    std::cout << sum(std::vector<int>{1, 2, 3}) << ' ';
    std::cout << sum(std::vector<double>{1.5, 2.5}) << ' ';
    std::cout << sum(std::vector<std::string>{"a", "b", "c"}) << '\n';
    return 0;
}
```

1. 程序输出什么？
2. 三次调用中 `T` 分别是什么类型？
3. `T total{}` 在 `T` 为 `int`、`double`、`std::string` 时，分别把 `total` 初始化成什么？
4. `sum({1, 2, 3})` 能否编译？为什么？怎样修改调用才能通过？

### 第 6 题：返回类型写成 auto

知识点：`auto` 返回类型、模板实例化时的类型推导。

```cpp
#include <iostream>
#include <string>

template <typename T, typename U>
auto add(T a, U b) {
    return a + b;
}

int main() {
    std::cout << add(1, 2) << ' ';
    std::cout << add(1, 2.5) << ' ';
    std::cout << add(std::string("hello "), std::string("world")) << '\n';
    return 0;
}
```

1. 程序输出什么？三次调用的 `T`、`U` 和返回类型分别是什么？

   3 3.5 hello world

2. 返回类型写成 `auto` 时，编译器在什么时候确定它？

   

3. 如果把返回类型改成 `T`，三次调用的输出分别变成什么？

   3 3 hello world

## 二、类模板

### 第 7 题：定义并使用类模板

知识点：类模板定义、模板实参、类模板实参推断。

```cpp
#include <iostream>
#include <string>

template <typename T>
class Box {
private:
    T value;

public:
    Box(T v) : value(v) {}
    T get() const { return value; }
};

int main() {
    Box<int> a(5);
    Box<double> b(2.5);
    Box<std::string> c("hi");
    std::cout << a.get() << ' ' << b.get() << ' ' << c.get() << '\n';

    Box d("hi");
    std::cout << d.get() << '\n';
    return 0;
}
```

1. 程序输出什么？
2. `Box<int>` 与 `Box<double>` 是同一个类吗？
3. C++17 起，`Box d("hi");` 中的 `d` 是什么类型？`T` 被推断成什么？
4. `Box<int> e;` 能否编译？为什么？

### 第 8 题：类模板的成员函数类外定义

知识点：类外定义、作用域运算符、模板头、注入类名。

```cpp
#include <iostream>
#include <string>

template <typename T>
class Box {
private:
    T value;

public:
    Box(T v);
    T get() const;
};

template <typename T>
Box<T>::Box(T v) : value(v) {}

template <typename T>
T Box<T>::get() const {
    return value;
}

int main() {
    Box<std::string> b("cpp");
    std::cout << b.get() << '\n';
    return 0;
}
```

1. 程序输出什么？
2. 两个类外定义前为什么都必须写 `template <typename T>`？
3. `Box<T>::Box(T v)` 中，第二个 `Box` 后面能不能再写 `<T>`？为什么？
4. `T Box<T>::get() const` 中，返回类型 `T` 前需要写 `typename` 吗？说明理由。
5. 如果漏掉第一个 `template <typename T>`，会出现什么错误？

### 第 9 题：成员函数按需实例化

知识点：类模板成员的实例化时机、未使用成员不检查。

```cpp
#include <iostream>

template <typename T>
class Holder {
private:
    T value;

public:
    Holder(T v) : value(v) {}
    T get() const { return value; }
    auto length() const { return value.size(); }
};

int main() {
    Holder<int> h(5);
    std::cout << h.get() << '\n';
    return 0;
}
```

1. 程序能编译吗？输出什么？
2. 如果在 `main()` 中增加 `std::cout << h.length() << '\n';`，会发生什么？
3. 解释类模板的成员函数在什么时候被实例化。
4. 这是否意味着模板代码完全不检查类型？简要说明。

### 第 10 题：类模板的静态成员

知识点：静态数据成员、类外定义、每个实例化各有一份。

```cpp
#include <iostream>
#include <string>

template <typename T>
class Counter {
private:
    static int count;
    T value;

public:
    Counter(T v) : value(v) { ++count; }
    static int getCount() { return count; }
};

template <typename T>
int Counter<T>::count = 0;

int main() {
    Counter<int> a(1);
    Counter<int> b(2);
    Counter<std::string> c("x");
    std::cout << Counter<int>::getCount() << ' '
              << Counter<std::string>::getCount() << '\n';
    return 0;
}
```

1. 程序输出什么？
2. `Counter<int>::count` 与 `Counter<std::string>::count` 是同一个变量吗？
3. 类外定义静态成员时，为什么需要 `template <typename T>`？
4. `getCount()` 能否通过 `Counter<int>::getCount()` 调用？为什么？

### 第 11 题：类模板作为函数参数

知识点：从实参推断类模板参数、用户定义转换、显式模板实参。

```cpp
#include <iostream>

template <typename T>
class Box {
private:
    T value;

public:
    Box(T v) : value(v) {}
    T get() const { return value; }
};

template <typename T>
void show(const Box<T>& b) {
    std::cout << b.get() << '\n';
}

int main() {
    Box<int> a(1);
    show(a);
    show(Box<double>(2.5));
    show(3);
    return 0;
}
```

1. 哪几次调用能编译？分别输出什么？
2. 前两次调用中 `T` 分别是什么？
3. `show(3)` 为什么不能编译？
4. 不修改 `show`，怎样让 `show(3)` 合法？至少写出一种写法。

## 三、非类型模板参数与特化

### 第 12 题：非类型模板参数

知识点：整型非类型模板参数、编译期常量、类模板类型。

```cpp
#include <iostream>

template <typename T, int N>
class Array {
private:
    T data[N]{};

public:
    int size() const { return N; }
    T& at(int i) { return data[i]; }
    T at(int i) const { return data[i]; }
};

int main() {
    Array<int, 5> a;
    a.at(0) = 10;
    std::cout << a.size() << ' ' << a.at(0) << '\n';
    Array<double, 3> b;
    std::cout << b.size() << ' ' << b.at(1) << '\n';
    return 0;
}
```

1. 程序输出什么？
2. `Array<int, 5>` 与 `Array<int, 6>` 是同一个类型吗？`Array<int, 5>` 与 `Array<double, 5>` 呢？
3. `N` 可以是运行时变量吗？例如 `int n = 5; Array<int, n> a;`。
4. `Array<int, 5> a;` 中 `data` 的元素是否被初始化为 0？依据是什么？
5. 本题的 `at()` 是否检查下标越界？

### 第 13 题：类模板全特化

知识点：全特化、`template <>`、特化后的独立成员。

```cpp
#include <iostream>

template <typename T>
class Printer {
public:
    void print(const T& value) const {
        std::cout << "generic: " << value << '\n';
    }
};

template <>
class Printer<bool> {
public:
    void print(bool value) const {
        std::cout << "bool: " << (value ? "true" : "false") << '\n';
    }
};

int main() {
    Printer<int> a;
    a.print(5);
    Printer<bool> b;
    b.print(true);
    return 0;
}
```

1. 程序输出什么？
2. `template <>` 表示什么？`Printer<bool>` 还是模板吗？
3. 在 `Printer<bool>` 的特化中，能不能把参数写成 `const T&`？为什么？
4. 如果删除整个特化，`b.print(true)` 输出什么？

### 第 14 题：类模板偏特化

知识点：偏特化、指针形式、偏特化的模板参数。

```cpp
#include <iostream>

template <typename T>
class Storage {
public:
    void info() const { std::cout << "generic\n"; }
};

template <typename T>
class Storage<T*> {
public:
    void info() const { std::cout << "pointer\n"; }
};

int main() {
    Storage<int> a;
    Storage<int*> b;
    Storage<const char*> c;
    a.info();
    b.info();
    c.info();
    return 0;
}
```

1. 程序输出什么？
2. `Storage<const char*>` 匹配偏特化时，偏特化里的 `T` 是什么？
3. 偏特化中的 `T` 与主模板的 `T` 是同一个模板参数吗？
4. 如果再增加一个 `template <> class Storage<int*> { ... };`，其中 `info()` 输出 `int-pointer`，`Storage<int*>` 会输出什么？

### 第 15 题：选择主模板、偏特化还是全特化

知识点：特化选择顺序、偏特化与全特化的关系。

```cpp
#include <iostream>

template <typename T>
class Tag {
public:
    static const char* name() { return "primary"; }
};

template <typename T>
class Tag<T*> {
public:
    static const char* name() { return "pointer"; }
};

template <>
class Tag<int*> {
public:
    static const char* name() { return "int-pointer"; }
};

int main() {
    std::cout << Tag<int>::name() << ' '
              << Tag<double*>::name() << ' '
              << Tag<int*>::name() << '\n';
    return 0;
}
```

1. 程序输出什么？
2. 为什么 `Tag<int*>` 选择全特化，而不是偏特化？请按“主模板 → 偏特化 → 全特化”的优先级说明。
3. 如果删除 `Tag<int*>` 的全特化，`Tag<int*>::name()` 返回什么？
4. 补充：函数模板能否像类模板这样偏特化？如果不能，通常用什么替代？

## 四、模板与编译

### 第 16 题：模板定义为什么不放在 .cpp 里

知识点：分离编译、模板实例化、链接错误、显式实例化。

下面的三个文件属于同一个工程，不是同一个 `main.cpp`。

```cpp
// max.h
#pragma once

template <typename T>
T maxValue(T a, T b);
```

```cpp
// max.cpp
#include "max.h"

template <typename T>
T maxValue(T a, T b) {
    return a > b ? a : b;
}
```

```cpp
// main.cpp
#include "max.h"
#include <iostream>

int main() {
    std::cout << maxValue(3, 7) << '\n';
    return 0;
}
```

1. 把三个文件一起编译链接，会发生什么？错误出现在编译阶段还是链接阶段？
2. `main.cpp` 只看到了声明，为什么还能通过编译？
3. `max.cpp` 中已经有完整的函数定义，为什么目标文件里仍然没有 `maxValue<int>` 的代码？
4. 不修改 `main.cpp` 中的调用，给出两种修复方法。
5. 类模板的成员函数定义在 `.cpp` 中时，通常也会遇到同样的问题。为什么？

补充：在 `main.cpp` 中直接写 `#include "max.cpp"` 能否解决链接错误？这种做法有什么问题？

### 第 17 题：依赖类型与 typename（稍难，可先跳过）

知识点：依赖名称、`typename` 消歧、嵌套类型。

```cpp
#include <iostream>
#include <string>
#include <vector>

template <typename T>
void showFirst(const T& values) {
    typename T::value_type first = *values.begin();
    std::cout << first << '\n';
}

int main() {
    showFirst(std::vector<int>{10, 20, 30});
    showFirst(std::vector<std::string>{"alpha", "beta"});
    return 0;
}
```

1. 程序输出什么？
2. 两次调用中 `T` 分别是什么？
3. 为什么 `T::value_type` 前面必须写 `typename`？如果不写，编译器会把它当成什么？
4. 如果把 `std::vector` 换成 `std::array<double, 3>`，这个函数还能使用吗？为什么？

### 第 18 题：默认模板实参与类模板实参推断

知识点：默认模板实参、按顺序指定、CTAD。

```cpp
#include <iostream>

template <typename T = int, int N = 3>
class Array {
private:
    T data[N]{};

public:
    int size() const { return N; }
    T at(int i) const { return data[i]; }
};

template <typename T>
class Box {
private:
    T value;

public:
    Box(T v) : value(v) {}
    T get() const { return value; }
};

int main() {
    Array<> a;
    Array<double> b;
    Array<char, 5> c;
    std::cout << a.size() << ' ' << b.size() << ' ' << c.size() << '\n';

    Box x(5);
    std::cout << x.get() << '\n';
    return 0;
}
```

1. 程序输出什么？
2. `Array<>` 的 `T` 和 `N` 分别是什么？
3. `Array<double>` 的 `N` 是什么？`Array<int>` 的 `N` 呢？
4. 能否写成 `Array<, 5>`，只指定 `N`？为什么？
5. `Box x(5);` 中 `x` 是什么类型？这依赖 C++17 的什么特性？
6. `Box y;` 能否编译？为什么？

## 五、小型编程题

### 第 19 题：实现 Pair 类模板

知识点：类模板设计、构造函数、类外定义、访问函数。

实现一个 `Pair<T1, T2>` 类模板，要求如下：

1. 私有成员为 `T1 firstValue` 和 `T2 secondValue`。
2. 构造函数 `Pair(const T1& a, const T2& b)`，使用初始化列表初始化两个成员。
3. 提供 `getFirst() const`、`getSecond() const`、`setFirst(const T1&)`、`setSecond(const T2&)`。
4. 构造函数必须在类外定义；至少再选一个成员函数也在类外定义。
5. 不需要使用 `std::pair`。

在 `main()` 中验证：

- 创建 `Pair<int, std::string> p(1, "one");`，输出 `1 one`。
- 创建 `Pair<double, char> q(2.5, 'x');`，输出 `2.5 x`。
- 把 `p` 的第二个值改为 `"two"`，把 `q` 的第一个值改为 `3.5`，再次按 `first second` 的格式输出两个对象。

思考：`Pair<int, std::string>` 与 `Pair<std::string, int>` 是同一个类型吗？为什么？

### 第 20 题：实现固定长度数组模板

知识点：非类型模板参数、类模板成员函数、`const` 成员函数。

实现一个 `Array<T, N>` 类模板，要求如下：

1. `N` 为整型非类型模板参数，私有成员为 `T data[N]`。
2. 默认构造函数把所有元素初始化为 `T{}`。
3. 提供以下成员函数：
   - `int size() const`：返回 `N`。
   - `void fill(const T& value)`：把所有元素设为 `value`。
   - `void set(int index, const T& value)`：设置指定下标的值。
   - `T get(int index) const`：返回指定下标的值。
   - `T sum() const`：返回所有元素之和。
4. 不要求做越界检查，本题约定下标合法。

在 `main()` 中验证：

- `Array<int, 4> a;`，先 `fill(2)`，再 `set(0, 10)`，输出 `4 16`。
- `Array<double, 3> b;`，设置 `b` 的第 0 个元素为 `1.5`、第 1 个元素为 `2.5`，输出 `3 4`。

思考：`Array<int, 4>` 与 `Array<double, 3>` 是同一个类型吗？这个类模板能用于 `std::string` 吗？需要 `std::string` 支持哪些操作？

### 第 21 题：实现 Stack 类模板

知识点：类模板与标准容器、成员函数、空状态处理。

实现一个 `Stack<T>` 类模板，要求如下：

1. 使用 `std::vector<T>` 保存元素，作为私有成员。
2. 提供以下成员函数：
   - `void push(const T& value)`：压栈。
   - `bool pop()`：弹栈；栈空时返回 `false`，否则返回 `true`。
   - `const T& top() const`：返回栈顶元素。
   - `bool empty() const`：判断栈是否为空。
   - `int size() const`：返回元素个数。
3. 调用 `top()` 前必须先判空；本题不要求异常处理。
4. 不需要实现拷贝构造、赋值运算符和析构函数。

在 `main()` 中验证：

- 创建 `Stack<int>`，依次压入 `1`、`2`、`3`，用循环输出并弹出，输出顺序为 `3 2 1`。
- 对空栈调用 `pop()`，输出返回值 `0`。
- 创建 `Stack<std::string>`，压入 `"cpp"`，输出栈顶元素。

思考：`Stack<int>` 与 `Stack<double>` 的成员函数是同一份代码吗？

## 六、选做

### 第 22 题：折叠表达式（选做）

知识点：可变参数模板、折叠表达式、空参数包。

```cpp
template <typename... Args>
auto sumAll(Args... args) {
    return (args + ...);
}
```

1. `sumAll(1, 2, 3)` 与 `sumAll(1, 2.5)` 的结果和返回类型分别是什么？
2. 为什么 `sumAll()` 不能编译？
3. 把函数体改成 `return (0 + ... + args);` 后，`sumAll()` 能编译吗？结果是什么？
4. 如果参数中有 `std::string`，例如 `sumAll(std::string("a"), std::string("b"))`，能正常工作吗？同时传入 `std::string` 和 `int` 呢？

## 附录：常见错误提示

| 编译器提示（大意） | 常见原因 | 对应题 |
| --- | --- | --- |
| `no matching function for call to 'maxValue(int, double)'` | 同一个 `T` 被推断成两种类型 | 第 2 题 |
| `request for member 'size' in 'value', which is of non-class type 'int'` | 成员函数在调用时才实例化，`int` 没有 `size()` | 第 9 题 |
| `undefined reference to 'int maxValue<int>(int, int)'` | 模板定义对调用方不可见，无法实例化 | 第 16 题 |
| `need 'typename' before 'T::value_type'` | 依赖名称被当作非类型解析 | 第 17 题 |

## 完成记录

- [ ] 第 1～6 题：函数模板、类型推断、重载与参数传递。
- [ ] 第 7～11 题：类模板、类外定义、按需实例化、静态成员。
- [ ] 第 12～15 题：非类型模板参数、全特化与偏特化。
- [ ] 第 16～18 题：模板的编译与链接、`typename`、默认实参与 CTAD。
- [ ] 第 19～21 题：三个小型类模板的完整实现。
- [ ] 第 22 题：选做的折叠表达式。
