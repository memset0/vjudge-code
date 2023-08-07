#include<bits/stdc++.h>
using namespace std;
const int N=2e5;
struct edge{
	int t,nxt;
}e[(N<<1)+10];
int T,n,D,m,u,v,f[N+10],be[N+10],cnt,ar[N+10];
int fa[N+10],dep[N+10],mnd[N+10],prt[N+10],sz;
char c;
int getf(int x){
	return f[x]==x?x:f[x]=getf(f[x]);
}
void scan(int&x){
	x=0;
	while(!isdigit(c=getchar()));
	while(isdigit(c))x=(x<<3)+(x<<1)+c-'0',c=getchar();
}
void add(int x,int y){
	e[++cnt]=(edge){y,be[x]},be[x]=cnt;
}
void Getdep(int x,int y){
	fa[x]=y,dep[x]=dep[y]+1;
	for(int i=be[x];i;i=e[i].nxt)if(e[i].t!=y)Getdep(e[i].t,x);
}
bool cmp(int x,int y){
	return dep[y]>dep[x];
}
bool Check(int x){
	for(int i=1)
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m;
		D=0;
		while(D*D<n)++D;
		for(int i=1;i<=n;++i)f[i]=i,be[i]=0,mnd[i]=D+1,ar[i]=i;
		cnt=sz=0;
		for(int i=1;i<=m;++i){
			//cin>>u>>v;
			u=i,v=i+1;
			if(getf(u)!=getf(v))add(u,v),add(v,u),f[f[u]]=f[v];
		}
		Getdep(1,0);
		sort(ar+1,ar+n+1,cmp);
		for(int i=1;i<=n;++i)if(Check(ar[i]))
		// assert(sz<=D);
		cout<<sz<<'\n';
		for(int i=1;i<=sz;++i){
			// printf("%d%c",prt[i]," \n"[i==sz]);
			cout<<prt[i]<<" \n"[i==sz];
		}
	}
	return 0;
}
/*
1
200000 199999
*/