/*
Tautology
Time Limit: 1000MS		Memory Limit: 65536K
Description

WFF 'N PROOF is a logic game played with dice. Each die has six faces representing 
some subset of the possible symbols K, A, N, C, E, p, q, r, s, t. A Well-formed 
formula (WFF) is any string of these symbols obeying the following rules:

p, q, r, s, and t are WFFs
if w is a WFF, Nw is a WFF
if w and x are WFFs, Kwx, Awx, Cwx, and Ewx are WFFs.
The meaning of a WFF is defined as follows:
p, q, r, s, and t are logical variables that may take on the value 0 (false) or 1 (true).
K, A, N, C, E mean and, or, not, implies, and equals as defined in the truth table below.
Definitions of K, A, N, C, and E
  w  x	  Kwx	  Awx	   Nw	  Cwx	  Ewx
  1  1	  1	       1	   0	  1	      1
  1  0	  0	       1	   0	  0	      0
  0  1	  0	       1	   1	  1	      0
  0  0	  0	       0	   1	  1	      1
A tautology is a WFF that has value 1 (true) regardless of the values of its variables. 
For example, ApNp is a tautology because it is true regardless of the value of p. On the 
other hand, ApNq is not, because it has the value 0 for p=0, q=1.

You must determine whether or not a WFF is a tautology.

Input
Input consists of several test cases. Each test case is a single line containing a WFF 
with no more than 100 symbols. A line containing 0 follows the last case.

Output
For each test case, output a line containing tautology or not as appropriate.

Sample Input

ApNp
ApNq
0
Sample Output

tautology
not

------------------------------------------------------------------------------
   题意分析：
      输入由p、q、r、s、t、K、A、N、C、E共10个字母组成的逻辑表达式WFF
      其中 
        p、q、r、s、t的值为1（true）或0（false），即逻辑变量.
 
        K、A、N、C、E为逻辑运算符，含义如下：
         K --> and:  w && x
         A --> or:  w || x
         N --> not :  !w
         C --> implies :  (!w) || x
         E --> equals :  w == x
 
      问WFF是否为【永真式】 (大前提：【输入格式保证是合法的】)
 
 
    解题思路：
      所谓的永真式, 就是不管WFF中的逻辑变量取任何值, 整个逻辑表达式的值始终为真.
      题目给出的逻辑变量共5个, 根据排列组合共 2^5 = 32 种组合变化
      那么只要计算WFF在这32种组合中的所有结果, 若均为真, 则WFF是永真式.
 
      那么问题剩下如何求解WFF.
 
        以样例输入的WFF表达式为例：ApNq
          其真正的含义是： A(p, N(q))
 
        更为复杂的情况是：EKpNAqrCsNt
          其含义是：E(K(p, N(A(q, r)), C(s, N(t)))
 
      对于要求解这类嵌套表达式的值, 最好的数据结构是栈：
        从最内层开始计算, 逐层向外推演
 
      在本题中, 由于只存在一目和二目运算符, 因此内层的运算总是在表达式末端,
      为此推演WFF表达式的算法是：
        从WFF表达式最后一个字符向前迭代：
        ① 遇到逻辑变量，则把该逻辑变量的当前值(0或1)直接压栈
        ② 遇到逻辑算符, 则根据是一目算符或二目算符，从栈顶取出对应两个逻辑变量值计算后, 把结果值压栈
 
      由于题目已经给出了一个大前提：【输入格式保证是合法的】
      因此整个过程无需考虑WFF表达式是否存在异常的情况，
      所以根据上述算法运算到最后，栈内必定只剩一下一个元素，该元素就是整个表达式的值.
 
      ================================================================================
      另外有个小技巧：
        由于存在5个逻辑变量, 常规枚举会产生5层循环嵌套.
        考虑到这5个变量只有0/1值, 可以用一个bit代表一个变量, 将5个变量编码成一个byte, 
        那就可以优化成一层循环（枚举[0, 31]），通过掩码取某个逻辑变量的值即可 

 参考: [ http://exp-blog.com/2018/06/15/pid-417/ ]

*/


#include<iostream>
#include<cstdio>
#include<cstring>
#include<stack>
using namespace std;

#define _K(a, b) ((a) && (b))   // K --> and
#define _A(a, b) ((a) || (b))   // A --> or
#define _N(a)    (!(a))         // N --> not
#define _C(a, b) ((!(a)) || (b))  // C --> implies
#define _E(a, b) ((a) == (b))   // E --> equals


const char P_MASK = 1<<0;
const char Q_MASK = 1<<1;
const char R_MASK = 1<<2;
const char S_MASK = 1<<3;
const char T_MASK = 1<<4;

char value(char ch, char code)
{
    switch(ch)
    {
        case 'p': return code & P_MASK ? 1 : 0;
        case 'q': return code & Q_MASK ? 1 : 0;
        case 'r': return code & R_MASK ? 1 : 0;
        case 's': return code & S_MASK ? 1 : 0;
        case 't': return code & T_MASK ? 1 : 0;
    }
    return 2;
}

bool calc(char* s, char code)
{
    stack<bool> stk;
    for(int i=strlen(s)-1; i>=0; --i)
    {
        char val = value(s[i], code);
        if(val <= 1) stk.push(val);  //s[i] 为逻辑变量
        else //s[i] 为逻辑运算符
        {
            if(s[i] == 'N')
            {
                // if(stk.size() < 1) return false; //题目保证不会出现这种情况
                bool a = stk.top(); stk.pop();
                stk.push( _N(a) );
            }
            else
            {
                // if(stk.size() < 2) return false; //题目保证不会出现这种情况
                bool a = stk.top(); stk.pop();
                bool b = stk.top(); stk.pop();
                switch(s[i]) //因为最后入栈的是最左边的逻辑变量, 因此先出栈的变量作为逻运算辑符的左操作数
                {
                    case 'K': stk.push( _K( a,b ) );     break;
                    case 'A': stk.push( _A( a,b ) );     break;
                    case 'C': stk.push( _C( a,b ) );     break;
                    case 'E': stk.push( _E( a,b ) );     break;
                }
            }
        }
    }
    return stk.size() == 1 && stk.top() == true;
}

int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif
    char s[105];
    while(scanf("%s",s) && s[0] != '0')
    {
        bool isTautology=true;
        //枚举p, q, r, s, t的取值情况, 一共有2^5=32种, 如果所有取值情况下表达式的结果都是true, 则该表达式
        //就是所谓的"永真式", 否则不是
        for(char code = 0; code < 32 && isTautology; ++code) isTautology &= calc(s, code);
        printf("%s\n", isTautology ? "tautology" : "not");
    }

    return 0;
}
