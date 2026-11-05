# 模板练习

记录日期：2026-11-05。

这是“模板”阶段的练习归档，保留 22 道模板专题题目和对应的 CMake 工程，供后续复习与改进。

## 文件说明

```text
模板练习/
├── README.md
└── template/
    ├── README.md
    ├── CMakeLists.txt
    └── main.cpp
```

- [练习文档](template/README.md)：函数模板、类模板、非类型模板参数、全特化与偏特化、模板与编译链接，共 22 题，不附参考答案。
- [程序入口](template/main.cpp)：练习代码入口，可以按题目把代码粘贴到这里运行。
- [CMakeLists.txt](template/CMakeLists.txt)：C++20 工程配置。

## 本阶段覆盖

1. 函数模板的定义、调用和类型参数推断。
2. 显式模板实参、函数模板与普通函数的重载。
3. 类模板、成员函数类外定义和按需实例化。
4. 类模板的静态成员及其类外定义。
5. 非类型模板参数和固定长度数组。
6. 类模板全特化、偏特化及选择顺序。
7. 模板的分离编译、链接错误和显式实例化。
8. 依赖名称与 `typename`、默认模板实参、类模板实参推断（CTAD）。

## 构建与运行

当前项目配置使用 C++20 和 CMake 4.0 及以上版本。

可直接用 CLion 打开 `template/`，或在 `模板练习/` 目录执行：

```sh
cmake -S template -B build
cmake --build build
```

构建完成后运行生成的 `template` 程序。可执行文件位置由生成器决定，Windows 下通常位于 `build/` 或 `build/Debug/`。

本次归档包含文档和源码，IDE 本地配置与编译产物由仓库根目录的 `.gitignore` 排除。
