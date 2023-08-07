#include<iostream>
#include<cstdio>
void write(__int128 x)
{
    if(x==0){puts("0");return;}
    if(x<0)x=-x,putchar('-');
    int s[55],top=0;
    while(x)s[++top]=x%10,x/=10;
    while(top)putchar(s[top--]+'0');
    puts("");
}
int main()
{
    long long a,b;
    std::cin>>a>>b;
    __int128 x=__int128(a)+b;
    write(x);
    return 0;
}