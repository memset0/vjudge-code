#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N=1e4+10;
const int M=1e6+10;
const int inf=0x3f3f3f3f;

bool vis[N];
int sr,ed,lim;
int le[N],gap[N],cur[N];
int tot,fir[N];
int nex[M],to[M],val[M];
void add(int x,int y,int z){
    ++tot;
    to[tot]=y; val[tot]=z;
    nex[tot]=fir[x]; fir[x]=tot;
}
void addge(int x,int y,int z){
    add(x,y,z); add(y,x,0);
}
void built(int x){
    addge(sr,2*x-1,1);
    addge(2*x,ed,1);
    for(int i=1; i<x; ++i){
        int d=i+x;
        int w=sqrt(d);
        if(w*w==d) addge(2*i-1,2*x,inf);
    }
}
int dfs(int pre,int u,int flow){
    if(u==ed || flow==0){
        if(flow) vis[pre-1]=true;
        return flow;
    }
    int tmp=0;
    for(int &i=cur[u]; ~i; i=nex[i]){
        int v=to[i];
        if(le[u]==le[v]+1 && val[i]>0){
            int d=dfs(u,v,min(flow-tmp,val[i]));
            tmp+=d;
            val[i]-=d;
            val[i^1]+=d;
            if(flow==tmp) return flow;
        }
    }
    if(--gap[le[u]]==0) le[sr]=ed+1;
    ++gap[++le[u]]; cur[u]=fir[u];
    return tmp;
}
int maxflow(){
    gap[sr]=le[sr]=0; cur[sr]=fir[sr];
    gap[ed]=le[ed]=0; cur[ed]=fir[ed];
    for(int i=0; i<=lim; ++i){
        le[i]=gap[i]=0;
        cur[i]=fir[i];
    }
    int ans=0;
    while(le[sr]<=ed){ans+=dfs(-1,sr,inf); }
    return ans;
}

int main()
{
    tot=-1;
    sr=N-2; ed=sr+1;
    memset(fir,-1,sizeof(fir));
    
    int n;
    scanf("%d",&n);
    for(int i=1; i<=n; ++i) built(i);
    int ans=n,tmp=0;
    for(int i=n+1; ; ++i){
        built(i); lim=i+i;
        tmp+=maxflow();
        if(i-tmp>n) break;
        ans=i;
    }
    printf("%d\n",ans);    
    for(int i=fir[sr]; ~i; i=nex[i]){
        int u=to[i];
        if(val[i] || vis[u]) continue;
        while(u){
            int v=0;
            for(int j=fir[u]; ~j; j=nex[j]){
                if(val[j]==inf || to[j]==sr) continue;
                v=to[j]-1;
                break;
            }
            printf("%d%c",(u+1)/2,v==0?'\n':' ');
            u=v;
        }
    }
    return 0;
}