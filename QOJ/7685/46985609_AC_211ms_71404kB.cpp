#include<bits/stdc++.h>
using namespace std;
const int N=5e5+9;
int T,n,m,ans,mex,a[N],nxt[N],tmp[N],s[N];
vector<int> bkt[N];
vector<pair<int,int>> qry[N];
inline void add(int k,int x){
    for(;k<N;k+=k&-k)s[k]+=x;
}
inline int ask(int k,int r=0){
    for(;k;k-=k&-k)r+=s[k];
    return r;
}
inline void add_query(int l,int r,int x){
    qry[l].emplace_back(r,x);
}
int main(){
#ifdef memset0
    freopen("B.in","r",stdin);
#endif
    ios::sync_with_stdio(0),cin.tie(0);
    cin>>T;
    while(T--){
        vector<int> val;
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            val.push_back(a[i]);
        }
        sort(val.begin(),val.end());
        val.erase(unique(val.begin(),val.end()),val.end());
        mex=val.size()+1;
        for(int i=0;i<val.size();i++)
            if(val[i]!=i+1){
                mex=i+1;
                break;
            }
        ans=val.size()-mex;
        for(int k:val){
            bkt[k].clear();
            tmp[k]=-1;
        }
        for(int i=1;i<=n;i++){
            qry[i].clear();
            bkt[a[i]].push_back(i);
        }
        for(int i=n;i>=1;i--){
            nxt[i]=tmp[a[i]];
            tmp[a[i]]=i;
        }
        for(int k:val){
            int lst=0;
            for(int i:bkt[k]){
                if(lst+1<=i-1){
                    add_query(lst+1,i-1,k);
                }
                lst=i;
            }
            if(lst+1<=n)add_query(lst+1,n,k);
        }
        fill_n(s,n+5,0);
        for(int i=n;i>=1;i--){
            add(i,1);
            if(nxt[i]!=-1){
                add(nxt[i],-1);
            }
            for(auto [r,x]:qry[i]){
                // cerr<<"query "<<i<<" "<<r<<" "<<x<<" >> "<<ask(r)<<endl;
                ans=max(ans,ask(r)-x);
            }
        }
        cout<<ans<<endl;
    }
}