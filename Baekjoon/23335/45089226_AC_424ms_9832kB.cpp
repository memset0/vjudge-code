#include<bits/stdc++.h>
using namespace std;
const int N=1e6;
int T,tn,n,p[N+10],lp[N+10],sz,ls,nw,tmp;
long long ans;
int main(){
    lp[1]=1;
    for(int i=2;i<=N;++i){
        if(!p[i])p[++sz]=i,lp[i]=i;
        for(int j=1;i*p[j]<=N;++j){
            p[i*p[j]]=1,lp[i*p[j]]=p[j];
            if(i%p[j]==0)break;
        }
    }
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n),tn=n,ls=ans=nw=tmp=1;
        while(n!=1){
            if(ls!=lp[n]){
                ans*=tmp,nw=lp[n],tmp=lp[n]+1,ls=lp[n];
            }else{
                nw*=ls,tmp+=nw;
            }
            n/=lp[n];
        }
        ans*=tmp;
        if(ans-tn==tn)puts("perfect");
        else if(ans-tn>tn)puts("abundant");
        else puts("deficient");
    }
    return 0;
}