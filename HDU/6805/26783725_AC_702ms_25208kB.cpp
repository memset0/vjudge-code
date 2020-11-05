#include<bits/stdc++.h>
template<class T> inline void read(T &x){
    x=0; register char c=getchar(); register bool f=0;
    while(!isdigit(c))f^=c=='-',c=getchar();
    while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
inline void read(char &x){
    x=getchar();
    while(!isalpha(x))x=getchar();
}
template<class T> inline void print(T x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=2e5+10;
int T,n,m,s,t,x,l,r,q[N];
char a[N];
bool vis[N];
long long dis[N];
std::vector<std::pair<int,int>> G[N];
inline void initGraph(int n){
    // memset(vis+1,0,n);
    // memset(dis+1,63,n<<3);
    for(int i=1;i<=n;i++)G[i].clear(),vis[i]=0,dis[i]=0x7fffffffffffffff;
}
inline void add(int u,int v,int w){
    G[u].push_back({v,w});
    G[v].push_back({u,w});
}
inline long long spfa(int s,int t){
    int u;
    std::pair<long long,int> f;
    std::priority_queue<std::pair<long long,int>> q;
    dis[s]=0,q.push({-dis[s],s});
    while(q.size()){
        f=q.top(),q.pop(),u=f.second;
        if(vis[u])continue; vis[u]=1;
        for(const auto &e:G[u]){
            int v=e.first,w=e.second;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                q.push({-dis[v],v});
            }
        }
    }
    return dis[t];
}
int main(){
    for(read(T);T--;){
        read(n),read(m),read(s),read(t),read(x);
        initGraph(n*2+2);
        for(int i=1;i<=n;i++)read(a[i]);
        for(int i=1,u,v,d;i<=m;i++){
            read(u),read(v),read(d);
            if(a[u]!='R'&&a[v]!='R')add(u,v,d);
            if(a[u]!='L'&&a[v]!='L')add(u+n,v+n,d);
            if(a[u]!='R'&&a[v]!='L')add(u,v+n,d+x);
            if(a[u]!='L'&&a[v]!='R')add(u+n,v,d+x);
        }
        if(a[s]!='R')add(n*2+1,s,0);
        if(a[s]!='L')add(n*2+1,s+n,0);
        if(a[t]!='R')add(t,n*2+2,0);
        if(a[t]!='L')add(t+n,n*2+2,0);
        print(spfa(2*n+1,2*n+2),'\n');
    }
}//12313213123123