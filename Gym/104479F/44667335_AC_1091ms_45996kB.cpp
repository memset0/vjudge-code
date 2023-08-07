#include<bits/stdc++.h>
#ifndef memset0
	#define endl '\n'
#endif
using namespace std;
using ll=long long;
const int N=2e5+9,K=20,mod=998244353;
int n,q,fa[N],dep[N],siz[N],f[N][K],g[N][2],fac[N],ifac[N];
vector<int> pts[N],G[N];
inline int binom(int n,int m){
	if(n<m)return 0;
	return (ll)fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
inline int power(int a,int b){
	int s=1;
	for(;b;b>>=1,a=(ll)a*a%mod)
		if(b&1)s=(ll)s*a%mod;
	return s;
}
inline int find(int x){
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
void dfs(int u){
	for(int v:G[u])
		if(v!=f[u][0]){
			f[v][0]=u;
			dep[v]=dep[u]+1;
			dfs(v);
		}
}
inline int lca(int u,int v){
	if(dep[u]>dep[v])swap(u,v);
	for(int i=K-1;i>=0;i--)
		if(f[v][i]&&dep[f[v][i]]>=dep[u]){
			v=f[v][i];
		}
	if(u==v)return u;
	for(int i=K-1;i>=0;i--)
		if(f[u][i]&&f[v][i]&&f[u][i]!=f[v][i]){
			u=f[u][i];
			v=f[v][i];
		}
	return f[u][0];
}
inline int dis(int u,int v){
	int t=lca(u,v);
	return dep[u]+dep[v]-dep[t]*2;
}
void link(int u,int v){
	int fu=find(u);
	int fv=find(v);
	assert(1<=u&&u<=n);
	assert(1<=v&&v<=n);
	if(siz[fu]<siz[fv]){
		swap(u,v);
		swap(fu,fv);
	}
	// fprintf(stderr,"link u=%d v=%d fu=%d fv=%d\n",u,v,fu,fv);
	fa[fv]=fu;
	siz[fu]+=siz[fv];
	pts[fu].insert(pts[fu].end(),pts[fv].begin(),pts[fv].end());

	G[u].push_back(v);
	G[v].push_back(u);
	f[v][0]=u;
	dep[v]=dep[u]+1;
	dfs(v);
	for(int i=1;i<K;i++){
		for(int x:pts[fv]){
			f[x][i]=f[f[x][i-1]][i-1];
		}
	}

	vector<tuple<int,int,int>> cho;
	cho.emplace_back(dis(g[fu][0],g[fu][1]),g[fu][0],g[fu][1]);
	cho.emplace_back(dis(g[fv][0],g[fv][1]),g[fv][0],g[fv][1]);
	for(int i=0;i<2;i++)
		for(int j=0;j<2;j++){
			cho.emplace_back(dis(g[fu][i],g[fv][j]),g[fu][i],g[fv][j]);
		}
	sort(cho.begin(),cho.end());
	g[fu][0]=get<1>(cho.back());
	g[fu][1]=get<2>(cho.back());
	// for(int i=1;i<=n;i++)cerr<<dep[i]<<" \n"[i==n];
	// for(int i=1;i<=n;i++)cerr<<f[i][0]<<" \n"[i==n];
}
int findpath(int u,int fa){
	int ans= 0;
	for(int v:G[u])
		if(v !=fa) {
			ans=max(findpath(v,u)+1,ans);
		}
	return ans;
}
int query(int x,int m,int k){
	assert(1<=x&&x<=n);
	assert(1<=k&&k<=n);
	int f,t,d;
	f=find(x);
	d=max(dis(x,g[f][0]),dis(x,g[f][1]));
	// fprintf(stderr,"query x=%d m=%d k=%d : f=%d d=%d\n",x,m,k,f,d);
	// assert(d==findpath(x,-1));
	if(m<=d){
		t=m+1;
	}else{
		t=d+1+(m-d)/2;
	}
	t=min(t,siz[f]);

	int ans=(ll)binom(n-t,k)*power(binom(n,k),mod-2)%mod;
	ans=(mod+1-ans)%mod;
	// fprintf(stderr,"query x=%d m=%d k=%d : f=%d d=%d t=%d : ans=%d\n",x,m,k,f,d,t,ans);
	return ans;
}
int main(){
#ifdef memset0
	// freopen("F-big.in","r",stdin);
	freopen("F.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	fac[0]=ifac[0]=ifac[1]=1;
	for(int i=2;i<N;i++)ifac[i]=(ll)(mod-mod/i)*ifac[mod%i]%mod;
	for(int i=1;i<N;i++){
		fac[i]=(ll)fac[i-1]*i%mod;
		ifac[i]=(ll)ifac[i-1]*ifac[i]%mod;
	}
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		fa[i]=i;
		dep[i]=1;
		siz[i]=1;
		pts[i].push_back(i);
		g[i][0]=g[i][1]=i;
	}
	for(int op,u,v,x,m,k,last=0,i=1;i<=q;i++){
		cin>>op;
		if(op==1){
			cin>>u>>v;
			link(u^last,v^last);
		}else{
			cin>>x>>m>>k;
			last=query(x^last,m^last,k^last);
			cout<<last<<endl;
			// cerr<<last<<endl;
		}
		// last=0;
	}
	// cout<<"pass"<<endl;
}