#include "bits/stdc++.h"
#define ll long long
#define pi pair<ll,int>
#define f first
#define s second
using namespace std;
const int N=5e5;
struct node{
    int l,r;
    pi mx;
}t[(N<<2)+10];
int n,a[N+10],pos[N+10],tmp,tp;
ll ss;
void Build(int x,int l,int r){
    t[x].l=l,t[x].r=r;
    if(l==r)return(void)(t[x].mx=(pi){a[l],l},pos[l]=x);
    int mid=(l+r>>1);
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
    t[x].mx=max(t[x<<1].mx,t[x<<1|1].mx);
}
void Mod(int x,ll v){
    x=pos[x];
    t[x].mx.f-=v;
    while(x)x>>=1,t[x].mx=max(t[x<<1].mx,t[x<<1|1].mx);
}
int main(){
    cin.sync_with_stdio(0),cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i)cin>>a[i];
    Build(1,1,n);
    for(int i=1;i<=(n<<2)&&t[1].mx.f+ss>=n-1;++i){
        tmp=(t[1].mx.f+ss)/(n-1),tp=t[1].mx.s;
        ss+=tmp,Mod(tp,tmp*n);
    }
    if(t[1].mx.f+ss<n-1)for(int i=1;i<=n;++i)cout<<t[pos[i]].mx.f+ss<<" \n"[i==n];
    else cout<<"Recurrent\n";
    return 0;
}