#include<bits/stdc++.h>
using namespace std;
char a[20]; 
int l,s;
bool c(char x,char y) {
    if(x=='i'&&y=='i')return 1;
    if(x=='w'&&y=='w')return 1;
    if(x=='('&&y==')')return 1;
    if(x==')'&&y=='(')return 1;
    return 0;
}
int main() {
    gets(a);
    l=strlen(a);
    s=(l+1)/2;
    for(int i=0;i<(l+1)/2;i++)
        if(c(a[i],a[l-1-i]))
            s--;
    printf("%d\n",s);
    return 0;
}