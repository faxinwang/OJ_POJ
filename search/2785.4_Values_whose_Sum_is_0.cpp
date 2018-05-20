/*
4 Values whose Sum is 0
Time Limit: 15000MS		Memory Limit: 228000K
Case Time Limit: 5000MS

Description
The SUM problem can be formulated as follows: given four lists A, B, C, D of integer 
values, compute how many quadruplet (a, b, c, d ) ∈ A x B x C x D are such that 
a + b + c + d = 0 . In the following, we assume that all lists have the same size n .

Input
The first line of the input file contains the size of the lists n (this value can 
be as large as 4000). We then have n lines containing four integer values (with 
absolute value as large as 228 ) that belong respectively to A, B, C and D .

Output
For each input file, your program has to write the number quadruplets whose sum is zero.

Sample Input
6
-45 22 42 -16
-41 -27 56 30
-36 53 -37 77
-36 30 -75 -46
26 -38 -10 62
-32 -54 -6 45

Sample Output
5

Hint
Sample Explanation: Indeed, the sum of the five following quadruplets is zero: 
(-45, -27, 42, 30), (26, 30, -10, -46), (-32, 22, 56, -46),(-32, 30, -75, 77), 
(-32, -54, 56, 30).

题目大意:
有A,B, C,D四个长度为n的整数序列, 设a,b,c,d分别是序列A,B,C,D中的元素, 求有多少种
a+b+c+d=0的组合.

解题思路:
如果简单粗暴地用四重循环分别枚举a,b,c,d, 肯定会超时.
我们可以枚举并列出C,D这两个序列中所有元素的两两之和, 然后排序.
再从A,B中枚举两个元素a,b, 再从排序后的序列中二分查找 a+b的相反数的个数k,
则a,b这两个元素与cd序列中的k个元素的和为0, 将k累加到答案中即可.
*/


#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 4005;
typedef long long LL;

int a[maxn], b[maxn], c[maxn],d[maxn];
int cd[maxn*maxn];

int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif
    
    int n;
    scanf("%d",&n);
    for(int i=0; i<n; ++i)
    {
        scanf("%d", &a[i]);
        scanf("%d", &b[i]);
        scanf("%d", &c[i]);
        scanf("%d", &d[i]);
    }
    
    for(int i=0; i<n; ++i)
        for(int j=0; j<n; ++j)
            cd[i*n + j] = c[i] + d[j];

    int N = n * n;
    sort(cd, cd + N);

    int ans = 0;
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n; ++j)
        {
            int ab = -(a[i] + b[j]);
            ans += upper_bound(cd, cd + N, ab) - lower_bound(cd, cd + N, ab);
        }
    }
    printf("%d\n", ans);

    return 0;
}