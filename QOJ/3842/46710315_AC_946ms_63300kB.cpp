#include "bits/stdc++.h"
#define ll long long
using namespace std;
const int N=1e6,INF=1e9;
int T,k,n,a[N+10],pos[N+10],t;
ll f[N+10][2];
int mn[(N<<2)+10],li[(N<<2)+10],ri[(N<<2)+10],ind[N+10];
void Build(int x,int l,int r){
    li[x]=l,ri[x]=r;
    if(l==r)return(void)(ind[l]=x,mn[x]=INF);
    int mid=(l+r>>1);
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
    mn[x]=min(mn[x<<1],mn[x<<1|1]);
}
void Upd(int x,int v){
    x=ind[x];
    mn[x]=v;
    x>>=1;
    while(x)mn[x]=min(mn[x<<1],mn[x<<1|1]),x>>=1;
}
int Que(int x,int l,int r){
    if(li[x]>r||ri[x]<l||l>r)return INF;
    if(l<=li[x]&&ri[x]<=r)return mn[x];
    return min(Que(x<<1,l,r),Que(x<<1|1,l,r));
}
int Calc(int x){
    if(x+k-1<n)return min(Que(1,0,x-1),Que(1,x+k,n-1));
    return Que(1,(x+k)%n,x-1);
}
int Dis(int x,int y){
    return min((x-y+n)%n,(y-x+n)%n);
}
int main(){
    cin.sync_with_stdio(0),cin.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k;
        for(int i=0;i<n;++i)cin>>a[i],pos[a[i]]=i;
        if(n==k){
            cout<<"0\n";
            continue;
        }
        Build(1,0,n-1);
        f[n][0]=f[n][1]=0;
        Upd(pos[n],n);
        for(int i=n-1;i>=1;--i){
            t=Calc((pos[i]-k+1+n)%n);
            if(t<=n){
                f[i][0]=min(Dis((pos[i]-k+1+n)%n,(pos[t]-k+1+n)%n)+f[t][0],Dis((pos[i]-k+1+n)%n,pos[t])+f[t][1]);
            }else f[i][0]=0;
            t=Calc(pos[i]);
            if(t<=n){
                f[i][1]=min(Dis(pos[i],(pos[t]-k+1+n)%n)+f[t][0],Dis(pos[i],pos[t])+f[t][1]);
            }else f[i][1]=0;
            Upd(pos[i],i);
            //cout<<"F "<<i<<"={"<<f[i][0]<<","<<f[i][1]<<"}\n";
        }
        t=Calc(0);
        //cout<<"t="<<t<<"\n";
        f[0][0]=min(Dis(0,(pos[t]-k+1+n)%n)+f[t][0],Dis(0,pos[t])+f[t][1]);
        cout<<f[0][0]<<"\n";
    }
    return 0;
}
/*
1
5 4


5
5 3
2 4 3 5 1
1 1
1
5 2
5 4 1 3 2
5 4
1 2 3 5 4
5 4
5 1 2 3 4
*/