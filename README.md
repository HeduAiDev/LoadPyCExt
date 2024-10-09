# LoadPyCExt
## 简介
该项目为文章[《CPython源码解读：Python 如何导入一个C扩展库（动态链接库）》](https://blog.hedup.cc/?p=698) 的配套代码，用于加载Python C扩展模块。

## 运行
代码需要在Windows平台运行，因为代码中使用了Windows特有的API。
~~~shell
cmake -S . -B build
cmake --build build --config Release
.\bin\loadcAdd.exe
~~~