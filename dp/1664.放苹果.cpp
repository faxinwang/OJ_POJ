/*
放苹果
Time Limit: 1000MS		Memory Limit: 10000K
Description
把M个同样的苹果放在N个同样的盘子里，允许有的盘子空着不放，问共有多少种不同的分法？
（用K表示）5，1，1和1，5，1 是同一种分法。

Input
第一行是测试数据的数目t（0 <= t <= 20）。以下每行均包含二个整数M和N，以空格分开。1<=M，N<=10。

Output
对输入的每组数据M和N，用一行输出相应的K。

Sample Input
1
7 3

Sample Output
8

解题思路:
状态定义: f[i][j]表示往i个同样的苹果放到j个同样的盘子里面的方案数
当i==1时, 由于盘子都是一样的, 一个苹果放到哪个盘子都算一种放法, 因此f[1][j]=1;
当j==1时, 所有苹果都放到唯一的盘子里面, 只有一种放法 f[i][1]=1;
当i<j时,  最少会空出j-i个盘子, 因此方案数与f[i][i]是相同的f[i][j] = f[i][i];
当i==j时, 如果所有盘子都不空着, 则正好每个盘子都放一个苹果,这是一种方案,如果空出一个盘子的方案数为f[i][j-1]
          此时f[i][j]=f[i][j-1]+1;
当i>j时,  如果所有盘子都不空着, 则每个盘子至少有一个苹果,这种情况和从每个盘子里面拿出一个苹果之后的方案数相同,因此
          f[i][j] = f[i-j][j]. 如果空出一个盘子, 则f[i][j] = f[i][j-1], 因此综合的: f[i][j]=f[i-j][j] + f[i][j-1]
*/
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 15;
typedef long long LL;

int f[maxn][maxn];

int solve(int M,int N)
{
    LL ans = 0;
    if(f[M][N]) return f[M][N]; //返回已经计算过的值,避免重复计算
    if(M == 1 || N == 1) ans = 1;
    if(M < N) ans = solve(M,M);
    if(M == N) ans = solve(M,N-1) + 1;
    if(M > N) ans = solve(M - N, N) + solve(M, N-1);
    return f[M][N] = ans; //记录已经算过的值
}

int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif
    int T,M,N;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&M,&N);
        printf("%d\n", solve(M,N));
    }


    return 0;
}