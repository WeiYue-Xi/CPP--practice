# C++ 类与对象专题练习（基于 README）

依据文档：[类和对象 README](E:/C++/Classes_And_Obects/README.md)。

本练习按文档中的知识点重新编排，共 22 题，不附参考答案。前 16 题练习概念、代码阅读和改错，第 17～20 题为编程题，第 21～22 题为选做题。

难度以初学者巩固为主。只使用短小的类，不要求实现容器、管理动态内存、编写移动操作或处理复杂继承关系。

## 使用说明

- 使用 C++17 或更新标准。
- 阅读题先手动分析，再运行核对；改错题需要实际修改代码，不能只添加注释。
- 填写代码时删除下划线占位符，检查普通语句和类定义末尾的分号。
- 各题代码相互独立，编程题可以各自使用一个源文件。
- 题目中的普通类均不包含继承和虚函数。对象大小题使用题目明确给出的环境假设。

## 一、概念与基础应用

### 第 1 题：class、struct 与访问权限

知识点：类定义、默认访问权限、访问限定符的作用范围。

```cpp
class A {
    int x = 1;
public:
    int y = 2;
    void setX(int n) { x = n; }
private:
    int z = 3;
};

struct B {
    int x = 4;
    void setX(int n) { x = n; }
};
```

假设在 `main()` 中已经创建 `A a;` 和 `B b;`。

请分别判断以下语句能否通过编译，并说明原因。各条语句独立判断。

1. `a.x = 10;`不同意，a.x为私有成员；
2. `a.y = 20;`通过，a.y为公有成员
3. `a.setX(30);`通过，a.setX为公有成员函数
4. `a.z = 40;`不通过，a.z为私有成员
5. `b.x = 50;`~~不通过b.x为私有成员~~通过，struct成员默认为public
6. `b.setX(60);`~~不通过，同上~~

补充：把 `A` 中的 `private:` 改为 `protected:` 后，第 4 条在 `main()` 中能否直接使用？本题不讨论继承中的区别。

你的作答：不能__________

### 第 2 题：类域与类外定义

知识点：成员函数声明、类外定义、作用域运算符 `::`。

补全四处空白，使程序能够编译并输出对象保存的数字。

```cpp
#include <iostream>

class Number {
private:
    int value = 0;

public:
    void setValue(int n);
    int getValue() const;
};

void Number::setValue(int n) {  // ①
    value = n;
}

int Number::getValue() const {  // ②、③
    return value;
}

int main() {
    Number n;
    n.setValue(8);  // ④
    std::cout << n.getValue() << '\n';
    return 0;
}
```

思考：如果另一个类也有一个叫 `getValue()` 的成员函数，两者一定会发生命名冲突吗？

你的作答：不会，~~函数重载~~不同类的成员处于不同的类作用域中。

### 第 3 题：对象大小与成员函数

知识点：对象大小、内存对齐、空类。

本题假设：`sizeof(char) == 1`、`sizeof(int) == 4`，`char` 的对齐要求为 `1` 字节，`int` 的对齐要求为 `4` 字节；普通类采用相应的常规内存对齐规则，没有额外的打包设置。

```cpp
class A {
    char first;
    int number;
    char last;
};

class B {
    int number;
    char first;
    char last;
};

class C {
    int number;
public:
    void f() {}
    void g() {}
};

class Empty {};
```

1. 按上述假设，计算 `sizeof(A)`、`sizeof(B)`、`sizeof(C)`。
2. `A` 与 `B` 的成员类型相同，为什么对象大小可能不同？
3. 给 `C` 再增加三个普通成员函数，会因为这些函数而增加每个对象的大小吗？
4. `sizeof(Empty)` 能否为 `0`？说明原因，不要求给出所有实现上的具体值。

你的作答：1.sizeof(A) = ~~9~~  12,sizeof(B) = ~~6~~  8,sizeof(C) = 4(整个对象大小要补齐到4的整数倍)

2.~~对象的内存对齐方式不同。~~成员排列顺序不同导致所需的填充字节数不同

3.不会，~~成员函数不占用空间~~ 普通非虚成员函数不会增加每个对象的大小

4.不能，因为需要一字节占位

### 第 4 题：this 与同名参数

知识点：`this` 指针、参数名与成员变量名相同的情况。

