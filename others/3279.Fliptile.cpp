/*
Fliptile
Time Limit: 2000MS		Memory Limit: 65536K

Description
Farmer John knows that an intellectually satisfied cow is a happy cow who will give 
more milk. He has arranged a brainy activity for cows in which they manipulate an 
M × N grid (1 ≤ M ≤ 15; 1 ≤ N ≤ 15) of square tiles, each of which is colored black 
on one side and white on the other side.

As one would guess, when a single white tile is flipped, it changes to black; when 
a single black tile is flipped, it changes to white. The cows are rewarded when 
they flip the tiles so that each tile has the white side face up. However, the 
cows have rather large hooves and when they try to flip a certain tile, they also 
flip all the adjacent tiles (tiles that share a full edge with the flipped tile). 
Since the flips are tiring, the cows want to minimize the number of flips they have 
to make.

Help the cows determine the minimum number of flips required, and the locations 
to flip to achieve that minimum. If there are multiple ways to achieve the task 
with the minimum amount of flips, return the one with the least lexicographical 
ordering in the output when considered as a string. If the task is impossible, 
print one line with the word "IMPOSSIBLE".

Input
Line 1: Two space-separated integers: M and N 
Lines 2..M+1: Line i+1 describes the colors (left to right) of row i of the grid 
with N space-separated integers which are 1 for black and 0 for white

Output
Lines 1..M: Each line contains N space-separated integers, each specifying how 
many times to flip that particular location.

Sample Input
4 4
1 0 0 1
0 1 1 0
0 1 1 0
1 0 0 1

Sample Output
0 0 0 0
1 0 0 1
1 0 0 1
0 0 0 0

题目大意:
在一个M*N的瓦片网格中, 分布着一些黑色和白色的瓦片, 这些瓦片都是一面白色,一面黑色,可以通过翻转让
某一个瓦片改变正面的颜色. 在翻转某一个瓦片的同时, 与之相邻的上下左右的四个瓦片也会改变颜色,
求让所有瓦片全部都白色朝上的最少翻转次数, 如果存在多解, 则输出字典序最小的解.

解题思路:
首先, 同一个格子翻转两次就会变回原样, 所以每个格子最多只需要翻转一次.

对于样例中最左上角的格子, 可以通过翻转(1,1), (1,2), (2,1)来改变它的颜色, 这样看起起来会很麻烦.
如果第一行的翻转方式确定了, 那对于格子(0,j), 只有(1,j)一个格子能改变它的颜色, 所以我们可以先
枚举第一行的翻转方法, 在根据第一行的状态确定第二行的状态, 如此下去, 如果最后一行的状态合法的话,
那么第一行的这个枚举是可行的. 否则第一行的该次枚举是不合法的.

当枚举完第一行的所有状态并找出所有解后, 就可以得到最优解了.第一行的状态有2^N种,
每次确定完第一行, 都需要O(M*N)的时间确定完剩下的所有行, 所以总时间复杂度为O(M*N*2^N)


用整数表示集合:
前面枚举第一行的状态,利用了整数表示集合的方法,用整数中的二进制位表示集合中元素是否存在
0           空集
1<<i        只含有一个元素{i}
(1<<n)-1    含有全部n个元素的集合
S>>i & 1    判断第i个元素是否属于集合S
S | 1<<i    向集合S中加入第i个元素
S & ~(1<<i) 从集合S中去除第i个元素
S | T       集合S与集合T的并集
S & T       集合S与集合T的交集

按从小到大的顺序枚举集合{a[0],a[1],a[2],..,a[n-1]}中的所有子集:
for(int S=0; S < 1<<n; ++S) { //处理子集 }
//S中的二进制位表示子集中包含的元素

枚举某个集合S的子集:
int s = S;
do
{
    //对子集的处理
    s = (s-1) & S;
}while(s != S); //处理完0之后, 会有-1 & S = S


枚举{a[0],a[1],a[2],...,a[n-1]}所包含的所有大小为k的子集:
int sk = (1<<k)-1, S = 1<<n;
while( sk < S)
{
    //对大小为k的子集进行处理
    int x = sk & -sk, y = sk + x;
    sk = ((sk & ~y) / x >> 1) | y;
}

*/


#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn = 16;

int tile[maxn][maxn]; //保存输入
int flip[maxn][maxn]; //保存中间状态
int best[maxn][maxn]; //保存最优解
int dir[5][2]={0,1,1,0, 0,-1,-1,0, 0,0};
int M,N;


int color(int x,int y)
{
    int s=tile[x][y]; //原本的颜色
    for(int i=0; i<5; ++i)
    {
        int tx = x + dir[i][0];
        int ty = y + dir[i][1];
        //四周和当前位置的影响
        if(0 <= tx && tx < M && 0 <= ty && ty < N) s += flip[tx][ty]; 
    }
    return s & 1; //最终的颜色
}

int calu()
{
    //从第二行开始判断当前行当前列是否需要翻转
    for(int i=1; i < M; ++i)
        for(int j=0; j<N; ++j)
            //上面一个位置是黑色的话,下面这个位置就必须翻转
            if(color(i-1,j) == 1) flip[i][j] = 1;

    //查看最后一行是否全为白色
    for(int j=0; j<N; ++j) if(color(M - 1,j) == 1) return -1; //有黑色
    //统计翻转次数
    int res = 0;
    for(int i=0; i<M; ++i)
        for(int j=0; j<N; ++j)
            res += flip[i][j];
    return res;
}

void solve()
{
    int res = -1;
    for(int i=0,n=1<<N; i<n; ++i) //枚举第一行的所有翻转方法
    {
        memset(flip, 0, sizeof(flip));
        //将第i种方法中的M位取出来放到第一行中
        for(int j=0; j<N; ++j) flip[0][j] = i >> j & 1; 
        int num = calu();
        if(num >=0 && (res < 0 || res > num))
        {
            res = num;
            memcpy(best, flip, sizeof(flip));
        } 
    }
    if(res < 0) printf("IMPOSSIBLE\n");
    else
    {
        for(int i=0; i<M; ++i)
            for(int j=0; j<N; ++j) 
                printf("%d%c", best[i][j], j+1==N? '\n':' ');
    }
}

int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif
    scanf("%d%d",&M,&N);
    for(int i=0; i < M; ++i)
        for(int j=0; j < N; ++j) 
            scanf("%d", &tile[i][j]);
    solve();

    return 0;
}