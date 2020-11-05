#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();if(f)x=-x;
}
const int N=1e5+10;
int n,q,k,rt,ans,id[N],fa[N],siz[N],vis[N];
long long l,f[N],d0[N],d1[N];
std::vector<std::pair<int,int>> G[N];
inline int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void bfs(int u,long long *dis){
	std::queue<int> q;
	q.push(u),memset(dis,-1,N<<3),dis[u]=0;
	while(q.size()){
		int u=q.front(); q.pop();
		for(auto it:G[u]){
			int v=it.first,w=it.second;
			if(dis[v]==-1)dis[v]=dis[u]+w,q.push(v);
		}
	}
}
int main(){
	read(n);
	for(int i=1,u,v,w;i<n;i++){
		read(u),read(v),read(w);
		G[u].push_back(std::make_pair(v,w));
		G[v].push_back(std::make_pair(u,w));
	}
	bfs(1,d0);
	bfs(std::max_element(d0+1,d0+n+1)-d0,d1);
	bfs(std::max_element(d1+1,d1+n+1)-d1,d0);
	for(int i=1;i<=n;i++)f[i]=std::max(d0[i],d1[i]),id[i]=i;
	std::sort(id+1,id+n+1,[](int a,int b){return f[a]==f[b]?a<b:f[a]>f[b];});
	rt=std::min_element(f+1,f+n+1)-f;
	// for(int i=1;i<=n;i++)printf("> %d %d\n",id[i],f[id[i]]);
	read(q);
	for(int i=1;i<=q;i++){
		read(l);
		for(int i=1;i<=n;i++)fa[i]=i,siz[i]=1,vis[i]=0;
		ans=0,k=1;
		for(int i=1;i<=n;i++){
			int u=id[i]; vis[u]=1;
			for(auto it:G[u]){
				int v=it.first;
				if(vis[v])fa[v]=u,siz[u]+=siz[v];
			}
			while(k<=n&&f[id[k]]>f[u]+l)siz[find(id[k++])]--;
			// printf("dfs u=%d dp=%d k=%d size=%d\n",u,f[u],k,siz[find(u)]);
			ans=std::max(ans,siz[find(u)]);
		}
		std::cout<<ans<<std::endl;
	}
}