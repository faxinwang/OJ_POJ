/*
A Simple Problem with Integers
Time Limit: 5000MS		Memory Limit: 131072K

Case Time Limit: 2000MS

Description
You have N integers, A1, A2, ... , AN. You need to deal with two kinds of operations. One type of 
operation is to add some given number to each number in a given interval. The other is to ask for 
the sum of numbers in a given interval.

Input
The first line contains two numbers N and Q. 1 ≤ N,Q ≤ 100000.
The second line contains N numbers, the initial values of A1, A2, ... , AN. -1000000000 ≤ Ai ≤ 1000000000.
Each of the next Q lines represents an operation.
"C a b c" means adding c to each of Aa, Aa+1, ... , Ab. -10000 ≤ c ≤ 10000.
"Q a b" means querying the sum of Aa, Aa+1, ... , Ab.

Output
You need to answer all Q commands in order. One answer in a line.

Sample Input
10 5
1 2 3 4 5 6 7 8 9 10
Q 4 4
Q 1 10
Q 2 4
C 3 6 3
Q 2 4

Sample Output
4
55
9
15

Hint
The sums may exceed the range of 32-bit integers.

解题思路:
标准线段树模板题, 写了好多次这个模板, 这次改了一下模板风格:
1.把获取结点区间长度的函数Len()拿到了Node结构体里面, 这样写起来感觉更简洁.
2.获取结点区间中点的函数Min()也拿到Node里面来了.
3.在build()的时候边创建线段树边读取叶子结点上的数据, 这样节省了一边读一边插入的时间(NlogN).
4.在处理区间的时候不再判断结点上的区间和要操作的区间是否相等, 而是判断结点上的区间是否被要
  操作的区间覆盖, 如果被覆盖就不用继续往下递归了(这种写法比前面一种要简介一些). 嗯, 感觉我的
  线段树的模板风格还是蛮清晰简洁的,以后就这么写.

5.在push_down()的时候, 是把父结点的add值乘以子结点的区间长度再加到子结点的sum中去, 而不是
  把父结点的add值累加到子结点的add值之后, 再用子结点的add值乘以其区间长度累加到子结点的sum中去, 
  被这个小失误折腾了好长时间, 心疼.
*/

#include<iostream>
#include<cstdio>
using namespace std;
typedef long long LL;
const LL maxn = 100005;

struct Node
{
    LL L,R;
    LL add , sum;
    LL Mid(){ return L + (R - L)/2; }
    LL Len(){ return R - L + 1; }
};

struct SegTree
{
    Node a[maxn<<6];

    inline void push_up(LL rt){ a[rt].sum = a[rt<<1].sum + a[rt<<1|1].sum; }

    inline void push_down(LL rt)
    {
        if(a[rt].L == a[rt].R) return;
        LL lc = rt<<1, rc=lc+1;
        a[lc].add += a[rt].add;
        a[rc].add += a[rt].add;
        a[lc].sum += a[rt].add * a[lc].Len();
        a[rc].sum += a[rt].add * a[rc].Len();
        a[rt].add = 0;
    }

    void build(LL L, LL R, LL rt=1)
    {
        a[rt].L = L;
        a[rt].R = R;
        a[rt].add = 0;
        if(L == R)
        {
            scanf("%lld" , &a[rt].sum);
            return;
        }
        LL m = a[rt].Mid();
        build(L, m, rt<<1);
        build(m+1, R, rt<<1|1);
        push_up(rt);
    }

    void update(LL L, LL R, LL val, LL rt=1)
    {
        if(L <= a[rt].L && a[rt].R <= R)
        {
            a[rt].sum += val * a[rt].Len();
            a[rt].add += val;
            return;
        }
        if(a[rt].add) push_down(rt);

        LL mid = a[rt].Mid();
        if(L <= mid) update(L, R, val, rt<<1);
        if(mid < R) update(L, R, val, rt<<1|1);
        push_up(rt);
    }

    LL query(LL L,LL R, LL rt=1)
    {
        
        if(L <= a[rt].L && a[rt].R <= R) return a[rt].sum;
        if(a[rt].add) push_down(rt);
        LL mid = a[rt].Mid();
        LL sum = 0;
        if(L <= mid) sum += query(L, R, rt<<1);
        if(mid < R) sum += query(L, R, rt<<1|1);
        return sum;
    }

    void DFS(LL rt = 1)
    {
        if(a[rt].L == a[rt].R)
        {
            printf("%lld ", a[rt].sum);
            return ;
        } 
        DFS(rt<<1);
        DFS(rt<<1|1);
        printf("[%d,%d]=%d\n", a[rt].L, a[rt].R, a[rt].sum);
    }

}tree;


int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif
    LL N,Q;
    char op[3];
    LL a,b,c;
    
    scanf("%lld%lld",&N,&Q);
    tree.build(1,N);
    // tree.DFS();
    // cout<<endl;

    while(Q--)
    {
        scanf("%s%lld%lld",op, &a,&b);
        if(op[0] == 'Q') printf("%lld\n", tree.query(a,b));
        else 
        {
            scanf("%lld", &c);
            tree.update(a,b,c);
        }
    }

    return 0;
}
