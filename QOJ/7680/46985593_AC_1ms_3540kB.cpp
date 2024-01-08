#include<bits/stdc++.h>
using namespace std;
const int N=59;
int n,m,a[N];
struct point{
    int x,y;
    inline bool operator<(const point &rhs)const{
        return x==rhs.x?y<rhs.y:x<rhs.x;
    }
    inline bool operator==(const point &rhs)const{
        return x==rhs.x&&y==rhs.y;
    }
    point operator*(const int rhs)const{
        return {x*rhs,y*rhs};
    }
    friend point operator+(const point &a,const point &b){
        return {a.x+b.x,a.y+b.y};
    }
    friend point operator-(const point &a,const point &b){
        return {a.x-b.x,a.y-b.y};
    }
}p[N];
// const point X={1,-10},Y={1,-11},W=X+Y;
const point X={1,-10000},Y={1,-10001},W=X+Y;
pair<point,int> t[N];
int main(){
#ifdef memset0
    freopen("H.in","r",stdin);
#endif
    ios::sync_with_stdio(0),cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>t[i].first.x>>t[i].first.y>>t[i].second;
    }
    sort(t+1,t+n+1);
    int m=0;
    for(int i=1;i<=n;i++){
        p[i]=t[i].first;
        a[i]=t[i].second;
        m=max(m,a[i]);
    }
    cout<<m<<endl;
    int cnt=1;
    for(int x=1;x<=m;x++){
        vector<point> ans;
        int lst=-1;
        auto link=[&](int u,int v){
            ++cnt;
            ans.push_back(p[u]+W*cnt-Y);
            for(int i=u+1;i<v;i++){
                ans.push_back(p[i]+W*cnt);
            }
            ans.push_back(p[v]+W*cnt-X);
        };
        for(int i=1;i<=n;i++){
            if(a[i]>=x){
                if(x>1&&lst!=-1){
                    link(lst,i);
                }
                lst=i;
                ans.push_back(p[i]);
            }
        }
        if(ans.size()==1){
            ++cnt;
            ans.push_back(ans.back()+W*cnt-Y);
        }
        ans.erase(unique(ans.begin(),ans.end()),ans.end());
        cout<<ans.size()<<' ';
        for(int i=0;i<ans.size();i++){
            cout<<ans[i].x<<' '<<ans[i].y<<" \n"[i+1==ans.size()];
        }
        // for(int i=0;i+1<ans.size();i++)cerr<<"Segment "<<ans[i].x<<' '<<ans[i].y<<' '<<ans[i+1].x<<' '<<ans[i+1].y<<endl;
    }
}