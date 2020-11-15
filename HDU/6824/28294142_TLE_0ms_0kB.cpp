#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+5,M=1e7+5;
int n,he[N],to[N<<1],ne[N<<1],fa[N],sn[N],sz[N],d[N],tp[N],ps[N],ct,mx;
void dfs1(int x,int y){
    fa[x]=y,d[x]=d[y]+1,sz[x]=1;
    for(int i=he[x],j;i;i=ne[i])if(j=to[i],j!=y){
        dfs1(j,x),sz[x]+=sz[j];
        if(sz[j]>sz[sn[x]])sn[x]=j;
    }
}
void dfs2(int x,int y){
    tp[x]=y,ps[x]=++ct;
    if(!sn[x])return;
    dfs2(sn[x],y);
    for(int i=he[x],j;i;i=ne[i])if(j=to[i],j!=fa[x]&&j!=sn[x])dfs2(j,j);
}
vector<int>vc[N<<2],e[M];
int u,v,w,id,cl[M],dfn[M],low[M],c,z,st[M],t;
inline void add(int x,int y){e[x].push_back(y),e[y^1].push_back(x^1),mx=max(mx,max(x,max(y,max((x^1),(y^1)))));}
void upd(int k,int l,int r){
    if(u<=l&&r<=v)return vc[k].push_back(w);
    int m=l+r>>1;
    if(u<=m)upd(k<<1,l,m);
    if(m<v)upd(k<<1|1,m+1,r);
}
void mdf(int x,int y){
    while(tp[x]!=tp[y]){
        if(d[tp[x]]<d[tp[y]])swap(x,y);
        u=ps[tp[x]],v=ps[x],upd(1,2,n),x=fa[tp[x]];
    }
    if(x!=y){
        if(d[x]<d[y])swap(x,y);
        u=ps[y]+1,v=ps[x],upd(1,2,n);
    }
}
void build(int k,int l,int r,int p){
    int o=vc[k].size(),i,j,u=++id,v=(id+=o);
    if(o)add(v-1<<1,v<<1);
    else if(p)add(p<<1,v<<1);
    for(i=0;i<o;++i){
        j=vc[k][i],add(j,u+i<<1);
        if(i>0)add(u+i-1<<1,u+i<<1),add(u+i-1<<1,j^1);
        else if(p)add(p<<1,u<<1),add(p<<1,j^1);
    }
    if(l==r)return;
    int m=l+r>>1;
    build(k<<1,l,m,v),build(k<<1|1,m+1,r,v);
}
void tarjan(int x){
    dfn[x]=low[x]=++z,st[++t]=x;
    for(auto j:e[x])
    if(!dfn[j])tarjan(j),low[x]=min(low[x],low[j]);
    else if(!cl[j])low[x]=min(low[x],dfn[j]);
    if(low[x]==dfn[x]){
        cl[x]=++c;
        while(st[t]!=x)cl[st[t--]]=c;
        --t;
    }
}
int l1[N],r1[N],l2[N],r2[N],b[N*4],m;
bool check(int mid){
    for(int i=0;i<=n;i++)he[i]=fa[i]=sn[i]=sz[i]=d[i]=tp[i]=ps[i]=0;
    for(int i=0;i<=n*2;i++)to[i]=ne[i]=0;
    for(int i=0;i<=n*4;i++)vc[i].clear();
    for(int i=0;i<=mx;i++)cl[i]=dfn[i]=low[i]=st[i]=0,e[i].clear();
    mx=ct=u=v=w=id=c=z=t=0;
    int i,j,k,t=0;
    // scanf("%d",&n);
    for(i=1;i<n;++i){
        // scanf("%d%d",&j,&k);
        ne[++t]=he[i],to[t]=i+1,he[i]=t;
        ne[++t]=he[i+1],to[t]=i,he[i+1]=t;
    }
    dfs1(1,0),dfs2(1,1);//scanf("%d",&m);
    for(i=1;i<=m;++i){
        // scanf("%d%d",&j,&k),w=i<<1,mdf(j,k);
        // scanf("%d%d",&j,&k),w|=1,mdf(j,k);
        j=l1[i];k=r1[i];w=i<<1;
        if(i!=m&&k>mid)j=n-1,k=n;
        mdf(j,k);
        j=l2[i];k=r2[i];w|=1;
        if(i!=m&&k>mid)j=n-1,k=n;
        mdf(j,k);
    }
    id=m,build(1,2,n,0);
    for(i=id<<1;i;--i)if(!cl[i])tarjan(i);
    for(i=1;i<=m;++i)if(cl[i<<1]==cl[i<<1|1])return 0;
    return 1;
}
int main(){
    int T;scanf("%d",&T);
    while(T--){
        scanf("%d",&m);n=0;
        for(int i=1;i<=m;i++){
            scanf("%d%d%d%d",&l1[i],&r1[i],&l2[i],&r2[i]);r1[i]+=l1[i];r2[i]+=l2[i];
            --l1[i];--l2[i];
            b[++n]=l1[i];b[++n]=r1[i];b[++n]=l2[i];b[++n]=r2[i];
        }
        sort(b+1,b+n+1);n=unique(b+1,b+n+1)-b-1;
        ++n;b[n]=b[n-1]+1;++n;b[n]=b[n-1]+1;
        for(int i=1;i<=m;i++){
            l1[i]=lower_bound(b+1,b+n+1,l1[i])-b;
            r1[i]=lower_bound(b+1,b+n+1,r1[i])-b;
            l2[i]=lower_bound(b+1,b+n+1,l2[i])-b;
            r2[i]=lower_bound(b+1,b+n+1,r2[i])-b;
            // printf(">>> %d %d %d %d\n",l1[i],r1[i],l2[i],r2[i]);
        }
        ++m;l1[m]=l2[m]=n-1;r1[m]=r2[m]=n;
        int l=1,r=n-2,ans=-1;
        // printf("fuck %d\n",check(1));
        while(l<=r){
            int mid=(l+r)>>1;
            if(check(mid))ans=mid,r=mid-1;
            else l=mid+1;
        }
        if(ans==-1)printf("-1\n");
        else printf("%d\n",b[ans]);
    }
    return 0;
}