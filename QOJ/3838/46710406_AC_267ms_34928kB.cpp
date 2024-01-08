#include "bits/stdc++.h"
#define ll long long
using namespace std;
const int N=1e6;
struct poi{
    ll x,y;
    ll operator*(const poi &t)const{
        return x*t.y-y*t.x;
    }
}p[(N<<1)+10];
int T,n,nw,ans;
bool cmp(poi a,poi b){
    if(!a.y){
        if(!b.y)return a.x>b.x;
        if(a.x>0)return 1;
        return b.y<0;
    }
    if(!b.y){
        if(b.x>0)return 0;
        return a.y>0;
    }
    if((a.y>0)!=(b.y>0))return a.y>0;
    return a*b>0;
}
int main()
{
    cin.sync_with_stdio(0),cin.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i)cin>>p[i].x>>p[i].y;
        sort(p+1,p+n+1,cmp);
        for(int i=1;i<=n;++i)p[n+i]=p[i];
        nw=1;
        ans=n;
        for(int i=1;i<=n;++i){
            while(nw<i+n&&p[i]*p[nw]>=0)++nw;
            ans=min(ans,n-(nw-i));
        }
        cout<<ans<<"\n";
    }
    return 0;
}
/*
3
2
1 0
2 0
3
1 0
0 1
-1 -1
5
2 -1
1 2
-1 2
-2 -1
0 -2
*/