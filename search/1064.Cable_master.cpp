/*
Cable master
Time Limit: 1000MS		Memory Limit: 10000K
Description

Inhabitants of the Wonderland have decided to hold a regional programming contest. The 
Judging Committee has volunteered and has promised to organize the most honest contest 
ever. It was decided to connect computers for the contestants using a "star" topology - i.e. 
connect them all to a single central hub. To organize a truly honest contest, the Head of 
the Judging Committee has decreed to place all contestants evenly around the hub on an 
equal distance from it. 

To buy network cables, the Judging Committee has contacted a local network solutions 
provider with a request to sell for them a specified number of cables with equal lengths. 
The Judging Committee wants the cables to be as long as possible to sit contestants as 
far from each other as possible. 

The Cable Master of the company was assigned to the task. He knows the length of each 
cable in the stock up to a centimeter,and he can cut them with a centimeter precision 
being told the length of the pieces he must cut. However, this time, the length is not 
known and the Cable Master is completely puzzled. 

You are to help the Cable Master, by writing a program that will determine the maximal 
possible length of a cable piece that can be cut from the cables in the stock, to get 
the specified number of pieces.

Input
The first line of the input file contains two integer numb ers N and K, separated by a 
space. N (1 = N = 10000) is the number of cables in the stock, and K (1 = K = 10000) 
is the number of requested pieces. The first line is followed by N lines with one number 
per line, that specify the length of each cable in the stock in meters. All cables are 
at least 1 meter and at most 100 kilometers in length. All lengths in the input file 
are written with a centimeter precision, with exactly two digits after a decimal point.

Output
Write to the output file the maximal length (in meters) of the pieces that Cable Master 
may cut from the cables in the stock to get the requested number of pieces. The number 
must be written with a centimeter precision, with exactly two digits after a decimal point. 
If it is not possible to cut the requested number of pieces each one being at least one 
centimeter long, then the output file must contain the single number "0.00" (without quotes).

Sample Input
4 11
8.02
7.43
4.57
5.39

Sample Output
2.00

题目大意:
从N条长度分别为L1,L2,..LN的绳子, 切出K条长度相等的绳子, 求所能得到的最大长度.

解题思路:
直接二分找答案, 但是有很多坑点:
1.虽然只需要保留到小数点后两位, 但是二分的时候我把精度设为1e-3时没过, 1e-4没过,1e-5也没过, 直到1e-9才过.
2.使用double类型保存绳子长度,但使用%lf输出时WA掉了, 但是改为%f就过了, 这点不是很懂.
3.感觉 floor(ans*100)/100 和 int(ans*100)/100.0是等价的, 但是前者过了, 后者依然WA掉了. 
所以写完这一题之后,我重新认识了一次POJ, 太TM神奇了.

*/
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const int maxn = 10005;
const int INF = 1000000;
typedef long long LL;

double a[maxn];

//看能否出k段长度为x的绳子,能切除k段长度为x的绳子时, 返回true
bool check(double x,int N, int K)
{
    int cnt = 0;
    for(int i=0; i<N; ++i) cnt += int(a[i] / x);
    return cnt >= K;
}

double binSearch(int N,int K)
{
    double L = 0, R = INF, M;
    while(R - L > 1e-9) //1e-6会WA掉
    {
        M = (L + R)/2;
        if( check(M, N, K) ) L = M;
        else R = M;
    }
    return M;
}

int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif

    int N,K;
    scanf("%d%d",&N,&K);
    for(int i=0; i<N; ++i) scanf("%lf", a + i);
    double ans = binSearch(N,K);
    printf("%.2f\n",  floor(ans*100) / 100); //写成%lf就过不了, 感觉很神奇
    
    return 0;
}