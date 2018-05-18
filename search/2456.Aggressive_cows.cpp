/*
Aggressive cows
Time Limit: 1000MS		Memory Limit: 65536K

Description
Farmer John has built a new long barn, with N (2 <= N <= 100,000) stalls. The stalls 
are located along a straight line at positions x1,...,xN (0 <= xi <= 1,000,000,000). 

His C (2 <= C <= N) cows don't like this barn layout and become aggressive towards 
each other once put into a stall. To prevent the cows from hurting each other, FJ 
want to assign the cows to the stalls, such that the minimum distance between any 
two of them is as large as possible. What is the largest minimum distance?

Input
* Line 1: Two space-separated integers: N and C 
* Lines 2..N+1: Line i+1 contains an integer stall location, xi

Output
* Line 1: One integer: the largest minimum distance

Sample Input
5 3
1
2
8
4
9

Sample Output
3

Hint
OUTPUT DETAILS: 
FJ can put his 3 cows in the stalls at positions 1, 4 and 8, resulting in a minimum 
distance of 3. 
Huge input data,scanf is recommended.

题目大意:
N个牛舍排在一条线上, C头牛要放到这N个牛舍中, 使得任意两头牛之间的距离最大.

解题思路:
二分枚举任意两头牛之间的最短距离x, 如果能够将这C头牛以x的最短距离分配到N个牛舍中, 则尝试更大的x,
否则尝试更小的x. 
判断C头牛能否以x为最小距离放入N个牛舍中的方法为:
将第一头牛放到第一个牛舍(也就是代码中的a[0]位置), 然后在后面找离前一头牛距离大于x的一个牛舍,
将第二头牛分配到该牛舍, 后面的牛安装同样的分配方法分配牛舍, 如果无法成功分配, 返回false.

*/
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 1e6+5;
const int INF = 1e9+5;
typedef long long LL;

int a[maxn]; //保存牛舍的位置
int N,C;

bool check(int x)
{
    int last = 0;
    //为C-1头牛分配牛舍, 每两头牛之间的距离要>= x, 第一头牛分配在a[0]位置
    for(int i=1; i<C; ++i) 
    {
        int cur = last + 1; 
        while(cur < N && a[cur] - a[last] < x) ++cur;
        if(cur == N) return false; //无法分配成功
        last = cur;
    }
    return true;
}

int binSearch()
{
    
    int L=0, R = INF, M;
    sort(a, a+N);
    
    while(R - L > 1)
    {
        M = L + (R - L)/2;
        check(M)? L = M : R = M;
    }
    return L; //L每次都是可以成功分配的值,在循环过程中L只会不断增大, 所以L就是最后的答案
}

int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif

    scanf("%d%d",&N, &C);
    
    for(int i=0; i<N; ++i) scanf("%d", &a[i]);

    printf("%d\n", binSearch());

    return 0;
}