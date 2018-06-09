#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 15;
typedef long long LL;

int f[maxn][maxn];

int solve(int M,int N)
{
    LL ans = 0;
    if(f[M][N]) return f[M][N]; //返回已经计算过的值,避免重复计算
    if(M <= 1 || N <= 1) ans = 1;
    if(M < N) ans = solve(M,M);
    if(M == N) ans = solve(M,N-1) + 1;
    if(M > N) ans = solve(M - N, N) + solve(M, N-1);
    return f[M][N] = ans; //记录已经算过的值
}

int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif
    int T,M,N;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&M,&N);
        printf("%d\n", solve(M,N));
    }


    return 0;
}