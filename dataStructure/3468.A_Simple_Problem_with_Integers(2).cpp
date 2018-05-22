/*
A Simple Problem with Integers
Time Limit: 5000MS		Memory Limit: 131072K

Case Time Limit: 2000MS

Description
You have N integers, A1, A2, ... , AN. You need to deal with two kinds of operations. One type of 
operation is to add some given number to each number in a given interx. The other is to ask for 
the sum of numbers in a given interx.

Input
The first line contains two numbers N and Q. 1 ≤ N,Q ≤ 100000.
The second line contains N numbers, the initial xues of A1, A2, ... , AN. -1000000000 ≤ Ai ≤ 1000000000.
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
来自挑战程序设计

树状数组擅长于单点更新与区间求和, 但时区间更新效率不高.
这里通过构建两个树状数组bit0,bit1, 使得区间更新和区间查询效率一样高, 都为LogN
设 
sum(i) = sum{a[j]| 1 <= j <= i}
sum(i) = sum(bit1) * i + sum(bit0,i)
那么在区间[L,R]上同时加上x就可以看成:
1.在bit0的L位置加上-x*(L-1)
2.在bit1的L位置加上x
3.在bit0的R+1位置加上x*R
4.在bit1的R+1位置加上-x
这四个操作.
*/

#include<iostream>
#include<cstdio>
using namespace std;
typedef long long LL;
const LL maxn = 100005;

struct BineryIndexedTree
{
    int _N;
    LL bit0[maxn];
    LL bit1[maxn];
    
    inline LL lowbit(LL x){ return x & -x; }

    //建立具有N个元素的树状数组, 下标从1开始
    void build(int N)
    {
        _N = N;
        int x;
        for(int i=1; i<=N; ++i)
        {
            scanf("%d",&x);
            add(bit0, i, x);
        }
    }

    //第i个元素增加x
    void add(LL*a, int i, int x) { for(; i<=_N; i += i&-i ) a[i] += x; }

    //求前n个元素的和
    LL sum(LL* a, int i)
    {
        LL s = 0;
        for(; i>0; i -= i&-i) s += a[i];
        return s;
    }

    void update(int L, int R, int x)
    {
        add(bit0, L, -x * (L-1));
        add(bit1, L, x);
        add(bit0, R+1, x * R);
        add(bit1, R+1, -x);
    }
    
    LL query(int L, int R)
    {
        LL s = 0;
        s += sum(bit0, R) + sum(bit1, R) * R;
        s -= sum(bit0, L-1) + sum(bit1, L-1) * (L-1);
        return s;
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
    tree.build(N);

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
