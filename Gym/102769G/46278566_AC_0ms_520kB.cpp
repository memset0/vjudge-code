#include<bits/stdc++.h>
using namespace std;
int T,n,k;
int query(int x,int k){
    if(x==0)return 0;
    return x/k;
}
int power(int x,int k){
    if(x==1)return 1;
    int s=1;
    while(k--){
        if((long long)s*x>n)return -1;
        s*=x;
    }
    return s;
}
int main(){
#ifdef memset0
    freopen("G.in","r",stdin);
#endif
    ios::sync_with_stdio(0),cin.tie(0);
    cin>>T;
    for(int t=1;t<=T;t++){
        cin>>n>>k;
        int ans=0;
        if(k==1){
            ans=n;
        }else{
            vector<pair<int,int>> seg;
            for(int i=1;;i++){
                auto x=power(i,k);
                if(x==-1)break;
                seg.emplace_back(x,-1);
            }
            for(int i=0;i+1<seg.size();i++){
                seg[i].second=seg[i+1].first-1;
            }
            seg.back().second=n;
            for(int i=0;i<seg.size();i++){
                auto [l,r]=seg[i];
                ans+=query(r,i+1)-query(l-1,i+1);
            }
        }
        cout<<"Case #"<<t<<": "<<ans<<endl;
    }
}