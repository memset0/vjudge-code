#include<bits/stdc++.h>
const int N=110,V=2e4+10;
int n,m,l,r,u,v,res,pos,id[N][N],idx[N][N],idy[N][N],q[V],p[V],h[V],fa[V],xx[V],yy[V],col[V];
char s[N][N],cc[4][4];
std::vector<int> G[V];
std::map<int,bool> map[V];
inline int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
inline void add(int u,int v){if(u&&v)G[u].push_back(v),G[v].push_back(u);}
int lca(int u,int v){
	static int fl[V],tim; ++tim;
	while(fl[u]!=tim){
		if(u)fl[u]=tim,u=find(p[h[u]]);
		std::swap(u,v);
	}return u;
}
void blossum(int u,int v,int t){
	while(find(u)!=t){
		p[u]=v,v=h[u],fa[u]=fa[v]=t;
		if(col[v]==1)col[v]=2,q[++r]=v;
		u=p[v];
	}
}
bool match(int rt){
	// printf("match %d\n",rt);
	for(int i=1;i<=pos;i++)fa[i]=i,col[i]=0;
	l=r=1,q[1]=rt,col[rt]=2;
	while(l<=r){
		u=q[l++];
		for(int v:G[u])if(!col[v]){
			col[v]=1,col[h[v]]=2,p[v]=u,q[++r]=h[v];
			if(!h[v]){
				while(u)u=h[p[v]],h[v]=p[v],h[p[v]]=v,v=u;
				return true;
			}
		}else if(col[v]==2){
			int t=lca(u,v); blossum(u,v,t),blossum(v,u,t);
		}
	}return false;
} 
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(s[i][j]=='.')id[i][j]=++pos,xx[pos]=i,yy[pos]=j;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(s[i][j]!='.'){
		idx[i][j]=++pos,idy[i][j]=++pos,add(idx[i][j],idy[i][j]);
		add(idx[i][j],id[i+1][j]),add(idy[i][j],id[i+1][j]);
		add(idx[i][j],id[i-1][j]),add(idy[i][j],id[i-1][j]);
		add(idx[i][j],id[i][j+1]),add(idy[i][j],id[i][j+1]);
		add(idx[i][j],id[i][j-1]),add(idy[i][j],id[i][j-1]);
		if(!map[id[i-1][j]][id[i][j-1]])add(id[i-1][j],id[i][j-1]),map[id[i-1][j]][id[i][j-1]]=map[id[i][j-1]][id[i-1][j]]=1;
		if(!map[id[i-1][j]][id[i][j+1]])add(id[i-1][j],id[i][j+1]),map[id[i-1][j]][id[i][j+1]]=map[id[i][j+1]][id[i-1][j]]=1;
		if(!map[id[i+1][j]][id[i][j-1]])add(id[i+1][j],id[i][j-1]),map[id[i+1][j]][id[i][j-1]]=map[id[i][j-1]][id[i+1][j]]=1;
		if(!map[id[i+1][j]][id[i][j+1]])add(id[i+1][j],id[i][j+1]),map[id[i+1][j]][id[i][j+1]]=map[id[i][j+1]][id[i+1][j]]=1;
		if(s[i][j]=='+')add(id[i-1][j],id[i+1][j]),add(id[i][j-1],id[i][j+1]);
	}
	// for(int i=1;i<=pos;i++)for(int j=1;j<=pos;j++)if(map[i][j])printf("> %d %d\n",i,j);
	for(int i=1;i<=pos;i++)if(!h[i]&&match(i))++res;
	for(int s=0,i=0;i<4;i++)for(int j=0;j<4;j++)cc[i][j]='a'+(s++);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(s[i][j]!='.'&&h[idx[i][j]]&&h[idx[i][j]]!=idy[i][j]&&h[idy[i][j]]&&h[idy[i][j]]!=idx[i][j]){
		s[i][j]=cc[(i-1)%4][(j-1)%4];
		s[xx[h[idx[i][j]]]][yy[h[idx[i][j]]]]=s[i][j];
		s[xx[h[idy[i][j]]]][yy[h[idy[i][j]]]]=s[i][j];
		// printf("%d %d : %d %d : %d %d\n",i,j,xx[h[idx[i][j]]],yy[h[idx[i][j]]],xx[h[idy[i][j]]],yy[h[idy[i][j]]]);
	}
	// int i=3,j=2; printf("%d %d : %d %d : %d %d\n",i,j,xx[h[idx[i][j]]],yy[h[idx[i][j]]],xx[h[idy[i][j]]],yy[h[idy[i][j]]]);
	for(int i=1;i<=n;i++){for(int j=1;j<=m;j++)putchar(s[i][j]);putchar('\n');}
}