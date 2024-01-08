#include<bits/stdc++.h>
using namespace std;
int n,m;
char c;
void scan(int&x){
    while(c=getchar(),!isdigit(c)&&!isalpha(c));
    while(isdigit(c)||isalpha(c)){
        if(isalpha(c))return(void)(x=-1);
        x=x*10+c-'0';
        c=getchar();
    }
}
int main(){
    scan(n),scan(m);
    if(n==-1||m==-1)return puts("NaN"),0;
    printf("%d",n-m);
    return 0;
}