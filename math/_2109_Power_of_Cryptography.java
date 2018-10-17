/*
Power of Cryptography
Time Limit: 1000MS		Memory Limit: 30000K
Description

Current work in cryptography involves (among other things) large prime 
numbers and computing powers of numbers among these primes. Work in this 
area has resulted in the practical use of results from number theory 
and other branches of mathematics once considered to be only of theoretical interest. 
This problem involves the efficient computation of integer roots of numbers. 
Given an integer n>=1 and an integer p>= 1 you have to write a program that 
determines the n th positive root of p. In this problem, given such integers 
n and p, p will always be of the form k to the nth. power, for an integer 
k (this integer is what your program must find).

Input
The input consists of a sequence of integer pairs n and p with each integer 
on a line by itself. For all such pairs 1<=n<= 200, 1<=p<10^101 and there 
exists an integer k, 1<=k<=10^9 such that k^n = p.

Output
For each integer pair n and p the value k should be printed, i.e., the number 
k such that k^n =p.

Sample Input
2 16
3 27
7 4357186184021382204544

Sample Output
4
3
1234

解题思路:
二分查找 + 高精度

*/

import java.io.File;
import java.io.FileNotFoundException;
import java.math.BigInteger;
import java.util.Scanner;

public class _2109_Power_of_Cryptography 
{
	static Scanner sc;
	static
	{
		try {
			sc = new Scanner(new File("./math/in.txt"));
		}catch(FileNotFoundException e){ sc = new Scanner(System.in); }
	}
	
	static BigInteger pow(BigInteger k, int n)
	{
		BigInteger r = BigInteger.valueOf(1);
		for(int i=0; i<n; ++i) r = r.multiply(k);
		return r;
	}
	
	public static void main(String[] args) throws FileNotFoundException
	{
		
		while(sc.hasNextLine())
		{
			int n = sc.nextInt();
			String s = sc.next();
			BigInteger p = new BigInteger(s);
			String num = "1";
			for(int i=1,len=s.length()/n; i<len; ++i) num += "0";
			BigInteger low = new BigInteger(num);
			BigInteger high = new BigInteger(num+"00");
			BigInteger mid=null;
			while(low.compareTo(high) <= 0)
			{
				
				mid = low.add(high).divide(BigInteger.valueOf(2));
//				System.out.println("low :" + low + " mid :" + mid + "  high :" + high);
				BigInteger kn = pow(mid,  n);
				int res = kn.compareTo(p);
				if(res == 0) break;
				if(res<0) low = new BigInteger(mid.toString()).add(BigInteger.valueOf(1));
				else high = new BigInteger(mid.toString()).add(BigInteger.valueOf(-1));
			}
			System.out.println(mid);
		}
		
		sc.close();
	}
}
