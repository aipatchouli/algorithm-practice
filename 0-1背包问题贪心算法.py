# 对于题目描述的静态分配寻找最大值问题可以使用贪心算法
# 如果是动态问题可以使用模拟退火算法
# 或者使用《云环境下基于神经网络和群搜索优化的资源分配机制》中提及的双向拍卖模型

import sys
a = list(map(int, input().split()))  # 用数组a来存储用户的个数 cpu个数 内存大小
a1 = a[0]  # 用户个数 n
a2 = a[1]  # cpu的个数 x
a3 = a[2]  # 内存大小 y
b = []  # 用二维数组b来存储用户的报价信息,共n行3列
b1 = [0]*a1  # 数组b1存储单位cpu价格
b2 = [0]*a1  # 数组b2存储单位内存价格
p1 = [0]*a1
p2 = [0]*a1  # 记录编号
cpunum_sum_0 = 0  # cpu累加个数初始化为0
sto_sum_0 = 0  # 内存累加初始化为0
prize_sum_0 = 0  #总价值
cpunum_sum_1 = 0  # cpu累加个数初始化为0
sto_sum_1 = 0   # 内存累加初始化为0
prize_sum_1 = 0 #总价值
c0 = []  # 记录输出用户编号
c1 = []
 
for i in range(a1):  # 输入用户报价cpu数，内存容量，价格
    b.append(list(map(int, input().split())))
 
 
for k in range(a1):   # 计算用户报价的cpu和内存的单位价格
    b1[k] = b[k][2]/b[k][0]  # cpu单位价格
    b2[k] = b[k][2]/b[k][1]  # 内存单位价格
    p1[k] = k
    p2[k] = k  # 记录用户编号
 
for i in range(0, a1-1):  # 按CPU单位价格进行排序，并且记录编号
    for j in range(1, a1-i):
        if b1[j]> b1[j-1]:
            tmp = b1[j-1]
            b1[j-1] = b1[j]
            b1[j] = tmp
            tmp = p1[j-1]
            p1[j-1] = p1[j]
            p1[j] =tmp
 
for i in range(0, a1-1):  # 按内存单位价格进行排序，并且记录编号
    for j in range(1, a1-i):
        if b2[j]> b2[j-1]:
            tmp = b2[j-1]
            b2[j-1] = b2[j]
            b2[j] = tmp
            tmp = p2[j-1]
            p2[j-1] = p2[j]
            p2[j] =tmp
 
# 约束条件为不能超过cpu总个数，不能超过总容量，按分别按cpu和内存单位价格从大到小开始累加
for i in range(a1):
    if cpunum_sum_0+b[p1[i]][0] <= a2 and sto_sum_0+b[p1[i]][1] <= a3:
        cpunum_sum_0 = cpunum_sum_0+b[p1[i]][0]
        sto_sum_0 = sto_sum_0+b[p1[i]][1]
        prize_sum_0 = prize_sum_0+b[p1[i]][2]
        c0.append(p1[i]+1)
    
for i in range(a1):
    if cpunum_sum_1+b[p2[i]][0] <= a2 and sto_sum_1+ b[p2[i]][1] <= a3:
        cpunum_sum_1 = cpunum_sum_1 + b[p2[i]][0]
        sto_sum_1 = sto_sum_1 + b[p2[i]][1]
        prize_sum_1 = prize_sum_1 + b[p2[i]][2]
        c1.append(p1[i]+1)
       
if prize_sum_0 > prize_sum_1:  # 比较按cpu和内存单位价格获得的总收益输出较大者
    print(prize_sum_0)  
    print(c0)  # 输出用户序列
else:
    print(prize_sum_1)
    print(c1)  # 输出用户序列
