# 类和对象练习

记录日期：2026-10-22。

这是“类和对象”阶段的练习归档，保留当前的题目作答、代码实现和项目模板，供后续复习与改进。

## 文件说明

```text
类和对象练习/
├── README.md
├── ObjectAndClass/
│   ├── README.md
│   ├── CMakeLists.txt
│   ├── main.cpp
│   └── example/
│       ├── Student.h / Student.cpp
│       ├── Point.h / Point.cpp
│       ├── Tracker.h / Tracker.cpp
│       └── Score.h / Score.cpp
└── template/
    ├── CMakeLists.txt
    ├── main.cpp
    └── README.md
```

- [练习文档](ObjectAndClass/README.md)：类与对象专题题目及当前作答。
- [程序入口](ObjectAndClass/main.cpp)：各个类的练习调用。
- [Student](ObjectAndClass/example/Student.h)：私有数据、公有接口、const 学号、初始化列表、const 成员函数和类外定义。
- [Point](ObjectAndClass/example/Point.h)：二维坐标与相等运算符重载。
- [Tracker](ObjectAndClass/example/Tracker.h)：利用静态成员和构造、析构函数统计当前存活的对象数量。
- [Score](ObjectAndClass/example/Score.h)：拷贝构造、拷贝赋值、连续赋值与自身赋值。
- `template/`：独立的基础 C++ 项目模板，保留供后续练习使用。

## 阶段小结

1. 用类把数据与操作组织在一起，通过访问权限控制类外能够使用的接口。
2. 使用构造函数建立对象的初始状态；初始化列表可以初始化 const 成员。
3. 只读取对象状态的成员函数使用 const，便于 const 对象调用。
4. 类内声明、类外定义成员函数时，需要使用类名和作用域运算符。
5. 拷贝构造用于创建新对象，拷贝赋值用于修改已经存在的对象。
6. 成员运算符重载中的左侧对象由 this 指定，可以通过重载相等运算符比较两个坐标。
7. 静态成员由同一个类的对象共享；结合构造与析构可以观察对象的生命周期。

## 后续自查

本次保留练习代码的当前状态，以下项目留待继续完善：

- `PointTest()` 中的 `(0, 0)` 是逗号表达式，需要检查与坐标对象比较时的写法，避免依赖整数到 Point 的隐式转换。
- `main()` 当前重复调用了 `StudentTest()`，尚未调用已经定义的 `ScoreTest()`。
- `ScoreTest()` 中的 `Score c = a;` 属于拷贝构造；验证拷贝赋值时，还需要覆盖先创建对象、再赋值的场景。
- 补充学生年龄修改和负数输入的验证，检查修改一个对象是否影响其他对象。

## 构建与运行

当前项目配置使用 C++20 和 CMake 4.0 及以上版本。

可用 CLion 打开 `ObjectAndClass/`，或在本目录中使用已经配置好编译器的终端执行：

```sh
cmake -S ObjectAndClass -B build
cmake --build build
```

构建完成后运行生成的 `ObjectAndClass` 程序。可执行文件位置由生成器决定，Windows 下通常位于 `build/` 或 `build/Debug/`。

本次归档包含源码和文档，IDE 本地配置与编译产物由仓库根目录的 `.gitignore` 排除。发布副本中的中文源文件统一使用 UTF-8 编码。
