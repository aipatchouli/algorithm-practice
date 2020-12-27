// 这个问题相当于0-1背包问题，区别在于有两个约束条件
// 动态规划一般用来求最值，核心问题在于穷举，但不是暴力穷举，一般需要设置一个dp table,
// 需要找出状态转移方程，对本题而言，dp table value[i][j][k] 的含义就是对前i个选项
// 在总cpu = j, ram = k 且不超过约束条件的情况向能获得的最大利润
// 状态转移或者说判断是否要选择第i个选项，标准是在不超过约束条件的情况，寻求最大价值

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int consumer_num = 0 ;  //用户报价数量
    int cpu_num_total = 0 ; //资源供应商 CPU 总数
    int ram_num_total = 0 ; //资源供应商 RAM 总数

    cin >> consumer_num >> cpu_num_total >> ram_num_total ;

    vector<vector<int>> consumer_offer(consumer_num) ;  //用户报价信息（CPU，RAM，PRICE）
    for (int i = 0; i < consumer_offer.size(); i++)
    {
        consumer_offer[i].resize(3) ;
    }
    for (int i = 0; i < consumer_offer.size(); i++)
    {
        for (int j = 0; j < consumer_offer[0].size(); j++)
        {
            consumer_offer[i][j] = 0 ;
            cin >> consumer_offer[i][j] ;
        }
    }

    vector<vector<int>> w(consumer_num) ;  //用户报价信息（CPU，RAM）,方便计算
    for (int i = 0; i < w.size(); i++)
    {
        w[i].resize(2) ;
    }
    for (int i = 0; i < w.size(); i++)
    {
        for (int j = 0; j < w[0].size(); j++)
        {
            w[i][j] = consumer_offer[i][j] ;
        }
    }

    vector<int> v(consumer_num) ;  //用户报价信息（PRICE）,方便计算
    for (int i = 0; i < v.size(); i++)
    {
        v[i] =  consumer_offer[i][consumer_offer[0].size() -1];
    }

    vector<vector<vector<int>>> value(consumer_num + 1) ;    //DP TABLE
    for (int i = 0; i < value.size(); i++)
    {
       value[i].resize(cpu_num_total + 1) ;
    }
    for (int i = 0; i < value.size(); i++)
    {
        for (int j = 0; j < value[0].size(); j++)
        {
            value[i][j].resize(ram_num_total + 1) ;
        }
    }
    for (int i = 0; i < value.size(); i++)
    {
        for (int j = 0; j < value[0].size(); j++)
        {
            for (int k = 0; k < value[0][0].size(); k++)
            {
                value[i][j][k] = 0 ;
            }
        }
    }

    int cpu = cpu_num_total ;
    int ram = ram_num_total ;

    for (int i = 1; i <= consumer_num; i++)
    {
        for (int j = cpu_num_total; j >= 0; j--)
        {
            for (int k = ram_num_total; k >= 0; k--)
            {
                if (j < w[i-1][0] || k < w[i-1][1])     //判断是否要选择替换
                {
                    value[i][j][k] = value[i-1][j][k] ; 
                }  
                else if (value[i-1][j][k] <= value[i-1][j-w[i-1][0]][k-w[i-1][1]] + v[i-1])
                {
                    value[i][j][k] = value[i-1][j-w[i-1][0]][k-w[i-1][1]] + v[i-1] ;    //状态转移方程
                }
                else
                {
                    value[i][j][k] = value[i-1][j][k] ;
                }
            }
        }
    }

    vector<int> distinguish(consumer_num) ;    //准备判断哪个用户被选中
    for (int i=0; i < consumer_num; i++)
    {
        distinguish[i] = 0 ;
    }

    int j = cpu_num_total ;
    int k = ram_num_total ;
    for (int i=consumer_num; i > 0; i--)     //从尾遍历，当value变大时说明选择
    {
        if (value[i][j][k] > value[i-1][j][k])
        {
            distinguish[i-1] = 1 ;
            j -= w[i-1][0] ;
            k -= w[i-1][1] ;
        }
    }

    int cpuoffered = 0 ;
    int ramoffered = 0 ;
    cout << "最大收益为：" << value[consumer_num][cpu_num_total][ram_num_total] << endl ;
    cout << "被选择用户为：" ;
    for (int i=0; i < consumer_num; i++)
    {
        if (distinguish[i])
        {
            cout << i+1 << "号" << " " ;
            cpuoffered += w[i][0] ;
            ramoffered += w[i][1] ;
        }
    }
    cout << endl ;
    cout << "cpu分配总量：" << cpuoffered << "\n" << "ram分配总量：" << ramoffered << endl ;
    return 0 ;
    
}