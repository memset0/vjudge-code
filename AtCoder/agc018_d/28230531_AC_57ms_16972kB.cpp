#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=1e5+10;
long long ans;
std::vector<std::pair<int,int>> G[N];
int n,root,root2,fa[N],siz[N],maxp[N];
void dfs(int u){
	siz[u]=1;
	for(auto it:G[u]){
		int v=it.first,w=it.second;
		if(v!=fa[u]){
			fa[v]=u,dfs(v);
			siz[u]+=siz[v];
			maxp[u]=std::max(maxp[u],siz[v]);
			ans+=2ll*w*std::min(siz[v],n-siz[v]);
		}
	}
	maxp[u]=std::max(maxp[u],n-siz[u]);
	if(maxp[u]<maxp[root])root=u,root2=0;
	else if(maxp[u]==maxp[root])root2=u;
}
int main(){
	read(n);
	for(int u,v,w,i=1;i<n;i++){
		read(u),read(v),read(w);
		G[u].push_back(std::make_pair(v,w));
		G[v].push_back(std::make_pair(u,w));
	}
	maxp[root]=n,dfs(1);
	// for(int i=1;i<=n;i++)printf("%d%c",siz[i]," \n"[i==n]);
	// for(int i=1;i<=n;i++)printf("%d%c",maxp[i]," \n"[i==n]);
	// printf(">> %d %d\n",root,root2);
	if(root2){
		for(auto it:G[root])if(it.first==root2){ans-=it.second;break;}
	}else{
		int min=G[root].begin()->second;
		for(auto it:G[root])min=std::min(min,it.second);
		ans-=min;
	}
	printf("%lld\n",ans);
}