#include <cstdio>
#include <algorithm>

int fa[200001][20],size[8000001],lson[8000001],rson[8000001],cnt,n,m,orig[100001],h[100001],root[100001],dfn[200001],mx[200001],now,f[200001];
int diff[200001]={2147483000},ch[200001][2],ord[200001],nodes,q,v,x,k;
int find(int x){return !f[x]?x:f[x]=find(f[x]);}
struct point{int u,v,diff;}num[500001];
bool cmp(point a,point b){return a.diff<b.diff;}
void dfs(int x){
    if(x<=n){
        dfn[x]=mx[x]=++now;
        ord[now]=x;
        return;
    }
    dfs(ch[x][0]);
    dfs(ch[x][1]);
    dfn[x]=dfn[ch[x][0]];
    mx[x]=mx[ch[x][1]];
}
void build(int &pos,int pre,int l,int r,int x){
    pos=++nodes;
    size[pos]=size[pre]+1;
    lson[pos]=lson[pre];
    rson[pos]=rson[pre];
    if(l==r)return;
    if((l+r)>>1>=x)build(lson[pos],lson[pre],l,(l+r)>>1,x);
    else build(rson[pos],rson[pre],((l+r)>>1)+1,r,x);
}
int query(int root,int pre,int l,int r,int k){
    if(l==r)return orig[l];
    if(size[rson[root]]-size[rson[pre]]>=k)return query(rson[root],rson[pre],((l+r)>>1)+1,r,k);
    else return query(lson[root],lson[pre],l,(l+r)>>1,k-size[rson[root]]+size[rson[pre]]);
}
int main(){
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++)scanf("%d",h+i),orig[i]=h[i];
    std::sort(orig+1,orig+n+1);
    int lim=std::unique(orig+1,orig+n+1)-orig-1;
    for(int i=1;i<=n;i++)h[i]=std::lower_bound(orig+1,orig+lim+1,h[i])-orig;
    for(int i=1;i<=m;i++)scanf("%d%d%d",&num[i].u,&num[i].v,&num[i].diff);
    std::sort(num+1,num+m+1,cmp);
    cnt=n;
    for(int i=1,K=1;i<=m&&K<n;i++){
        int fu=find(num[i].u),fv=find(num[i].v);
        if(fu!=fv){
            f[fu]=f[fv]=fa[fu][0]=fa[fv][0]=++cnt;
            diff[cnt]=num[i].diff;
            ch[cnt][0]=fu,ch[cnt][1]=fv;
            ++K;
        }
    }
    for(int i=1;i<20;i++)
        for(int j=1;j<=cnt;j++)
            fa[j][i]=fa[fa[j][i-1]][i-1];
    dfs(cnt);
    for(int i=1;i<=n;i++)build(root[i],root[i-1],1,lim,h[ord[i]]);
    for(int i=1;i<=q;i++){
        scanf("%d%d%d",&v,&x,&k);
        for(int j=19;j>=0;j--)if(diff[fa[v][j]]<=x)v=fa[v][j];
        if(mx[v]-dfn[v]+1<k)puts("-1");
        else printf("%d\n",query(root[mx[v]],root[dfn[v]-1],1,lim,k));
    }
}