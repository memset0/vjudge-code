#include<bits/stdc++.h>
#ifndef memset0
	#define endl '\n'
#endif
using namespace std;
const int N=1e5+9;
int T,n,m,q,tot,anc[N],fa[N],dfn[N],dep[N],a[N],b[N],top[N],cur[N],siz[N],son[N],rnkl[N],rnkr[N];
long long len[N],dp[N][2],pre[N],suf[N];
bool col[N],foc[N];
vector<int> red,F[N];
vector<pair<int,int>> G[N];
template<class T> inline void updmin(T &x,T y){
	if(y<x)x=y;
}
template<class T> inline void updmax(T &x,T y){
	if(y>x)x=y;
}
inline int cmp_by_dfn(int u,int v){
	return dfn[u]<dfn[v];
}
// int jp[N][20];
// inline int lca(int u,int v){
// 	// cerr<<"lca "<<u<<" "<<v<<" "<<dep[u]<<" "<<dep[v]<<endl;
// 	if(dep[u]>dep[v])swap(u,v);
// 	for(int i=19;i>=0;i--)
// 		if(jp[v][i]&&dep[jp[v][i]]>=dep[u]){
// 			v=jp[v][i];
// 		}
// 	if(u==v)return u;
// 	for(int i=19;i>=0;i--)
// 		if(jp[u][i]&&jp[v][i]&&jp[u][i]!=jp[v][i]){
// 			u=jp[u][i];
// 			v=jp[v][i];
// 		}
// 	return jp[u][0];
// }
void dfs(int u,int u_anc){
	if(col[u]){
		u_anc=u;
	}
	dfn[u]=++tot;
	anc[u]=u_anc;
	siz[u]=1;
	son[u]=0;
	// cerr<<"!!! dfs "<<u<<" "<<u_anc<<endl;
	for(auto [v,w]:G[u])
		if(v!=fa[u]){
			// cerr<<u<<" >> "<<v<<endl;
			fa[v]=u;
			dep[v]=dep[u]+1;
			len[v]=len[u]+w;
			dfs(v,u_anc);
			siz[u]+=siz[v];
			if(siz[v]>siz[son[u]]){
				son[u]=v;
			}
		}
}
void dfs2(int u,int tpt){
	top[u]=tpt;
	if(siz[u]==1)return;
	dfs2(son[u],tpt);
	for(auto [v,w]:G[u])
		if(v!=fa[u]&&v!=son[u]){
			dfs2(v,v);
		}
}
inline int lca(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]>dep[top[v]])swap(u,v);
		v=fa[top[v]];
	}
	return dep[u]<dep[v]?u:v;
}
void solve(int u){
	dp[u][0]=dp[u][1]=0;
	rnkl[u]=rnkr[u]=cur[u];
	if(foc[u]){
		dp[u][0]=len[u];
	}
	for(int v:F[u]){
		solve(v);
		updmax(dp[u][1],dp[v][1]);
		if(dep[anc[v]]<dep[u]){
			updmax(dp[u][0],dp[v][0]);
		}else{
			updmax(dp[u][1],dp[v][0]-len[anc[v]]);
		}
		updmin(rnkl[u],rnkl[v]);
		updmax(rnkr[u],rnkr[v]);
	}
	if(col[u]){
		updmax(dp[u][1],dp[u][0]-len[u]);
		dp[u][0]=0;
	}
	// cerr<<"dp["<<u<<"] :: "<<dp[u][0]<<" "<<dp[u][1]<<endl;
}
int main(){
#ifdef memset0
	freopen("B.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m>>q;
		fill_n(col+1,n,false);
		for(int i=1;i<=n;i++){
			G[i].clear();
		}
		for(int x,i=1;i<=m;i++){
			cin>>x;
			red.push_back(x);
			col[x]=true;
		}
		for(int u,v,w,i=1;i<n;i++){
			cin>>u>>v>>w;
			// cerr<<"! "<<u<<" "<<v<<" "<<w<<endl;
			G[u].emplace_back(v,w);
			G[v].emplace_back(u,w);
		}
		// exit(0);
		tot=0;
		dep[1]=1;
		dfs(1,1);
		dfs2(1,1);
		// for(int i=1;i<=n;i++){
		// 	jp[i][0]=fa[i];
		// }
		// for(int j=1;j<20;j++)
		// 	for(int i=1;i<=n;i++){
		// 		jp[i][j]=jp[jp[i][j-1]][j-1];
		// 	}
		// for(int i=1;i<=n;i++)cerr<<son[i]<<" \n"[i==n];
		// for(int i=1;i<=n;i++)cerr<<siz[i]<<" \n"[i==n];
		// for(int i=1;i<=n;i++)cerr<<top[i]<<" \n"[i==n];
		for(int k,i=1;i<=q;i++){
			cin>>k;
			for(int i=1;i<=k;i++)cin>>b[i];
			sort(b+1,b+k+1,cmp_by_dfn);
			a[tot=1]=1;
			for(int i=1;i<=k;i++){
				a[++tot]=b[i];
				// cerr<<"! "<<b[i]<<" "<<lca(b[i-1],b[i])<<endl;
				if(i>1)a[++tot]=lca(b[i-1],b[i]);
			}
			sort(a+1,a+tot+1,cmp_by_dfn);
			tot=unique(a+1,a+tot+1)-a-1;
			for(int i=1;i<=tot;i++){
				cur[a[i]]=i;
				foc[a[i]]=false;
				F[a[i]].clear();	
			}
			for(int i=1;i<=k;i++){
				foc[b[i]]=true;
			}
			// cerr<<"  A ";for(int i=1;i<=tot;i++)cerr<<a[i]<<" \n"[i==tot];
			// cerr<<"DFN ";for(int i=1;i<=tot;i++)cerr<<dfn[a[i]]<<" \n"[i==tot];
			// cerr<<"FOC ";for(int i=1;i<=tot;i++)cerr<<foc[a[i]]<<" \n"[i==tot];
			for(int lc,i=1;i<tot;i++){
				lc=lca(a[i],a[i+1]);
				F[lc].push_back(a[i+1]);
			}
			solve(1);
			for(int i=1;i<=tot;i++){
				pre[i]=pre[i-1];
				if(foc[a[i]]){
					updmax(pre[i],len[a[i]]-len[anc[a[i]]]);
				}
			}
			suf[tot+1]=0;
			for(int i=tot;i>=1;i--){
				suf[i]=suf[i+1];
				if(foc[a[i]]){
					updmax(suf[i],len[a[i]]-len[anc[a[i]]]);
				}
			}
			long long ans=LLONG_MAX;
			for(int i=1;i<=tot;i++){
				int u=a[i];
				long long cur=dp[u][1];
				updmax(cur,dp[u][0]-len[u]);
				if(rnkl[u]>1){
					updmax(cur,pre[rnkl[u]-1]);
				}
				if(rnkr[u]<tot){
					updmax(cur,suf[rnkr[u]+1]);
				}
				ans=min(ans,cur);
				// cerr<<"ans["<<u<<"] :: "<<cur<<endl;
			}
			cout<<ans<<endl;
		}
	}
}