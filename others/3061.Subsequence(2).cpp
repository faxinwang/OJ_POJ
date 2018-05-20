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
方法二:
1.首先计算出原序列的前缀和数组,存放于sum[]中,由于序列由正整数构成, 
  因此前缀和必然是一个递增的数组(为二分搜索创造了条件).
2.使用循环枚举子序列的起点s, 然后用lower_bound()函数在sum数组的[s,N+1)中
  寻找sum[s]+S的位置t, 则t-s就是子序列的长度, 并且子序列的和大于等于S.
3.起点的范围应满足 sum[s] + S <= s[N]

时间复杂度: O(NlogN)
*/

#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 1e5+5;
typedef long long LL;

int a[maxn], sum[maxn];
int N,S;

int solve()
{
    int res = N+1;
    for(int i=1; i<=N; ++i) sum[i] = sum[i-1] + a[i];
    if(sum[N] < S) return 0; //序列的总和都小于S, 显然没有子序列的和满足大于等于S的条件

    //枚举起点s, 二分搜索终点t
    for(int s=1; sum[N] - sum[s] >= S; ++s)
    {
        int t = lower_bound(sum + s, sum + N + 1, sum[s] + S) - sum ;
        res = min(res, t - s);
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