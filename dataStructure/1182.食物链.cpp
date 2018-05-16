/*
Description
动物王国中有三类动物A,B,C，这三类动物的食物链构成了有趣的环形。A吃B， B吃C，C吃A。 
现有N个动物，以1－N编号。每个动物都是A,B,C中的一种，但是我们并不知道它到底是哪一种。 
有人用两种说法对这N个动物所构成的食物链关系进行描述： 
第一种说法是"1 X Y"，表示X和Y是同类。 
第二种说法是"2 X Y"，表示X吃Y。 
此人对N个动物，用上述两种说法，一句接一句地说出K句话，这K句话有的是真的，有的是假的。
当一句话满足下列三条之一时，这句话就是假话，否则就是真话。 
1）	当前的话与前面的某些真的话冲突，就是假话； 
2）	当前的话中X或Y比N大，就是假话； 
3）	当前的话表示X吃X，就是假话。 
你的任务是根据给定的N（1 <= N <= 50,000）和K句话（0 <= K <= 100,000），输出假话的总数。 

Input
第一行是两个整数N和K，以一个空格分隔。 
以下K行每行是三个正整数 D，X，Y，两数之间用一个空格隔开，其中D表示说法的种类。 
若D=1，则表示X和Y是同类。 
若D=2，则表示X吃Y。

Output
只有一个整数，表示假话的数目。

Sample Input
100 7
1 101 1 
2 1 2
2 2 3 
2 3 3 
1 1 3 
2 3 1 
1 5 5

Sample Output
3

解题思路:
用并查集表示同类物种.
对于每一个编号x(1<= x <=N), 用 
x 表示 x 属于A类物种, 
x + N 表示 x 属于B物种, 
x + N * 2 表示 x 属于C物种.
则当 a=x (1 <= a <= N) 和 b=y+N (N <= b <= 2N) 属于同一个集合时, 
就表示 x 属于 A 物种, y属于物种B这两个事件同时成立.

基于上面的定义,有:
如果x和y是同类成立的话, 
    x+N, y+N 是同类也一定同时成立;
    x+N*2, y+N*2 是同类也也定成立.
如果x吃y成立的话, 则 
    x属于A类物种, y+N属于B类物种, 也一定同时成立; 
    x+N处于B类物种, y+N*2处于C类物种 也一定同时成立;
    x+N*2处于C类物种, y属于A类物种, 也一定同时成立.
*/
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 5e4+5;
typedef long long LL;

int p[maxn * 3]; //1...N 表示A物种, N+1...N*2 表示B物种 2N+1,...N*3表示C物种.
int h[maxn * 3]; //存储树的高度

int Find(int x){ return p[x]==0? x : p[x] = Find(p[x]); }

bool Same(int x,int y){ return Find(x)==Find(y); }

void Union(int x,int y)
{
    x = Find(x), y=Find(y);
    if(x == y) return;
    if(h[x] < h[y]) p[x] = y; //将一个高度较小的树挂到较高的树根上, 不会导致高树的高度增大.
    else
    {
        p[y] = x;
        if(h[x] == h[y]) ++h[x];
    } 
}

int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif
    int N,K,ans=0;
    int op,x,y;
    scanf("%d%d",&N,&K);
    for(int i=0; i<K; ++i)
    {
        scanf("%d%d%d",&op,&x,&y);
        //编号不合法
        if(x < 1 || N < x || y < 1 || N < y )
        {
            ++ans;
            continue;
        }

        if(op == 1) //X和Y是同类。
        {
            //如果x和y是同类, 则x和y+N一定不是同类, x和y+N*2一定也不是同类
            if(Same(x, y + N) || Same(x, y + N * 2))
            {
                ++ans;
                continue;
            }
            //合并同类
            Union(x, y); 
            Union(x + N, y + N);
            Union(x + N * 2, y + N * 2);
        }
        else //x吃y
        {
            //x吃y,则x和y一定不是同类, x+N*2也一定不是同类.
            if(Same(x, y) || Same(x, y + N * 2))
            {
                ++ans;
                continue;
            }
            Union(x, y + N);
            Union(x + N, y + N * 2);
            Union(x + N * 2, y);
        }
    }
    printf("%d\n", ans);


    return 0;
}