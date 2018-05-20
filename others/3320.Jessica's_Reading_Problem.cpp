/*
Jessica's Reading Problem
Time Limit: 1000MS		Memory Limit: 65536K

Description
Jessica's a very lovely girl wooed by lots of boys. Recently she has a problem. The 
final exam is coming, yet she has spent little time on it. If she wants to pass it, 
she has to master all ideas included in a very thick text book. The author of that 
text book, like other authors, is extremely fussy about the ideas, thus some ideas 
are covered more than once. Jessica think if she managed to read each idea at least 
once, she can pass the exam. She decides to read only one contiguous part of the 
book which contains all ideas covered by the entire book. And of course, the sub-book 
should be as thin as possible.

A very hard-working boy had manually indexed for her each page of Jessica's text-book 
with what idea each page is about and thus made a big progress for his courtship. 
Here you come in to save your skin: given the index, help Jessica decide which contiguous 
part she should read. For convenience, each idea has been coded with an ID, which is 
a non-negative integer.

Input
The first line of input is an integer P (1 ≤ P ≤ 1000000), which is the number of 
pages of Jessica's text-book. The second line contains P non-negative integers describing 
what idea each page is about. The first integer is what the first page is about, the 
second integer is what the second page is about, and so on. You may assume all integers 
that appear can fit well in the signed 32-bit integer type.

Output
Output one line: the number of pages of the shortest contiguous part of the book 
which contains all ideals covered in the book.

Sample Input
5
1 8 8 8 1

Sample Output
2

题目大意:
一本书中有一些知识点, 每一页会出现某一个知识点, 知识点个数小于页数. 现要通过读某一连续页面
来覆盖书中所有的知识点, 求最少所需要读的页面数.

解题思路:
跟3061的解法类似, 也是用尺取法求解.
只不过这里需要用map<int,int>来记录s,t下标所控制的区间内各知识点所出现的次数,
还要用一个cnt变量记录当前[s,t)区间中出现的知识点的个数.
*/
#include<iostream>
#include<cstdio>
#include<set>
#include<map>
using namespace std;
const int maxn = 1e6+5;
typedef long long LL;

int a[maxn];

int getIdeas(int P)
{
    set<int> ideas;
    for(int i=0; i<P; ++i) ideas.insert(a[i]);
    return ideas.size();
}

int solve(int P)
{
    int N = getIdeas(P);
    int res = P+1, s=0,t=0, cnt=0;
    map<int,int> count; //记录区间[0,t)之间已经出现过的知识点出现的次数
    while(1)
    {
        //如果出现了先的知识点, 就把cnt增加1, 直到找到所有的知识点
        while(t < P && cnt < N) if(count[ a[t++]]++ == 0 ) ++cnt;
        if(cnt < N) break;
        res = min(res, t - s);
        //某一个知识点在当前区间中出现次数为0, 所以知识点个数要减一
        if(--count[ a[s++] ] == 0) --cnt; 
    }
    return res;
}

int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif
    int P;//number of page
    scanf("%d",&P);
    for(int i=0; i<P; ++i) scanf("%d", &a[i]);
    printf("%d\n", solve(P));

    return 0;
}