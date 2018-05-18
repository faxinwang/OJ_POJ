/*
Conscription
Time Limit: 1000MS		Memory Limit: 65536K

Description
Windy has a country, and he wants to build an army to protect his country. He 
has picked up N girls and M boys and wants to collect them to be his soldiers. 
To collect a soldier without any privilege, he must pay 10000 RMB. There are 
some relationships between girls and boys and Windy can use these relationships 
to reduce his cost. If girl x and boy y have a relationship d and one of them 
has been collected, Windy can collect the other one with 10000-d RMB. Now given 
all the relationships between girls and boys, your assignment is to find the 
least amount of money Windy has to pay. Notice that only one relationship can 
be used when collecting one soldier.

Input
The first line of input is the number of test case.
The first line of each test case contains three integers, N, M and R.
Then R lines followed, each contains three integers xi, yi and di.
There is a blank line before each test case.

1 ≤ N, M ≤ 10000
0 ≤ R ≤ 50,000
0 ≤ xi < N
0 ≤ yi < M
0 < di < 10000

Output
For each test case output the answer in a single line.

Sample Input
2

5 5 8
4 3 6831
1 3 4583
0 0 6592
0 1 3063
3 3 4975
1 3 2049
4 2 2104
2 2 781

5 5 10
2 4 9820
3 2 6236
3 1 8864
2 4 8326
2 0 5156
2 0 1463
4 1 2439
0 4 4373
3 4 8889
2 4 3133

Sample Output
71071
54223

题目大意:
现需招募N名男边, M名女兵, 每招募一个人需要支付10000RMB, 如果招募的人之间有一些亲密
关系,则可以少花一些钱. 给出若干男女之间的关系,和她们之间的亲密度d, 则招募一个人的费用
为10000 - max(d),d为该人和其它异性的亲密度. 求在合适的招募顺序下招募这些人所需要的
最小的费用.

解题思路:
如果将男兵按照N+1,,N+M编号, 则可以将他们看成N+M个顶点,R条边构成的无向图,
边权为他们之间的亲密度. 需要注意的是, 他们之间可能有多个连通分量(从第一组样例可以看出), 
所以其实够成了森林, 那么问题就变成了最大权森林问题, 可以通过把权值取反,将
问题转化为最小生成树的问题来解决.

需要注意的是, 由于可能不止一个连通分量, 当连通分量不止一个时, 构成生成树的边数
就不再是V-1了, 所以这里最好用kruskal算法来求解最小生成树.

其实也可以将边按权值从大到小排序, 选出权值最大的一些边构成森林,
这样的话最后的答案就是10000*(M+N) - kruskal(R)
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN = 1e4+5;
const int MAXE = 5e4+5;
typedef long long LL;

int p[MAXN*2];

int Find(int x){return p[x]==0? x : p[x] = Find(p[x]); }

void Union(int x, int y)
{
    x = Find(x);
    y = Find(y);
    p[x] = y;
}

bool Same(int x,int y){ return Find(x) == Find(y); }

struct Edge
{
    int form, to, cost;
    bool operator<(const Edge& e)const{return cost < e.cost;}
}eds[MAXE];


int kruskal(int E)
{
    int ans=0,cnt=0;
    sort(eds, eds+E);
    for(int i=0; i<E; ++i) //选取V-1条边就可以了
    {
        if(!Same(eds[i].form, eds[i].to))
        {
            Union(eds[i].form, eds[i].to);
            ans += eds[i].cost;
            ++cnt;
        }
    }
    return ans;
}

int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif
    int T,u,v,w;
    int N, M, R;

    scanf("%d",&T);
    while(T--)
    {
        memset(p, 0, sizeof(p));
        scanf("%d%d%d", &N,&M,&R);
        for(int i=0; i<R; ++i)
        {
            scanf("%d%d%d",&eds[i].form, &eds[i].to, &eds[i].cost);
            //男生的编号用N+v表示
            eds[i].to += N;
            eds[i].cost = -eds[i].cost; //把边权取反.
        }
        printf("%d\n", 10000*(N+M) + kruskal(R));
    }

    return 0;
}