#include<bits/stdc++.h>
using namespace std;
const int N=4e5+9,p1=998244353,p2=1e9+7,base=131131;
int n,k,c,a[N],w1[N],w2[N],cnt[N],fir[N],s1[N],s2[N],h1[N],h2[N];
int main(){
#ifdef memset0
    freopen("C.in","r",stdin);
#endif
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>k;
    w1[1]=w2[1]=base;
    for(int i=2;i<=k;i++){
        w1[i]=(long long)w1[i-1]*base%p1;
        w2[i]=(long long)w2[i-1]*base%p2;
    }
    for(int i=1;i<=n;i++){
        cin>>a[i];
        cnt[a[i]]++;
        fir[i]=cnt[1];
        s1[i]=(s1[i-1]+w1[a[i]])%p1;
        s2[i]=(s2[i-1]+w2[a[i]])%p2;
    }
    long long tmp=0;
    for(int i=1;i<=k;i++)tmp+=w1[i];
    tmp%=p1;
    for(int i=1;i<=n;i++)h1[i]=(s1[i]-(long long)fir[i]*tmp%p1+p1)%p1;
    tmp=0;
    for(int i=1;i<=k;i++)tmp+=w2[i];
    tmp%=p2;
    for(int i=1;i<=n;i++)h2[i]=(s2[i]-(long long)fir[i]*tmp%p2+p2)%p2;
    // for(int i=1;i<=n;i++)cerr<<fir[i]<<" \n"[i==n];
    // for(int i=1;i<=n;i++)cerr<<h1[i]<<" \n"[i==n];
    // for(int i=1;i<=n;i++)cerr<<h2[i]<<" \n"[i==n];
    map<pair<int,int>,pair<int,int>> mp;
    for(int i=0;i<=n;i++){
        auto hsh=make_pair(h1[i],h2[i]);
        auto it=mp.find(hsh);
        if(it==mp.end()){
            mp[hsh]={fir[i],fir[i]};
        }else{
            it->second.first=min(it->second.first,fir[i]);
            it->second.second=max(it->second.second,fir[i]);
        }
    }
    int ans=0;
    for(const auto &it:mp){
        ans=max(ans,(it.second.second-it.second.first)*k);
    }
    cout<<ans<<endl;
}