```cpp
#include <iostream>

class Student {
private:
    int age = 0;

public:
    void setAge(int age) {
        //*this.age = age;
        
        //(*this).age = age;
        this->age = age;
    }

    int getAge() const {
        return age;
    }
};

int main() {
    Student s;
    s.setAge(18);
    std::cout << s.getAge() << '\n';
    return 0;
}
```

1. 程序实际输出什么？
2. 保留参数名 `age`，修改 `setAge()`，使它真正设置对象的年龄。
3. 调用 `s.setAge(18)` 时，成员函数中的 `this` 指向哪个对象？

你的作答：1.18

3.~~this指向类本身~~ this指向对象s，不是类本身

### 第 5 题：构造函数与默认参数

知识点：构造函数重载、默认构造函数、调用歧义。

```cpp
class Box {
private:
    int size;

public:
    Box() : size(1) {}
    Box(int n = 2) : size(n) {}
};
```

分别独立判断下面的对象定义能否通过编译，并说明原因：

1. `Box a;`不能，因为Box()和所有参数都有都有默认值的Box(int n = 2)都可以接受无参调用，编译器无法确定选择哪一个
2. `Box b(5);`可以通过

再修改类的构造函数设计，使以下两种写法都可以使用：

- `Box a;`：大小初始化为 `1`。
- `Box b(5);`：大小初始化为 `5`。

限制：保留两个构造函数，只修改其中一个函数的参数列表。

你的作答：`Box() :size(1){}`;`Box(int n) :size(n) {}`

### 第 6 题：没有写构造函数就一定初始化为零吗

知识点：编译器生成的默认构造函数、成员默认初始化值。

```cpp
class Counter {
private:
    int count = 0;

public:
    int getCount() const {
        return count;
    }
    Counter(int n = 0)
        :count(n)
        {}
};

int main() {
    Counter c;
    return 0;
}
```

1. 能否仅凭上述代码，就认定局部对象 `c` 的 `count` 一定是 `0`？
2. 写出两种修改方法，保证创建 `Counter c;` 后，`count` 为 `0`：一种在成员声明处修改，另一种使用构造函数。

本题不要求运行并读取未初始化的成员来猜测结果。

你的作答：不能

## 二、构造、析构与对象复制

### 第 7 题：构造与析构顺序

知识点：局部作用域、对象生命周期、析构顺序。

```cpp
#include <iostream>

class Trace {
private:
    int id;

public:
    Trace(int n) : id(n) {
        std::cout << "Create " << id << '\n';
    }

    ~Trace() {
        std::cout << "Destroy " << id << '\n';
    }
};

int main() {
    Trace a(1);
    {
        Trace b(2);
        Trace c(3);
        std::cout << "Inside\n";
    }
    std::cout << "Outside\n";
    return 0;
}
```

写出完整输出，并说明 `b`、`c` 为什么在对应的位置析构。

你的输出：

```text
Create 1
Create 2
Create 3
Inside
Destroy 3
Destroy 2
Outside
Destroy 1

```

你的说明：一个局部域对的多个对象，C++规定后定义的先析构。

### 第 8 题：拷贝构造还是拷贝赋值

知识点：创建新对象与修改已有对象的区别。

```cpp
class Point {
private:
    int x;
    int y;

public:
    Point(int a = 0, int b = 0) : x(a), y(b) {}
};

int main() {
    Point a(1, 2);  // ①
    Point b = a;   // ②
    Point c;       // ③
    c = a;         // ④
    Point d(a);    // ⑤
    return 0;
}
```

1. 逐条说明 ①～⑤ 分别使用了哪种构造函数或赋值操作。
2. 哪几条语句创建了新对象？哪一条修改了已有对象？
3. 为什么不能只根据有没有 `=` 来判断是否调用赋值运算符？

你的作答：1.~~1,2,5使用了拷贝构造，3为默认构造，4为赋值操作~~ 1使用整数参数调用构造函数创建a。2,5拷贝构造。3默认构造。4拷贝赋值

2.1,2,3,5创建了新对象，4修改了已有对象

3.~~主要看创建对象时是否初始化~~  先看这条语句是在创建对象，还是操作已有对象；如果是创建新对象，再看是否用已有的同类对象进行初始化。出现等号可能是初始化也可能是赋值。

