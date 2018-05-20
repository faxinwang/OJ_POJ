/*
Face The Right Way
Time Limit: 2000MS		Memory Limit: 65536K

Description
Farmer John has arranged his N (1 ≤ N ≤ 5,000) cows in a row and many of them are facing 
forward, like good cows. Some of them are facing backward, though, and he needs them all 
to face forward to make his life perfect.

Fortunately, FJ recently bought an automatic cow turning machine. Since he purchased the
discount model, it must be irrevocably preset to turn K (1 ≤ K ≤ N) cows at once, and 
it can only turn cows that are all standing next to each other in line. Each time the 
machine is used, it reverses the facing direction of a contiguous group of K cows in 
the line (one cannot use it on fewer than K cows, e.g., at the either end of the line 
of cows). Each cow remains in the same *location* as before, but ends up facing the 
*opposite direction*. A cow that starts out facing forward will be turned backward by 
the machine and vice-versa.

Because FJ must pick a single, never-changing value of K, please help him determine 
the minimum value of K that minimizes the number of operations required by the machine 
to make all the cows face forward. Also determine M, the minimum number of machine 
operations required to get all the cows facing forward using that value of K.

Input
Line 1: A single integer: N 
Lines 2..N+1: Line i+1 contains a single character, F or B, indicating whether cow i 
is facing forward or backward.

Output
Line 1: Two space-separated integers: K and M

Sample Input
7
B
B
F
B
F
B
B

Sample Output
3 3

Hint
For K = 3, the machine must be operated three times: turn cows (1,2,3), (3,4,5), 
and finally (5,6,7)

题目大意:
N头牛排成一列, 初始时有的朝前有的朝后, 每次可以将一个长度为k的区间[i,i+k-1]内的所有牛改变朝向,
设区间长度为k时使所有牛全部朝前的最少操作次数为M, 求最小的M和其对应的k.

解题思路:
首先对于每一头牛, 操作次数为奇数次跟操作1次效果是一样的, 操作次数为偶数次跟操作0次效果也是一样的.
所以对于每一头牛, 最多只需要操作一次.

然后考虑第0头牛, 其只可能在区间[0,0+k-1]区间内被操作. 如果初始时它是朝向后方的, 则需要对区间[0,0+k-1]
进行一次翻转,使0号牛朝前, 而如果最开始时它本来就是朝前的, 那么就不需要对[0,0+k-1]区间进行操作.不管这次
有没有对0号牛进行操作, 以后也不用再考虑0号牛, 数据规模就减小到了N-1.

考虑如果[i,i+k-1]区间被翻转了, 那么一定是为了让i号牛变为朝前, 但时此次翻转也会改变后面的k-1头牛的朝向,
如果通过数组模拟的话, 就需要花费O(k)的时间来更新后面k-1头牛的状态. 我们可以通过下面的方法将O(k)的时间
优化到O(1):

设f[i] 为如果区间[i,i+k-1]内的牛被翻转了的话, 就为1, 否则为0

这样,在考虑编号为i的牛时, 如果 f[i-k+1]+..+f[i] 为奇数的话, 那么该牛变得与之前的方向相反, 否则其方向
没有改变. 又由于我们可以递推计算 : f[i-k+2] + ...+f[i+1] = f[i-k+1] + ... + f[i] + f[i+1] - f[i-k+1]
也就是加上前面一项,减去最后一项, 就可以在O(1)时间内递推计算出下一个区间中的总和. 然后通过f[i-k+1]+...+f[i]
的和再加上该牛最初的朝向, 就可以知道是否需要对当前区间[i,i+k-1]进行翻转了. 也就可以通过O(n)的时间计算出
给定的K下需要翻转操作的最少次数M.

最后通过枚举k(1<= k <= N), 计算出相应的操作次数m. 保存最小的m和其对应的k值就可以了.就可以在O(N^2)时间内
求出答案, 否则如果通过数组模拟的话, 需要O(N^3)的时间,会超时.

总结与提炼:
这个问题的模型可以总结为开关问题, 也就是一个对象只能在两种状态之间切换的情况, 这种情况下, 一个对象最多只
需要对其进行一次操作(但可能被对其他对象的操作影响而改变状态).
*/


#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn = 5005;
typedef long long LL;

int dir[maxn], N;
int f[maxn]; //f[i] 记录区间[i+k-1]是否进行翻转, 1表示进行了翻转

int calu(int k)
{
    int res=0; //总的翻转次数
    int sum=0; //记录区间[i+k-1]内翻转的次数
    memset(f,0,sizeof(f)); //f数组会多次使用, 没吃使用前需要清0
    for(int i=0; i + k <= N; ++i)
    {
        if( (dir[i] + sum) & 1 )
        {   
            ++res;
            f[i] = 1;
        }
        sum += f[i];
        if(i - k + 1 >= 0) sum -= f[i-k + 1];
    }
    //查看最后的k-1头牛是否方向一致朝前,不一致的话,说明无解
    for(int i=N-k+1; i<N; ++i)
    {
        if((dir[i] + sum) & 1) return -1;
        if(i - k + 1>= 0) sum -= f[i-k + 1];
    }
    return res;
}

void solve()
{
    int M = N;
    int K = 1;
    for(int k=1; k<=N; ++k)
    {
        int m = calu(k);
        // printf("k=%d m=%d\n",k,m);
        if(0 <= m && m < M)
        {
            M = m;
            K = k;
        }
    }
    printf("%d %d\n", K,M);
}

int main()
{
    #ifdef WFX
    freopen("in.txt", "r", stdin);
    #endif
    char ch;
    scanf("%d\n",&N);
    for(int i=0; i<N; ++i)
    {
        scanf("%c\n",&ch);
        dir[i] = ch=='F'? 0 : 1;
    }
    solve();

    return 0;
}