/*
K-th Number
Time Limit: 20000MS		Memory Limit: 65536K
Case Time Limit: 2000MS

Description
You are working for Macrohard company in data structures department. After failing your previous 
task about key insertion you were asked to write a new data structure that would be able to 
return quickly k-th order statistics in the array segment. 

That is, given an array a[1...n] of different integer numbers, your program must answer a 
series of questions Q(i, j, k) in the form: "What would be the k-th number in a[i...j] segment, 
if this segment was sorted?" 
For example, consider the array a = (1, 5, 2, 6, 3, 7, 4). Let the question be Q(2, 5, 3). 
The segment a[2...5] is (5, 2, 6, 3). If we sort this segment, we get (2, 3, 5, 6), the third number 
is 5, and therefore the answer to the question is 5.

Input
The first line of the input file contains n --- the size of the array, and m --- the number of 
questions to answer (1 <= n <= 100 000, 1 <= m <= 5 000). 
The second line contains n different integer numbers not exceeding 109 by their absolute values 
--- the array for which the answers should be given. 
The following m lines contain question descriptions, each description consists of three numbers: 
i, j, and k (1 <= i <= j <= n, 1 <= k <= j - i + 1) and represents the question Q(i, j, k).

Output
For each question output the answer to it --- the k-th number in sorted a[i...j] segment.

Sample Input
7 3
1 5 2 6 3 7 4
2 5 3
4 4 1
1 7 3

Sample Output
5
6
3

Hint
This problem has huge input,so please use c-style input(scanf,printf),or you may got time limit exceed.

题目大意:
给定一个规模为N(<= 1e5)的序列, 和M(<=5e3)个查询Q(i,j,k), 求出每个查询中在原序列中[i,j]区间内
第k小的数(也就是升序排序后的第k个数).

解题思路:
第一次学习分桶法, 感觉这种方法很有意思.
分桶法的基本思想是把一个很大的集合或序列分成若干个相同大小的,规模更小一些的集合或者序列.
每个桶里面独立维护其最大值最小值或者序列的有序性等. 这样在数据查询的时候可以更高效.桶的
大小设为sqrt(N), N是原始数据规模的大小.

对于这一题, 我们需要维护每个桶内元素的有序性. 然后, 额外保存一份原始序列并对其排序(用于二分搜索).
对于每一个查询Q(i,j,k), 区间[i,j]内的第k小的数一定也是原始序列中的某一个数,基于这一事实, 我们可以
使用二分搜索查找区间[i,j]内的第k小的数. 具体步骤为:
设原始序列为A, 额外保存的排序过的序列为B.
二分枚举B序列中的某个数x, 在桶数组和A序列中查找小于等于x的数的个数cntX, 如果cntX >= k, 说明小于
x的数过多,也就是x有点偏大, 所以接下来再枚举更小的x, 否则枚举更大的x.

查找小于等于x的数的个数,也可以使用二分,只需要在最开始对每个桶内的元素排序, 对于每个桶,
可以使用upper_bound()在logB(B为桶内元素的个数)时间内找出小于等于x的数的个数.
*/
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100005;
const int B = 800; //桶的大小, 


int arr1[maxn], arr2[maxn];//arr1保存初始序列, arr2保存arr1排序后的序列
int N, M;
vector<int> bucket[maxn / B];

int binSearch(int L,int R,int K)
{
    int low = 0, high = N-1, mid;
    while(high - low >= 1)
    {
        mid = (low+high)/2;
        int x = arr2[mid], a=L, b=R+1, cnt=0;

        //计算[a,b)区间中小于x的数的数个
        while(a < b && a % B ) if(arr1[a++] <= x) ++cnt;
        while(a < b && b % B ) if(arr1[--b] <= x) ++cnt;
        while(a < b)
        {
            int t = a / B;
            cnt += upper_bound(bucket[t].begin(), bucket[t].end(), x)
                     - bucket[t].begin();
            a += B;
        }
        //cnt>=K说明小于等于x的数太多了, 所以x太大了, 所以让high=mid把x调小一些
        cnt >= K ? high = mid : low = mid+1;
    }
    return arr2[high];
}

int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif
    int L,R, K;
    scanf("%d%d",&N,&M);
    for(int i=0; i<N;++i)
    {
        scanf("%d",&arr1[i]);
        arr2[i] = arr1[i];
        bucket[i/B].push_back(arr1[i]); //分到对应的桶中去
    }
    
    //计算桶的个数;
    int NB = N / B;
    //对每个桶中的元素进行排序
    for(int i=0; i<NB; ++i) sort(bucket[i].begin(), bucket[i].end());
    //排序初始元素,用于查找原始序列中给定区间中的第K大的数
    sort(arr2, arr2 + N);

    for(int i=0; i<M; ++i)
    {
        scanf("%d%d%d",&L,&R,&K);
        printf("%d\n", binSearch(L-1, R-1, K));
    }

    return 0;
}