### 第 9 题：成员初始化顺序

知识点：初始化列表、声明顺序、成员之间的依赖。

```cpp
#include <iostream>

class Example {
private:
    int x;
    int y;

public:
    Example(int n) : y(x + 2), x(n) {}

    void show() const {
        std::cout << x << " " << y << '\n';
    }
};

int main() {
    Example e(5);
    e.show();
    return 0;
}
```

1. `x` 和 `y` 谁先初始化？依据是什么？
2. 程序输出什么？这里计算 `x + 2` 时，`x` 是否已经初始化？
3. 调整初始化列表的书写顺序，使其与成员声明顺序一致，并保持原有结果。

你的作答：1、x先初始化，初始化顺序是按照声明顺序初始化。

2、5 7，x已经初始化

3、`Example(int n) : x(n),y(x + 2) {}`

### 第 10 题：const 对象能调用什么函数

知识点：`const` 成员函数、只读访问与修改操作。

```cpp
class Meter {
private:
    int value;

public:
    Meter(int n) : value(n) {}

    int getValue() {
        return value;
    }

    void setValue(int n) {
        value = n;
    }
};
```

假设存在以下两个对象：

```cpp
Meter a(3);
const Meter b(7);
```

1. 分别独立判断 `a.getValue()`、`a.setValue(4)`、`b.getValue()`、`b.setValue(8)` 能否通过编译。
2. 不修改对象定义，也不取消 `b` 的 `const`，让两个对象都能读取数值，应如何修改 `getValue()`？
3. 能否给当前的 `setValue()` 直接加上函数末尾的 `const`，让它修改 `b`？说明原因。

你的作答：1、``b.setValue(8)`、`b.getValue()`不能通过编译

2、`int getValue() const{return value;}`

3、不能通过给当前的`setValue()`加`const`来让它修改b，加上`const`后，函数体中的`value = n`反而违反了只读约束，无法通过编译。函数末尾的`const`表示该成员函数不会修改对象的普通非静态数据成员。

### 第 11 题：explicit 与隐式转换

知识点：转换构造函数、显式构造。

```cpp
class Number {
private:
    int value;

public:
    explicit Number(int n) : value(n) {}
};

void use(const Number& n) {}
```

以下语句分别独立判断，不要求将它们放在同一个程序中：

1. `Number a(5);`可以，显示提供参数直接构造
2. `Number b = 5;`不可以，需要从整数到Number的隐式转换
3. `Number c{5};`可以，使用花括号直接构造
4. `use(5);`不可以，整数实参需要隐式转化为Number
5. `use(Number(5));`可以，先显示构造Number，再传入函数

分别说明能否通过编译。如果移除构造函数前的 `explicit`，哪些结论会变化？

你的作答：

## 三、改错与接口设计

### 第 12 题：必须在初始化阶段处理的成员

知识点：`const` 成员、引用成员、没有默认构造函数的类成员。

以下三个片段分别独立判断。指出问题，并只通过修改构造函数来修复，不修改成员类型。

**片段 A**

```cpp
class Record {
private:
    const int id;
public:
    Record(int n) {
        id = n;
    }
};

class Record{
    private:
    	const int id;
    public:
    Record(int n)
        : id(n)
        {}
};
```

**片段 B**

```cpp
class Link {
private:
    int& value;
public:
    Link(int& n) {
        value = n;
    }
};
class Link {
private:
    int& value;
public:
    Link(int& n)
        : value(n)
        {}
};
```

**片段 C**

```cpp
class Engine {
public:
    Engine(int power) {}
};

class Car {
private:
    Engine engine;
public:
    Car(int power) {
        engine = Engine(power);
    }
};

//Engine只有带参构造函数，所以Car不能先默认构造engine，再在函数体给它赋值
Car(int power) 
    : engine(power)
    {}
```

补充：使用 `Link` 时，被引用的整数对象需要满足什么生命周期条件？

被引用的整数对象，在`Link`通过引用访问它是必须任然存活。引用成员不会自动延长被引用对象的生命周期，不能继续使用已销毁的对象。

### 第 13 题：拷贝构造函数的参数

知识点：拷贝构造函数的正确声明、引用参数。

```cpp
class Score {
private:
    int value;

public:
    Score(int n = 0) : value(n) {}

