cutils
======

some helper functions in C

在日常生活中，无论是写一些POC的玩具项目，或者是工作上的东西，从头开始一个C的工程总是一件比较痛苦的事情，意味着重造一遍轮子。比如字符串，队列，列表，memory allocator

所以我决定，需要把一些自己常用的东西去除依赖，保存起来，再开始新项目的时候直接拿来用。 作为我的自用公共代码库，拿来看看可以，生产环境慎用。


###c_logger

一个简单的无依赖的logger, 可以选择输出到文件或者标准错误输出, 支持log级别, 同时支持动态调整级别.

###c_alloc

带log的内存分配器, 对于错误情况有一些log

###c_string

一个轻量的c的字符串封装

TODO string interning

###c_array

轻量的变长数组封装(类似c++的vector)

###queue.h

steal it from BerkerlyDB
