/*
487-3279
Time Limit: 2000MS		Memory Limit: 65536K
Description

Businesses like to have memorable telephone numbers. One way to make a telephone number 
memorable is to have it spell a memorable word or phrase. For example, you can call the 
University of Waterloo by dialing the memorable TUT-GLOP. Sometimes only part of the 
number is used to spell a word. When you get back to your hotel tonight you can order a 
pizza from Gino's by dialing 310-GINO. Another way to make a telephone number memorable 
is to group the digits in a memorable way. You could order your pizza from Pizza Hut by 
calling their ``three tens'' number 3-10-10-10. 

The standard form of a telephone number is seven decimal digits with a hyphen between 
the third and fourth digits (e.g. 888-1200). The keypad of a phone supplies the mapping 
of letters to numbers, as follows: 

A, B, and C map to 2 
D, E, and F map to 3 
G, H, and I map to 4 
J, K, and L map to 5 
M, N, and O map to 6 
P, R, and S map to 7 
T, U, and V map to 8 
W, X, and Y map to 9 

There is no mapping for Q or Z. Hyphens are not dialed, and can be added and removed 
as necessary. The standard form of TUT-GLOP is 888-4567, the standard form of 310-GINO 
is 310-4466, and the standard form of 3-10-10-10 is 310-1010. 

Two telephone numbers are equivalent if they have the same standard form. (They dial the same number.) 

Your company is compiling a directory of telephone numbers from local businesses. As 
part of the quality control process you want to check that no two (or more) businesses 
in the directory have the same telephone number. 

Input

The input will consist of one case. The first line of the input specifies the number of 
telephone numbers in the directory (up to 100,000) as a positive integer alone on the line. 
The remaining lines list the telephone numbers in the directory, with each number alone on a 
line. Each telephone number consists of a string composed of decimal digits, uppercase 
letters (excluding Q and Z) and hyphens. Exactly seven of the characters in the string will
 be digits or letters. 

Output

Generate a line of output for each telephone number that appears more than once in any form. 
The line should give the telephone number in standard form, followed by a space, followed by 
the number of times the telephone number appears in the directory. Arrange the output lines 
by telephone number in ascending lexicographical order. If there are no duplicates in the 
input print the line: 

No duplicates. 

Sample Input

12
4873279
ITS-EASY
888-4567
3-10-10-10
888-GLOP
TUT-GLOP
967-11-11
310-GINO
F101010
888-1200
-4-8-7-3-2-7-9-
487-3279

Sample Output

310-1010 2
487-3279 4
888-4567 3

解题思路:
1.用数组保存字符到数组的映射关系
2.将输入的每个电话号码转化为用数字表示的形式,并用map<string,int>统计每个电话号码出现的次数
3.遍历map<string,int>,按遍历顺序输出value值大于1的电话号码(注意格式转化)
*/


#include<iostream>
#include<cstdio>
#include<string>
#include<map>
using namespace std;

map<string, int> m;
char d[128];

void init()
{
    d['A']=d['B'] = d['C'] = '2';
    d['D']=d['E'] = d['F'] = '3';
    d['G']=d['H'] = d['I'] = '4';
    d['J']=d['K'] = d['L'] = '5';
    d['M']=d['N'] = d['O'] = '6';
    d['P']=d['R'] = d['S'] = '7';
    d['T']=d['U'] = d['V'] = '8';
    d['W']=d['X'] = d['Y'] = '9';
    d['0'] = '0';
    d['1'] = '1';
    d['2'] = '2';
    d['3'] = '3';
    d['4'] = '4';
    d['5'] = '5';
    d['6'] = '6';
    d['7'] = '7';
    d['8'] = '8';
    d['9'] = '9';
}


int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif
    init();

    register string x;
    char s[50];
    register int n;
    scanf("%d",&n);
    for(register int i=0; i<n; ++i)
    {
        scanf("%s",s);
        x = "";
        for(int i=0; s[i]; ++i) if(s[i] != '-') x += d[s[i]];
        ++m[x];
    }

    map<string,int>::iterator pos = m.begin(), end = m.end();
    bool noDuplicate = true;
    for(; pos != end; ++pos)  if(pos->second > 1) 
    {
        const char* s = pos->first.c_str();
        printf("%c%c%c-%s %d\n",s[0],s[1],s[2], s+3, pos->second);
        noDuplicate = false;
    }
    if(noDuplicate) printf("No duplicates.\n");

    return 0;
}