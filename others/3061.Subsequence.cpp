/*
Subsequence
Time Limit: 1000MS		Memory Limit: 65536K

Description
A sequence of N positive integers (10 < N < 100 000), each of them less than or 
equal 10000, and a positive integer S (S < 100 000 000) are given. Write a program 
to find the minimal length of the subsequence of consecutive elements of the sequence, 
the sum of which is greater than or equal to S.

Input
The first line is the number of test cases. For each test case the program has to 
read the numbers N and S, separated by an interval, from the first line. The numbers 
of the sequence are given in the second line of the test case, separated by intervals. 
The input will finish with the end of file.

Output
For each the case the program has to print the result on separate line of the output file.
if no answer, print 0.

Sample Input
2
10 15
5 1 3 5 10 7 4 9 2 8
5 11
1 2 3 4 5

Sample Output
2
3

题目大意:
给定一个正整数序列和一个正整数S, 求子序列中和大于等于S的子序列的最小长度.

解题思路:
方法一:
暴力枚举子序列的开始下标, 然后寻找自学列和>=S的结束下标. 并不断更新子序列的长度res.
过程中res会越来越小. 所以内存循环会越来越快, 但很不幸还是TLE了.
目测该算法的时间复杂度介于NLogN 与 N^2之间.
*/

#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 1e5+5;
typedef long long LL;

int a[maxn];
int N,S;

int solve()
{
    int res = N+1;
    for(int i=1; i<N; ++i)
    {
        int s = 0;
        for(int j=0; j<res && i+j<=N; ++j)
        {
            s += a[i+j];
            if(s >= S)
            {
                res = min(res, j + 1);
                break;
            }
        }
    }
    return res == N+1 ? 0 : res;
}

int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&N,&S);
        for(int i=1; i<=N; ++i) scanf("%d", &a[i]);
        printf("%d\n", solve());
    }

    return 0;
}