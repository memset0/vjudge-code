#include<bits/stdc++.h>
using namespace std;
int n,m,p;
int main(){
    scanf("%d%d",&n,&m);
    p=m;
    for(int i=1;i<=n;i+=2){
        if(!p){
            for(int j=1;j<=m;++j)printf("%d%c",j==1," \n"[j==m]);
            if(i+1<=n)for(int j=1;j<=m;++j)printf("%d%c",j==1," \n"[j==m]);
        }else{
            for(int j=1;j<=m;++j)printf("%d%c",j==p," \n"[j==m]);
            if(i+1<=n)for(int j=1;j<=m;++j)printf("%d%c",j==p," \n"[j==m]);
            --p; 
        }
    }
    return 0;
}