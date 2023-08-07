#include<bits/stdc++.h>
using namespace std;
const long long N=1e5,mod=1e9+7;
long long n,k[N+10],a[N+10],ans,ss[N+10],mk,tmp,tn;
long long rem,s,l;
long long Calc(long long x,long long y,long long z){
    if(z<1)return 0;
    return(x%mod*z+1ll*(y<0?y+mod:y)*ss[z])%mod;
}
int main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;++i)scanf("%lld%lld",&k[i],&a[i]),mk=max(mk,k[i]),s+=1ll*k[i]*a[i],l+=k[i];
    for(int i=1;i<=mk;++i)ss[i]=(ss[i-1]+i)%mod;
    s/=l;
    for(int i=1;i<=n;++i)a[i]-=s;
    for(int i=1;i<=n;++i){
        if(rem>=0){
            if(a[i]>=0)ans=(ans+Calc(rem,a[i],k[i]))%mod;
            else if(rem+1ll*k[i]*a[i]<0){
                tmp=rem/(-a[i]),tn=rem%(-a[i]);
                ans=(ans+Calc(rem,a[i],tmp)+((-a[i])-tn)+Calc((-a[i])-tn,-a[i],k[i]-tmp-1))%mod;
            }else ans=(ans+Calc(rem,a[i],k[i]))%mod;
        }else{
            if(a[i]<=0)ans=(ans+Calc(-rem,-a[i],k[i]))%mod;
            else if(rem+1ll*k[i]*a[i]>0){
                tmp=(-rem)/a[i],tn=(-rem)%a[i];
                ans=(ans+Calc(-rem,-a[i],tmp)+(a[i]-tn)+Calc(a[i]-tn,a[i],k[i]-tmp-1))%mod;
            }else ans=(ans+Calc(-rem,-a[i],k[i]))%mod;
        }
        rem+=1ll*k[i]*a[i];
        assert(ans>=0);
    }
    printf("%lld",ans);
    return 0;
}
/*
2
100000 5
10000 5
*/