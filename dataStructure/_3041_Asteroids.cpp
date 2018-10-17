/*
Asteroids
Time Limit: 1000MS		Memory Limit: 65536K
Description

Bessie wants to navigate her spaceship through a dangerous asteroid field in the shape 
of an N x N grid (1 <= N <= 500). The grid contains K asteroids (1 <= K <= 10,000), 
which are conveniently located at the lattice points of the grid. 

Fortunately, Bessie has a powerful weapon that can vaporize all the asteroids in any 
given row or column of the grid with a single shot.This weapon is quite expensive, so 
she wishes to use it sparingly.Given the location of all the asteroids in the field, 
find the minimum number of shots Bessie needs to fire to eliminate all of the asteroids.

Input
* Line 1: Two integers N and K, separated by a single space. 
* Lines 2..K+1: Each line contains two space-separated integers R and C (1 <= R, C <= N)
 denoting the row and column coordinates of an asteroid, respectively.

Output
* Line 1: The integer representing the minimum number of times Bessie must shoot.

Sample Input
3 4
1 1
1 3
2 2
3 2

Sample Output
2

Hint
INPUT DETAILS: 
The following diagram represents the data, where "X" is an asteroid and "." is empty space: 
X.X 
.X. 
.X. 

OUTPUT DETAILS: 
Bessie may fire across row 1 to destroy the asteroids at (1,1) and (1,3), and then she may 
fire down column 2 to destroy the asteroids at (2,2) and (3,2).

解题思路:
把方阵看做一个特殊的二分图（以行列分别作为两个顶点集V1、V2，其中| V1|=| V2|）
然后把每行x或者每列y看成一个点，而障碍物(x,y)可以看做连接x和y的边。按照这种思路构图后。问题就转化
成为选择最少的一些点(x或y)，使得这些点覆盖了所有的边，其实这就是最小点覆盖问题。
再利用二分图最大匹配的Konig定理：最小点覆盖数 = 最大匹配数
见图1

*/

#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn = 505;

int g[maxn][maxn]; //vertex number starting from 1
int match[maxn];
bool used[maxn];
int N;

bool find(int x)
{
    for(int y=1; y<=N; ++y)
    {
        if(g[x][y] && !used[y])
        {
            used[y] = 1;
            if(match[y] == 0 || find(match[y]) )
            {
                match[y] = x; //为x找到了匹配:y
                // match[x] = y;
                return true;
            }
        }
    }
    return false; //没有为x找到匹配
}

int hungary(int n)
{
    int cnt=0;
    for(int x=1; x<=n; ++x)
    {
        //在为下一个x寻找匹配的时候, 可能会滕出之前已经匹配过的对象而为该对象重新寻找匹配
        //因此需要消除使用标记, 否则就无法为之重新寻找匹配, 也就无法为后续要匹配的对象滕出一些对象来
        memset(used, 0 , sizeof(used)); 
        if(find(x)) ++cnt;
    }
    return cnt;
}

int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif
    int K, x, y;
    scanf("%d%d",&N,&K);
    for(int i=0; i<K; ++i)
    {
        scanf("%d%d",&x,&y);
        g[x][y] = 1;
    }

    printf("%d\n", hungary(N));


    return 0;
}