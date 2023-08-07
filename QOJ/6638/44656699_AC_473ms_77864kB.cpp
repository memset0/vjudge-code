#include<bits/stdc++.h>
using namespace std;
const int N=1e6;
int T,n,p[N+10],sz[N+10],l,r,mid,f[N+10],prt[N+10],flg[N+10];
vector<int>e[N+10];
bool Check(int x){
    for(int i=n;i>=1;--i){
        f[i]=0;
        for(int j=0;j<e[i].size();++j)f[i]+=f[e[i][j]];
        f[i]=(i!=1)+max(0,f[i]-x);
    }
    return !f[1];
}
int main(){
    //freopen("H.in","r",stdin);
    //freopen("H.ans","w",stdout);
    ios::sync_with_stdio(0),cin.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i)vector<int>().swap(e[i]);
        for(int i=2;i<=n;++i)cin>>p[i],e[p[i]].push_back(i);
        l=1,r=n-1;
        while(l<r){
            mid=l+r>>1;
            if(Check(mid))r=mid;
            else l=mid+1;
        }
        for(int i=n;i>=1;--i){
            sz[i]=1;
            for(int j=0;j<e[i].size();++j)sz[i]+=sz[e[i][j]];
        }
        Check(l-1),flg[1]=1;
        for(int i=2;i<=n;++i)flg[i]=(flg[p[i]]&&f[i]!=1);
        for(int i=1;i<=n;++i){
            if(sz[i]-1==l)prt[i]=(f[1]==1&&flg[i]);
            else prt[i]=(sz[i]-1>l);
        }
        for(int i=1;i<=n;++i)cout<<prt[i];
        cout<<'\n';
    }
    return 0;
}