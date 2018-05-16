/*
Time Limit: 1000MS		Memory Limit: 30000K
Total Submissions: 1712		Accepted: 576
Description

Background 
In 1801, Carl Friedrich Gauss (1777-1855) published his "Disquisitiones Arithmeticae",
 which basically created modern number theory and is still being sold today. One of 
 the many topics treated in his book was the problem of quadratic residues. 

Consider a prime number p and an integer a !≡ 0 (mod p). Then a is called a quadratic 
residue mod p if there is an integer x such that 
x2 ≡ a (mod p), 
and a quadratic non residue otherwise. Lagrange (1752-1833) introduced the following 
notation, called the "Legendre symbol": 
        
(a/p) =  1  if a is a quadratic residue mod p
(a/p) = -1  if a is a quadratic non residue mod p

For the calculation of these symbol there are the following rules, valid only for 
distinct odd prime numbers p, q and integers a, b not divisible by p: 
 
The statements 1. to 3. are obvious from the definition, 4. is called the Completion
Theorem, and 5. is the famous Law of Quadratic Reciprocity for which Gauss himself 
gave no less than six different proofs in the "Disquisitiones Arithmeticae". 
Knowing these facts, one can calculate all possible Legendre symbols as in the 
following example: 

Input
The first line contains the number of scenarios. 
For each scenario, there is one line containing the integers a and p separated by a 
single blank, where 2 < p < 109 is an odd prime, and a satisfies both a !≡ 0 (mod p)
and |a| <= 109.

Output
Start the output for every scenario with a line containing "Scenario #i:", where i 
is the number of the scenario starting at 1. Then print a single line containing (a/p), 
followed by a blank line.

Sample Input
3
29 79
2 29
1 3

Sample Output
Scenario #1:
-1

Scenario #2:
-1

Scenario #3:
1

*/


#include<iostream>
#include<cstdio>
using namespace std;
typedef long long LL;

LL pow_mod(LL a, LL n, LL mod)
{
    LL ans = 1;
    a %= mod;
    while(n)
    {
        if(n&1) ans = ans * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return ans;
}

/*
计算x^2 = a (mod p)的最小整数解x
先判断是否有解, 再根据剩余类特殊判断.
O(logn*logn)
*/
LL sqr_mod(LL a, LL p)
{
    LL x, b;
    if(p == 2) return a % p;
    if(pow_mod(a , (p-1)/2, p) == 1)
    {
        if(p % 4 == 3) x = pow_mod(a, (p+1)/4, p);
        else
        {
            for(b=1; pow_mod(b, (p-1)/2, p) == 1; ++b );
            LL i = (p-1)/2;
            LL k = 0;
            do{
                i /= 2;
                k /= 2;
                if((pow_mod(a, i, p) * pow_mod(b, k, p)+1) % p == 0) k += (p-1)/2;
            }while(i % 2 == 0);
            x = pow_mod(a, (i+1)/2, p) * pow_mod(b, k/2, p) % p;
        }
        if(x * 2 > p) x = p - x;
        //return x;
        return 1; //本题有解时返回1, 而不用求出解
    }
    return -1; //无解
}



int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif
    LL T,a,p;
    cin>>T;
    for(int kiss=1; kiss<=T; ++kiss)
    {
        cin>>a>>p;
        // if(a < 0) a += p;
        if(a < 0) a = (a % p + p) % p;
        // printf("Scenario #%d:\n%lld\n\n", kiss, sqr_mod(a,p));
        printf("Scenario #%d:\n%d\n\n", kiss, (pow_mod(a,(p-1)/2, p)==1)? 1 : -1);
    }
    return 0;
}