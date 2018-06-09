/*
Palindrome
Time Limit: 3000MS		Memory Limit: 65536K
Description

A palindrome is a symmetrical string, that is, a string read identically from 
left to right as well as from right to left. You are to write a program which, 
given a string, determines the minimal number of characters to be inserted 
into the string in order to obtain a palindrome. 

As an example, by inserting 2 characters, the string "Ab3bd" can be transformed 
into a palindrome ("dAb3bAd" or "Adb3bdA"). However, inserting fewer than 2 characters 
does not produce a palindrome. 

Input
Your program is to read from standard input. The first line contains one integer: 
the length of the input string N, 3 <= N <= 5000. The second line contains one 
string with length N. The string is formed from uppercase letters from 'A' to 'Z', 
lowercase letters from 'a' to 'z' and digits from '0' to '9'. Uppercase and lowercase 
letters are to be considered distinct.

Output
Your program is to write to standard output. The first line contains one integer, 
which is the desired minimal number.

Sample Input
5
Ab3bd

Sample Output
2

题目大意:
给定一个长度为N(<=5000)的字符串s, 可以在任意位置插入任意多个字符, 要使得原字符串变成回文字符串,
至少要插入多少字符.

解题思路:
 典型的区间模型，回文串拥有很明显的子结构特征，即当字符串X是一个回文串时，在X两边各添加
 一个字符'a'后，aXa仍然是一个回文串，我们用d[i][j]来表示A[i...j]这个子串变成回文串所
 需要添加的最少的字符数，那么对于A[i] == A[j]的情况，很明显有 d[i][j] = d[i+1][j-1] 
 （这里需要明确一点，当i+1 > j-1时也是有意义的，它代表的是空串，空串也是一个回文串，
 所以这种情况下d[i+1][j-1] = 0）；当A[i] != A[j]时，我们将它变成更小的子问题求解，
 我们有两种决策：
    1、在A[j]后面添加一个字符A[i]；
    2、在A[i]前面添加一个字符A[j]；
根据两种决策列出状态转移方程为：
    d[i][j] = min{ d[i+1][j], d[i][j-1] } + 1;  (每次状态转移，区间长度增加1)
空间复杂度O(n^2)，时间复杂度O(n^2)

*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 5005;
typedef long long LL;

char s[maxn];
unsigned short d[maxn][maxn];

//记忆化递归 (1704MS)
int dp(int i, int j)
{
    if(i >= j ) return 0;
    if(d[i][j]) return d[i][j];
    return d[i][j] = s[i] == s[j] ? dp(i+1, j-1) : min( dp(i+1, j), dp(i, j-1) ) + 1;
}

//循环 (1282MS)
int dp(int n)
{
    for(int k=1; k<n; ++k)
    {
        for(int i=0,j=k; j<n; ++i,++j) 
            d[i][j] = s[i]==s[j] ? d[i+1][j-1] : min(d[i+1][j], d[i][j-1])+1;
    }
    return d[0][n-1];
}

int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif

    int n;
    scanf("%d%s",&n,s);
    printf("%d\n", dp(n));
    // memset(d,0,sizeof(d));
    // printf("%d\n", dp(0,n-1));

    return 0;
}