    Score(Score other) : value(other.value) {}
};
```

1. 这个拷贝构造函数的参数声明有什么问题？

   第一个函数参数不是类类型对象的引用。

2. 修改参数声明，让它可以从普通对象和 `const` 对象进行拷贝构造。

   Score(const Score& other) : value(other.value) {}

3. 为什么这里不能使用按值传参？

​		~~因为`const`成员必须使用初始化列表初始化。~~

​		按值传入`other`，需要先复制一个`Score`形参，如果这个操作又要调用同一个按值传参的构造函数，就会再次需要赋值形参，形参递归依赖。因此这种参数形式被禁止，编译器会报错。

### 第 14 题：赋值运算符与连续赋值

知识点：`operator=`、返回当前对象、`this`。

补全空白，使下面的类支持普通赋值和连续赋值。

```cpp
#include <iostream>

class Number {
private:
    int value;

public:
    Number(int n = 0) : value(n) {}

    Number& operator=(const Number& other) {
        value = other.value;
        return *this;
    }

    int getValue() const {
        return value;
    }
};

int main() {
    Number a(1);
    Number b(2);
    Number c(9);
    a = b = c;
    std::cout << a.getValue() << " "
              << b.getValue() << " "
              << c.getValue() << '\n';
    return 0;
}
```

1. 填写空白。

2. 写出输出。

   9 9 9

3. `b = c` 中，`this` 指向哪个对象？

   b

4. 本题只有一个普通整数成员。如果不手写赋值运算符，编译器生成的版本能否完成这里的数值复制？

   ~~不能，编译器只能复制基本类型。~~
   
   可以，`Number`的唯一成员是普通`int`，编译器生成的拷贝赋值运算符可以将右侧对象的`value`赋给左侧对象的`value`，也能支持这里的连续赋值。

### 第 15 题：静态成员函数缺少什么

知识点：静态成员函数、非静态成员、指定对象。

```cpp
class Counter {
private:
    int count = 5;

public:
    static int read() {
        return count;
    }
};
```

1. 为什么 `read()` 不能按当前写法读取 `count`？

   ~~静态成员只能接触静态成员~~

   静态成员函数没有`this`，不能在没有指定对象的情况下直接读取非静态成员`count`

2. 保持 `count` 为非静态成员，写出两种修改方案：
   - 将 `read()` 改为普通成员函数，通过对象调用。

     ```c++
     class Counter {
     private:
         int count = 5;
     
     public:
         int read() {
             return count;
         }
     };
     
     Counter c;
     std::cout << c.read() << endl;
     ```
   
     
   
   - 保留 `read()` 为静态成员函数，增加一个对象参数，读取传入对象的 `count`。
   
     ```c++
     class Counter {
     private:
     	int count = 5;
     public:
         static int read(const Counter& obj){
             return obj.count;
         }
     };
     
     Counter c;
     std::cout << Counter::read(c) << endl;
     ```
     
     
   
3. 分别写出两种方案在 `main()` 中的调用方式。

### 第 16 题：友元与内部类的访问权限

知识点：友元函数、嵌套类、访问权限的方向。

**片段 A：友元函数**

```cpp
class Box {
private:
    int value = 10;
public:
    friend int readBox(const Box& b);
};

int readBox(const Box& b) {
    return b.value;
}
```

1. `readBox()` 是否是 `Box` 的成员函数？

   不是

2. 它为什么可以读取 `value`？

   友元函数可以访问私有成员和保护成员。

3. 如果删除 `friend` 声明，类外的 `readBox()` 还能按当前函数体读取 `value` 吗？

   不能

**片段 B：内部类**

```cpp
class Outer {
private:
    int value = 20;

public:
    class Inner {
    private:
        int code = 3;
    public:
        int read(const Outer& obj) const {
            return obj.value;
        }
    };

