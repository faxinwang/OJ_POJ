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
The segment a[2...5] is (5, 2, 6, 3). If we sort this segment, we get (2, 3, 5, 6), the third 
number is 5, and therefore the answer to the question is 5.

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
This problem has huge input,so please use c-style input(scanf,printf),or you 
may got time limit exceed.

题目大意:
给定一个规模为N(<= 1e5)的序列, 和M(<=5e3)个查询Q(i,j,k), 求出每个查询中在原序列中[i,j]区间内
第k小的数(也就是升序排序后的第k个数).

解题思路:
使用线段树,在线段树的每个结点中保存该结点区间对应的序列, 并维护序列的
有序性.这样, 就可以在logN时间内查询任意区间中小于等于x的数的个数.

同样可以使用二分对x进行枚举.


时间:
线段树: 7313MS
平方分割,B=1000时: 11860MS
*/


#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100005;

int N,M;
int nums[maxn]; //数据下标从1开始

struct Node
{
    int L,R;
    vector<int> v;
    inline int Mid(){ return (L+R) / 2; }
    inline int Len(){ return R - L + 1; }
};

struct SegmentTree
{
    Node a[maxn<<2];

    //将左右两个子树中的序列合并到父结点中, 跟归并排序的合并过程相同
    inline void push_up(int rt)
    {   
        vector<int>& p = a[rt].v;
        vector<int>& lc = a[rt<<1].v;
        vector<int>& rc = a[rt<<1|1].v;
        p.reserve( a[rt].Len() );
        int i,j, n=lc.size(), m=rc.size();
        for(i=j=0; i<n && j<m;)
        {
            int x = lc[i] < rc[j] ? lc[i++] : rc[j++];
            p.push_back(x);
        }
        while(i<n) p.push_back(lc[i++]);
        while(j<m) p.push_back(rc[j++]);

        // merge(lc.begin(), lc.end(), rc.begin(), rc.end(), 
        //     a[rt].v.begin());
    }

    //每个节点维护一个有序序列 到达页结点时输入数据,并额外保存一份数据到nums[]中
    void build(int L,int R, int rt=1)
    {
        a[rt].L = L;
        a[rt].R = R;
        if(L == R)
        {
            int x;
            scanf("%d", &x);
            nums[L] = x; //保存原始序列
            a[rt].v = vector<int>(1,0);
            a[rt].v[0] = x;
            // printf("%d ", a[rt].v[0]);
            return;
        }
        int m = a[rt].Mid();
        build(L,m, rt<<1);
        build(m+1, R, rt<<1|1);
        push_up(rt);
    }

    //查询区间[L,R]内小于等于x的数的个数.
    int query(int L, int R, int x, int rt=1)
    {
        // printf("L=%d R=%d x=%d rt=%d\n",L,R,x,rt);
        //如果要查询的区间与当前节点内的区间完全不相交,返回0
        if(R < a[rt].L || a[rt].R < L) return 0;

        //如果要查询的区间完全包含于当前结点内的区间,则返回该结点所维护的序列中小于等于x的数的个数.
        if(L <= a[rt].L && a[rt].R <= R)
            return upper_bound(a[rt].v.begin(), a[rt].v.end(), x) - a[rt].v.begin();
        
        //否则去左右子树中去查找
        return query(L, R, x, rt<<1) + query(L, R, x, rt<<1|1);
    }
}tree;


int binSearch(int L,int R,int K)
{
    int low = 1, high = N, mid;
    while(high - low >= 1)
    {
        mid = (low + high) / 2;
        int x = nums[mid];
        tree.query(L,R, x) >= K ? high = mid : low = mid+1;
    }
    return nums[high];
}

int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif
    int L,R, K;
    scanf("%d%d",&N, &M);    
    tree.build(1, N); //建树

    sort(nums+1, nums + N + 1);

    for(int i=0; i<M;++i)
    {
       scanf("%d%d%d",&L,&R,&K);
       printf("%d\n",binSearch(L,R,K));
    }
    

    return 0;
}