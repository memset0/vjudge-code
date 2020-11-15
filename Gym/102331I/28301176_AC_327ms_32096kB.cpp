#include<bits/stdc++.h>
std::mt19937 rng(20040725^std::chrono::steady_clock::now().time_since_epoch().count());
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=2e5+10;
int n,m,rt,full,maxp[N],vis[N],siz[N];
std::vector<int> G[N];
int calcsize(int u,int fa){
	int siz=1;
	for(int v:G[u])if(v!=fa){
		siz+=calcsize(v,u);
	}
	return siz;
}
void findroot(int u,int fa){
	siz[u]=1,maxp[u]=0;
	for(int v:G[u])if(v!=fa){
		findroot(v,u);
		siz[u]+=siz[v];
		maxp[u]=std::max(maxp[u],siz[v]);
	}
	maxp[u]=std::max(maxp[u],full-siz[u]);
	if(maxp[u]<maxp[rt]||(maxp[u]==maxp[rt]&&(rand()&1)))rt=u;
}
void solve(int u){
	std::vector<int> son=G[u];
	if(!son.size()){printf("! %d\n",u),fflush(stdout); return;}
	int mid=son.size()&1?(son.size()>>1):(son.size()>>1)-1,op;
	// printf("%d ::=> %d %d\n",u,mid,son.size());
	// for(int i=0;i<son.size();i++)printf("%d%c",son[i]," \n"[i+1==son.size()]);
	printf("? %d %d ",mid+1,u);
	for(int i=0;i<=mid;i++)printf("%d ",son[i]);
	printf("\n"),fflush(stdout);
	read(op);
	G[u].clear();
	if(op==0){
		for(int i=0;i<=mid;i++)G[u].push_back(son[i]);
	}else{
		for(int i=mid+1;i<son.size();i++)G[u].push_back(son[i]);
	}
	full=maxp[rt=0]=calcsize(u,0),findroot(u,0),solve(rt);
}
int main(){
	read(n);
	for(int u,v,i=1;i<n;i++){
		read(u),read(v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=1;i<=n;i++)std::shuffle(G[i].begin(),G[i].end(),rng);
	full=maxp[rt=0]=n,findroot(1,0),solve(rt);
}