    int readCode(const Inner& obj) const {
        return obj.code;
    }
};
```

1. `Inner::read()` 的访问是否允许？为什么需要参数 `obj`？

   允许。因为Inner类的this指针是`const Inner*`，需要通过参数obj指定要访问哪个对象

2. `Outer::readCode()` 的访问是否允许？

   不允许

3. 如果不使用额外的友元声明，如何通过给 `Inner` 增加公有成员函数来修复整个片段？

   可在`Inner`的`public`区增加：

   ```c++
   int getCode() const{
       return code;
   }
   ```

   并把`Outer::readCode()`的函数体改为调用这个公有接口：`return obj.getCode()`。

4. 单独创建 `Outer outer;`，是否会自动创建一个 `Inner` 对象？

   不会自动创建



## 四、小型编程题

### 第 17 题：用初始化列表实现学生类

知识点：封装、初始化列表、`const` 成员、`const` 成员函数、类外定义。

实现一个 `Student` 类，要求如下：

1. 私有成员为 `const int id`、`std::string name`、`int age`。
2. 构造函数接收学号、姓名和年龄，使用初始化列表初始化全部成员。
3. 提供 `getId()`、`getName()`、`getAge()`，均可被 `const Student` 对象调用。
4. 提供 `setAge(int n)`，只在 `n >= 0` 时修改年龄。
5. 学号创建后不能修改，不提供修改学号的函数。
6. 至少把一个成员函数写成类内声明、类外定义的形式；可以仍放在同一个源文件中。

在 `main()` 中验证：

- 创建一个普通学生对象，输出信息，修改年龄，再次输出。
- 尝试设置负数年龄，检查原年龄是否保留。
- 创建一个 `const Student` 对象，通过读取函数输出信息。

每次输出按“学号 姓名 年龄”的顺序，中间用一个空格分隔。

本题不要求对含 `const` 成员的学生对象进行赋值。

### 第 18 题：二维坐标的相等比较

知识点：成员运算符重载、参数、只读成员函数。

实现一个 `Point` 类，要求如下：

1. 私有成员 `x`、`y` 均为整数。
2. 构造函数可以不传参数，此时坐标为 `(0, 0)`；也可以传入两个整数指定坐标。
3. 实现成员函数形式的相等运算符：`bool operator==(const Point& other) const;`。
4. 只有横坐标和纵坐标分别相等时，两个点才相等。

在 `main()` 中先创建一个默认构造的点，再另外创建四个点，坐标分别为 `(0, 0)`、`(2, 3)`、`(2, 3)`、`(3, 2)`，验证：

- 默认构造的点与显式指定为 `(0, 0)` 的点是否相等。
- 两个 `(2, 3)` 是否相等。
- `(2, 3)` 与 `(3, 2)` 是否相等。

用 `if` 将每次比较结果输出为 `Equal` 或 `Different`。

补充说明：这里的成员运算符函数为什么只需要显式写一个参数？

如果一个重载运算符函数是成员函数，则它的第一个运算对象默认传给隐式的this指针，因此运算符重载作为成员函数时，参数比运算对象少一个。

### 第 19 题：统计当前存活的对象数量

知识点：静态成员变量、静态成员函数、构造与析构。

实现一个 `Tracker` 类，要求如下：

1. 有一个私有静态整数成员 `liveCount`，初值为 `0`。本题采用类内声明、类外定义的写法。
2. 每次无参构造一个对象，数量加 `1`。
3. 每次对象析构，数量减 `1`。
4. 提供公有静态成员函数 `getLiveCount()` 返回当前数量。

在 `main()` 中按以下顺序验证，并在每个步骤后输出数量：

- 尚未创建任何对象。
- 在 `main()` 的作用域中创建对象 `a`。
- 进入一个额外的花括号作用域，在其中创建 `b`、`c`。
- 离开这个额外作用域。

限制：本题不进行对象拷贝、对象赋值、函数传值或创建匿名对象，只统计上述直接创建的对象。也不需要使用 `new` 或 `delete`。

思考：为什么 `getLiveCount()` 可以通过 `Tracker::getLiveCount()` 调用，而不必先创建一个对象？

因为静态成员函数属于类而不属于对象，调用它不需要任何对象实例提供this，所以可以通过类名::函数名()调用。

### 第 20 题：为成绩类实现复制操作

知识点：拷贝构造、拷贝赋值、连续赋值、对象独立性。

实现一个 `Score` 类，只保存一个私有整数成员 `value`，要求如下：

1. 构造函数 `Score(int n = 0)` 使用初始化列表设置成绩。
2. 显式实现拷贝构造函数 `Score(const Score& other)`。
3. 显式实现拷贝赋值运算符 `Score& operator=(const Score& other)`。
4. 提供 `setValue(int n)` 和 `getValue() const`。
5. 支持 `a = b = c`，也支持 `a = a`，且结果保持正确。

本题假设成绩参数合法，不需要判断范围；没有指针和动态资源，不需要手写析构函数。

在 `main()` 中验证：

- 用值为 `80` 的对象 `a` 拷贝构造 `b`。
- 修改 `b` 为 `90`，检查 `a` 的值是否保持不变。
- 创建对象 `c`，再用 `a` 对它赋值。
- 进行一次连续赋值和一次自身赋值，输出相关对象的值。

先在注释中标明各语句是“构造新对象”还是“给已有对象赋值”，再运行程序核对。

## 五、选做：临时对象与拷贝优化

### 第 21 题：临时对象的生命周期

知识点：匿名对象、完整表达式、局部 `const` 引用。

```cpp
#include <iostream>

