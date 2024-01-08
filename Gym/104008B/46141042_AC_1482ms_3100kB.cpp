#include<bits/stdc++.h>
using namespace std;
using uint=unsigned int;
const int N=409,M=1<<18;
int n,m,pre[M],use[M],dis[M];
struct atom{
    int s,x,y;
    bool fl;
    uint upd;
}a[N][6],t[6];
inline int getc(){
    int c=getchar();
    while(!isupper(c))c=getchar();
    return c;
}
inline int geti(){
    int c=getchar();
    int x=0;
    while(!isdigit(c))c=getchar();
    while(isdigit(c))x=x*10+c-'0',c=getchar();
    return x;
}
int main(){
#ifdef memset0
    freopen("B.in","r",stdin);
#endif
    n=geti(),m=geti();
    for(int i=1;i<=n;i++){
        for(int j=0;j<m;j++){
            char x=getc();
            if(x=='O')a[i][j].s=0;
            else if(x=='W')a[i][j].s=1;
            else if(x=='T')a[i][j].s=2;
            else if(x=='M')a[i][j].s=3;
            else if(x=='R')a[i][j].s=4;
            a[i][j].x=geti();
            a[i][j].y=geti();
            // fprintf(stderr,"a[%d][%d] = %d %d %d\n",i,j,a[i][j].s,a[i][j].x,a[i][j].y);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<m;j++){
            if(!t[j].s){
                if(a[i][j].s){
                    t[j].s=a[i][j].s;
                }
                t[j].x=max(t[j].x,a[i][j].x);
                t[j].y=max(t[j].y,a[i][j].y);
            }
        }
    }
    for(int k=1;k<=n;k++){
        for(int i=0;i<m;i++){
            if(a[k][i].x>t[i].x||a[k][i].y>t[i].y){
                a[k][i].fl=true;
            }
            if(a[k][i].s){
                if(a[k][i].s!=t[i].s){
                    a[k][i].fl=true;
                }
                a[k][i].upd|=1u<<i;
            }
            if(a[k][i].x==t[i].x){
                // cerr<<"x满足 "<<a[k][i].x<<" "<<t[i].x<<endl;
                a[k][i].upd|=1u<<i+6;
            }
            if(a[k][i].y==t[i].y){
                // cerr<<"y满足 "<<a[k][i].y<<" "<<t[i].y<<endl;
                a[k][i].upd|=1u<<i+12;
            }
        }
    }
    uint x=0,s=0,e=0;
    for(int j=0;j<m;j++){
        if(t[j].s)x|=1u<<j;
        if(t[j].x==0)s|=(1u<<j+6);
        if(t[j].y==0)s|=(1u<<j+12);
        e|=(1u<<j+6)|(1u<<j+12);
    }
    e|=x;
    if(s==e){
        // 全部都是OK,0/0
        cout<<1<<endl;
        cout<<1<<endl;
        return 0;
    }
    use[s]=-1;
    for(uint x=s;x<e;x++){
        if(!use[x])continue;
        bool fl=false;
        for(int i=0;i<6;i++)
            if((x>>i)&1){
                //说明i已经挂了
                if(i>=m){
                    fl=true;
                    break;
                }
            }
        if(fl)continue;
        for(int k=1;k<=n;k++){
            uint y=x;
            bool fl=false;
            // cerr<<"=============================="<<endl;
            for(int i=0;i<m;i++)
                if(!((x>>i)&1)){
                    //说明i没有挂
                    if(a[k][i].fl){
                        fl=true;
                        break;
                    }
                    y|=a[k][i].upd;
                }
            if(fl)continue;
            if(x==y)continue;
            // cerr<<bitset<18>(x)<<" => "<<bitset<18>(y)<<" : "<<k<<endl;
            if(!use[y]||dis[x]+1<dis[y]){
                dis[y]=dis[x]+1;
                pre[y]=x;
                use[y]=k;
            }
        }
    }
    // cerr<<"! s = "<<bitset<18>(s)<<endl;
    // cerr<<"! e = "<<bitset<18>(e)<<endl;
    assert(use[e]!=0);
    vector<int> ans;
    for(int u=e;u!=s;u=pre[u]){
        // cerr<<bitset<18>(u)<<" "<<use[u]<<" "<<pre[u]<<endl;
        ans.push_back(use[u]);
    }
    reverse(ans.begin(),ans.end());
    cout<<ans.size()<<endl;
    for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<" \n"[i+1==ans.size()];
    }
}