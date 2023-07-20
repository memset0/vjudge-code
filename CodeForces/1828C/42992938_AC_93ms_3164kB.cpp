#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int T,n;
vector<int> a,b,c,d;
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        a.resize(n+2);
        b.resize(n+2);
        c.clear();
        c.resize(n+2);
        d.clear();
        d.resize(n+2);
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        for(int i=1;i<=n;i++){
            cin>>b[i];
        }
        sort(a.begin()+1,a.begin()+n+1);
        sort(b.begin()+1,b.begin()+n+1);
        long long ans=1;
        for(int i=1;i<=n;i++){
            int k=lower_bound(b.begin()+1,b.begin()+n+1,a[i])-b.begin();
            if(k<i){
                ans=0;
                break;
            }
            c[i]+=1;
            c[k]-=1;
            d[i]=d[i-1]+c[i];
            ans=ans*d[i]%mod;
        }
        cout<<ans<<endl;
    }
}