class Trace {
private:
    int id;

public:
    Trace(int n) : id(n) {
        std::cout << "Create " << id << '\n';
    }

    ~Trace() {
        std::cout << "Destroy " << id << '\n';
    }

    void show() const {
        std::cout << "Show " << id << '\n';
    }
};

int main() {
    Trace(1).show(); std::cout << "Next\n";
    const Trace& ref = Trace(2);
    std::cout << "Bound\n";
    ref.show();
    std::cout << "End\n";
    return 0;
}
```

1. 写出完整输出。

   Create 1

   Show 1

   Destroy 1

   Next

   Create 2

   Bound

   Show 2

   End

   Destroy 2

2. 第一个临时对象是在输出 `Next` 之前还是之后析构？不要仅按源代码的物理行数判断。

   之前，这个临时对象没有发生生命周期延长，因此在创建它的完整表达式结束时析构。

3. 第二个临时对象为什么还能在后面通过 `ref.show()` 使用？它何时析构？

   这里临时对象直接绑定到局部`const`引用`ref`，其生命周期延长到`ref`的作用域结束。

### 第 22 题：看到等号就一定有拷贝吗

知识点：C++17 及以后同类型纯右值的直接构造、可选的命名返回值优化。

本题只判断规则，不要求精确统计某个编译器的构造函数打印次数。

```cpp
class Number {
private:
    int value;

public:
    Number(int n) : value(n) {}
    Number(const Number& other) : value(other.value) {}
};

Number makeA() {
    return Number(7);
}

Number makeB() {
    Number local(7);
    return local;
}

int main() {
    Number a = Number(3);
    Number b = makeA();
    Number c = makeB();
    return 0;
}
```

1. `Number a = Number(3);` 是初始化还是给已有对象赋值？

   初始化，这条语句正在定义并初始化新对象a，a不是一个此前已经存在的对象，这里的等号不表示调用拷贝赋值运算符。(<u>***判断重点：这条语句正在创建新对象，还是修改已经存在的对象***</u>)

2. 在 C++17 及以后，这条语句是否一定先创建一个独立临时对象，再拷贝给 `a`？

   会直接构造a，不需要先构造一个独立临时对象，再拷贝给a。

3. `makeA()` 返回同类型纯右值，与 `makeB()` 返回具名局部对象，在拷贝消除的保证上是否相同？

   `makeA()`返回同类型纯右值，直接构造结果对象是标准保证的。`makeB()`返回具名局部对象，允许进行命名返回值优化NRVO(具名返回值优化)，但不保证一定进行。

4. 为什么不能把某次编译运行观察到的拷贝次数，当成所有编译器和设置下都固定的结果？

   可选的NRVO是否发生，可能受到编译器及编译选项等元素影响。因此，一次实验里没有观察到拷贝，不能证明所有环境下都不会发生拷贝。

## 完成记录

- [ ] 第 1～6 题：访问权限、类域、对象大小、this 与初始化基础。
- [ ] 第 7～11 题：构造析构、复制操作、const 与 explicit。
- [ ] 第 12～16 题：初始化列表、赋值重载、静态成员、友元与内部类。
- [ ] 第 17～20 题：小型类的完整实现和验证。
- [ ] 第 21～22 题：选做的临时对象与拷贝优化。