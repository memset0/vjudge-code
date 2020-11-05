#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=1e4+10;
int n,m,cnt,tim,top,dfn[N],low[N],stk[N],col[N],mrk[N],anc[N],vis[N],sizV[N],sizE[N];
std::vector<int> G[N],nod[N];
std::set<std::pair<int,int>> set[N];
std::vector<std::pair<int,int>> E;
void SUCCESS(){puts("Yes"),exit(0);}
int find(int x){return x==anc[x]?x:anc[x]=find(anc[x]);}
inline void add_circle(int l){
	if(mrk[l])SUCCESS();
	mrk[l]=1;
};
void tarjan(int u,int fa){
	dfn[u]=low[u]=++tim,stk[++top]=u;
	for(int v:G[u])if(v!=fa){
		if(!dfn[v]){
			tarjan(v,u);
			low[u]=std::min(low[u],low[v]);
		}else{
			low[u]=std::min(low[u],dfn[v]);
		}
	}
	if(dfn[u]==low[u]){
		++cnt;
		do{
			col[stk[top]]=cnt;
			nod[cnt].push_back(stk[top]);
		}while(stk[top--]!=u);
	}
}
void solve(int c){
	std::vector<int> all;
	for(int i:nod[c])if(set[i].size()==2){
		int u,v,wu,wv;
		std::tie(u,wu)=*set[i].begin();
		std::tie(v,wv)=*--set[i].end();
		if(u==v){
			add_circle(wu+wv);
			continue;
		}
		set[u].erase({i,wu}),set[u].insert({v,wu+wv});
		set[v].erase({i,wv}),set[v].insert({u,wu+wv});
	}
	for(int i:nod[c])if(set[i].size()!=2)all.push_back(i);
	for(int u:all)
		printf("%d\n",u);
	for(int u:all)for(auto it:set[u])if(u<it.first)
		printf("%d %d %d\n",u,it.first,it.second);
	std::function<bool(int,int)> connect=[&](int s,int t){
		vis[s]=vis[t]=0;
		for(int i:all)if(!vis[i])anc[i]=i;
		for(int u:all)if(!vis[u])
			for(const auto &it:set[u]){
				int v=it.first;
				if(!vis[v])anc[find(u)]=find(it.first);
			}
		vis[s]=vis[t]=1;
		return anc[s]==anc[t];
	};
	for(int s:all){
		std::function<void(int,int)> dfs=[&](int u,int l){
			for(const auto &it:set[u]){
				int v=it.first,w=it.second;
				if(v==s)add_circle(w+l);
				else{
					vis[v]=1;
					if(connect(u,v))dfs(v,w+l);
					vis[v]=0;
				}
			}
		};
		vis[s]=1,dfs(s,0),vis[s]=0;
	}
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(m);
	for(int u,v,i=1;i<=m;i++){
		read(u),read(v);
		G[u].push_back(v);
		G[v].push_back(u);
		E.push_back({u,v});
	}
	for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i,-1);
	for(int i=1;i<=n;i++)printf("%d%c",col[i]," \n"[i==n]);
	for(const auto &it:E){
		int u=it.first,v=it.second;
		if(col[u]==col[v]){
			sizE[col[u]]++;
			set[u].insert({v,1});
			set[v].insert({u,1});
		}
	}
	for(int i=1;i<=cnt;i++){
		sizV[i]=nod[i].size();
		if(sizE[i]>sizV[i]+sqrt(sizV[i])+5)SUCCESS();
	}
	for(int i=1;i<=cnt;i++)solve(i);
	puts("No");
}