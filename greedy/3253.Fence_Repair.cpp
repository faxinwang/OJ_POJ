/*
Description

Farmer John wants to repair a small length of the fence around the pasture. He measures 
the fence and finds that he needs N (1 ≤ N ≤ 20,000) planks of wood, each having some 
integer length Li (1 ≤ Li ≤ 50,000) units. He then purchases a single long board just 
long enough to saw into the N planks (i.e., whose length is the sum of the lengths Li). 
FJ is ignoring the "kerf", the extra length lost to sawdust when a sawcut is made; you 
should ignore it, too.

FJ sadly realizes that he doesn't own a saw with which to cut the wood, so he mosies 
over to Farmer Don's Farm with this long board and politely asks if he may borrow a saw.

Farmer Don, a closet capitalist, doesn't lend FJ a saw but instead offers to charge 
Farmer John for each of the N-1 cuts in the plank. The charge to cut a piece of wood 
is exactly equal to its length. Cutting a plank of length 21 costs 21 cents.

Farmer Don then lets Farmer John decide the order and locations to cut the plank. 
Help Farmer John determine the minimum amount of money he can spend to create the 
N planks. FJ knows that he can cut the board in various different orders which will 
result in different charges since the resulting intermediate planks are of different 
lengths.

Input

Line 1: One integer N, the number of planks 
Lines 2..N+1: Each line contains a single integer describing the length of a needed plank
Output

Line 1: One integer: the minimum amount of money he must spend to make N-1 cuts
Sample Input

3
8
5
8
Sample Output

34
Hint

He wants to cut a board of length 21 into pieces of lengths 8, 5, and 8. 
The original board measures 8+5+8=21. The first cut will cost 21, and should be used to 
cut the board into pieces measuring 13 and 8. The second cut will cost 13, and should 
be used to cut the 13 into 8 and 5. This would cost 21+13=34. If the 21 was cut into 
16 and 5 instead, the second cut would cost 16 for a total of 37 (which is more than 34).

题目大意:
将一个很长的木料切割成N个长度分别为L[1],L[2]...,L[N]的短木料,
当将一个长度为a的木料切割为两个长度分别为a,b的木料时, 会产生a+b的耗费.
切割木料的顺序不限, 求最小的总耗费.
eg:将一个长度为5的木料切割为长度分别为1,1,3的木料,
方案一:
先将5切割为1,4, 耗费为5
在将4切割为1,3, 耗费为4
总耗费为9.

方案二:
先将5切割成2,3, 耗费为5,
在将2切割为1,1, 耗费为2
总耗费为7.

解题思路:
可以假设已经有了长度分别为L[1],L[2],..,L[N]的木料, 然后将他们组合成一整个长木料, 
组合a,b时产生a+b的耗费, 这样就变成了构造赫夫曼树的过程.用优先级队列很容易实现.
时间复杂度为O(NlogN)
*/

#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
const int maxn = 1e9;
typedef long long LL;


int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif
    int N,x;
    priority_queue<int, deque<int> , greater<int> > Q;
    scanf("%d",&N);
    for(int i=0;i<N; ++i)
    {
        scanf("%d",&x);
        Q.push(x);
    }
    LL ans = 0,t;
    while(Q.size() > 1)
    {
        t = 0;
        t += Q.top(); Q.pop();
        t += Q.top(); Q.pop();
        ans += t;
        Q.push(t);
    }
    cout<<ans<<endl;

    return 0;
}