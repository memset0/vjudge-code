#include<bits/stdc++.h>
#define ll long long
int n,m,t,x,y,mod,ans,v[200010];
std::map<int,int> map;
void solve(int l,int r,int k){
    if(l==r||k<=1){map[r-l+1]++;return;}
    solve(l,l+r>>1,k-1),solve((l+r>>1)+1,r,k-1);
}
int fpow(ll a,int b){ll s=1;for(;b;b>>=1,a=a*a%mod)if(b&1)s=s*a%mod;return s;}
ll f(ll x){return (ll)x*(x-1)%mod*fpow(4,mod-2)%mod;}
ll f(ll x,ll y){
    ll res=(ll)x*y%mod*fpow(2,mod-2)%mod;
    for(int i=1;i<=x;i++)res=(res-v[i+y]+v[i]);
    return (res%mod+mod)%mod;
}
int main(){
#ifdef memset0
    freopen("1.in","r",stdin);
#endif
    scanf("%d%d%d",&n,&m,&mod),solve(1,n,m);
    for(int i=0;i<=n+m;i++)v[i]=(v[i-1]+fpow(i,mod-2))%mod;
    t=map.begin()->first,x=map[t],y=map[t+1];
    printf("%d\n",(x*f(t)+y*f(t+1)+x*(x-1)/2%mod*f(t,t)+x*y%mod*f(t,t+1)+y*(y-1)/2%mod*f(t+1,t+1))%mod);
}