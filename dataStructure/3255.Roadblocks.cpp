/*
Roadblocks
Time Limit: 2000MS		Memory Limit: 65536K

Description
Bessie has moved to a small farm and sometimes enjoys returning to visit one of her best 
friends. She does not want to get to her old home too quickly, because she likes the 
scenery along the way. She has decided to take the second-shortest rather than the 
shortest path. She knows there must be some second-shortest path.

The countryside consists of R (1 ≤ R ≤ 100,000) bidirectional roads, each linking two 
of the N (1 ≤ N ≤ 5000) intersections, conveniently numbered 1..N. Bessie starts at 
intersection 1, and her friend (the destination) is at intersection N.

The second-shortest path may share roads with any of the shortest paths, and it may 
backtrack i.e., use the same road or intersection more than once. The second-shortest 
path is the shortest path whose length is longer than the shortest path(s) (i.e., 
if two or more shortest paths exist, the second-shortest path is the one whose length 
is longer than those but no longer than any other path).

Input
Line 1: Two space-separated integers: N and R 
Lines 2..R+1: Each line contains three space-separated integers: A, B, and D that 
describe a road that connects intersections A and B and has length D (1 ≤ D ≤ 5000)

Output
Line 1: The length of the second shortest path between node 1 and node N

Sample Input
4 4
1 2 100
2 4 200
2 3 250
3 4 100

Sample Output
450

Hint
Two routes: 1 -> 2 -> 4 (length 100+200=300) and 1 -> 2 -> 3 -> 4 (length 100+250+100=450)

题目大意:
某街区共有R条道路, N个路口. 道路可以双向通行.问从1号路口到N号路口的次短路长度是多少.
同一条边可以经过多次.

解题思路:
通过对dijkstra算法稍微修改一下, 就可以得到源点到任意点的次短路. 算法思想如下:
到某个顶点v的次短路要么是其他某个点u的最短路再加上u->v的边, 要么是到u的次短路
加上u->v的边. 因此需要求源点到所有顶点的最短路和次短路. 可以在dijkstra算法中
更新和维护这两组数据.

*/
#include<iostream>
#include<cstdio>
#include<queue>
#include<vector>
using namespace std;
const int MAXV = 5e3+5;
const int MAXE = 1e5+5;
const int INF = 1<<30;
typedef long long LL;

typedef pair<int,int> Pair;
struct Edge
{
    int to, cost;
    Edge(int to=0, int cost=0):to(to),cost(cost){}
};

vector<Edge> G[MAXV];
priority_queue<Pair, vector<Pair>, greater<Pair> > Q;
int dist1[MAXV], dist2[MAXV];
int V,E;

void dijkstra()
{
    fill(dist1, dist1+V+1, INF);
    fill(dist2, dist2+V+1, INF);
    dist1[1] = 0; //源点为1, 终点为N. 注意只需要将源点到自己的最短距离设为0,次短距离并不为0
    Q.push(Pair(0,1)); //源点为1, 到自己的距离为0
    while(!Q.empty())
    {
        Pair p = Q.top(); Q.pop();
        int u = p.second, d = p.first;
        if(dist2[u] < d) continue;
        for(int i=0,n=G[u].size(); i<n; ++i)
        {
            Edge &e = G[u][i];
            int d2 = d + e.cost;
            //更新最短路
            if(d2 < dist1[e.to] )
            {
                swap(dist1[e.to], d2);
                Q.push(Pair(dist1[e.to], e.to));
            }
            //更新次短路
            if(d2 < dist2[e.to])
            {
                swap(dist2[e.to], d2);
                Q.push(Pair(dist2[e.to], e.to));
            }
        }
    }
}

int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif
    int u,v,w;
    scanf("%d%d",&V,&E); //number of vertex, number of edge
    for(int i=0; i<E; ++i)
    {
        scanf("%d%d%d", &u, &v, &w);
        G[u].push_back(Edge(v,w));
        G[v].push_back(Edge(u,w));
    }
    dijkstra();
    printf("%d\n", dist2[V]);

    return 0;
}