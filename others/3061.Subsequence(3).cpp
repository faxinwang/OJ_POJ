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
方法三:
设以a[s]开始总和最初大于S的连续子序列为a[s]+...+a[t-1],则
a[s+1]+...+a[t-2] < a[s]+...+a[t-2] < S

所以从a[s+1]开始的总和超过S的连续子序列的和如果是a[s+1]+...+a[t'-1]的话, 则
必然有t <= t'. 利用这一性质, 可以设计如下算法:
1.初始时:s = t = sum = 0;
2.只要依然有sum < S,就不断将sum += a[t], 然后 ++t.
3.如果步骤2结束后sum任然小于S则终止, 否则更新res = min(res, t-s)
4.将sum -= a[s], 然后++s, 这一操作之后sum一定变得小于S, 然后回到第2步.

时间复杂度: t是一直增加的, 直到超过N, 所以复杂度为O(N).
*/

#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 1e5+5;
typedef long long LL;

int a[maxn];
int N,S;

int solve()
{
    int res = N+1;
    int s = 1, t=1, sum=0;
    while(1)
    {
        while(t <= N && sum < S) sum += a[t++];
        if(sum < S) break; //therefore, t must > N
        res = min(res, t - s);
        sum -= a[s++];
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