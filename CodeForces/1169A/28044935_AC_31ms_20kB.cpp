#include <bits/stdc++.h>
using namespace std;
int n,a,b,x,y;
void read(){scanf("%d%d%d%d%d",&n,&a,&x,&b,&y);}
void work(){
    while(a!=x&&b!=y){
        a=a%n+1,b--;
        if(b==0) b=n; // 123
        if(a==b) cout<<"Yes"<<endl,exit(0);
    }
    cout<<"NO"<<endl;
}
int main(){
    read();
    work();
    return 0;
} // 1231231