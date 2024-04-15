## 正确性测试

该测试已实现在 main 函数中，并使用简单的数据样例进行检查。 input 文件夹为程序输入，expected 文件夹为正确程序输出，测试结果打印在 output 文件夹。测试程序比较输出结果与正确输出是否⼀致从而进行评判。

使用如下命令运行正确性测试：

```

#编译链接正确性测试文件
make all
#运行正确性测试
make grade
#清理编译结果
make clean

```




## YCSB测试

该测试实现在ycsb_test.hpp文件和ycsb_test.cpp文件中。每组测试运行45s 以获得较为稳定的测试结果。对相关的基础操作，记录平均时延，P50 、P90 、P99 时延【P50 是指⼀组数据中的中位数值（第 50 百分位数），相应的， P90 时延是指⼀组数据中的第 90 百分位数， P99 时延是指⼀组数据中的第 99 百分位数】

使用如下命令运行YCSB测试：

```

#编译并运行测试
make ycsb
#清理编译结果
make ycsb_clean

```

三种不同工作负载下的实验数据将分别输出到同一目录下的workload1_statistics.txt、workload2_statistics.txt、workload3_statistics.txt文件中