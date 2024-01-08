#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
#ifndef memset0
	#define endl '\n'
#endif
#define all(x) begin(x),end(x)
using namespace std;
const int N=2e5+9,S=400,B=N/S+9;
int n,m,f[N],g[N],h[N],bln[N];
bool vis[N];
vector<int> st[N];
template<const int N> struct Bukket:array<int,N>{
	int len=0;
	void clear(){len=0;}
	void push_back(int x){this->operator[](len++)=x;}
};
Bukket<N> bkt;
struct Block{
	int l,r,lazy;
	bool force=true;
	Bukket<S+9> q;
	void rebuild(){
		for(int i=l;i<=r;i++)f[i]=max(1,f[i]-lazy);
		lazy=0;
		for(int i=l;i<=r;i++)
			if(f[i]>=l){
				g[i]=g[f[i]];
				h[i]=h[f[i]]+1;
			}else{
				g[i]=f[i];
				h[i]=1;
			}
		if(force){
			force=false;
			for(int i=l;i<=r;i++)if(f[i]>=l){force=true; break;}
		}
	}
	void jump(int d){
		if(force){
			for(int i=l;i<=r;i++)f[i]=max(1,f[i]-d);
			rebuild();
		}else{
			lazy+=d;
		}
	}
}b[B];
int getf(int x){return b[bln[x]].force?f[x]:max(1,f[x]-b[bln[x]].lazy);}
int getg(int x){return b[bln[x]].force?g[x]:max(1,f[x]-b[bln[x]].lazy);}
int geth(int x){return b[bln[x]].force?h[x]:1;}
int depth(int u){
	int dep=0;
	// cerr<<"DEPTH "<<u;
	while(u!=1){
		dep+=geth(u);
		u=getg(u);
	}
	// cerr<<" = "<<dep<<endl;
	return dep;
}
int lca(int u,int v){
	if(u==v)return u;
	int pu=u,pv=v;
	while(u!=v){
		if(u>v)swap(u,v),swap(pu,pv);
		pv=v,v=getg(v);
	}
	u=pu,v=pv;
	while(u!=v){
		if(u>v)swap(u,v);
		v=getf(v);
	}
	return u;
}
int solve(vector<int> &a){
	sort(all(a));
	a.erase(unique(all(a)),a.end());
	if(a.size()==1)return 1;
	int t=a[0];
	for(int i=1;t!=1&&i<a.size();i++){
		t=lca(t,a[i]);
	}
	int ans=1-depth(t);
	for(int x:a){
		vis[x]=true;
		bkt.push_back(x);
		b[bln[x]].q.push_back(x);
		st[x].push_back(x);
	}
	auto build=[&](int x){
		// cerr<<"build "<<x<<" :: ";for(int y:st[x])cerr<<y<<",";cerr<<endl;
		if(st[x].size()<=1){
			ans+=st[x][0]==x?0:geth(st[x][0]);
		}else{
			for(int u:st[x]){
				if(u==x)continue;
				int f=getf(u);
				// cerr<<">>> "<<u<<" -> "<<f<<endl;
				while(!vis[f]){
					vis[f]=true;
					bkt.push_back(f);
					ans++;
					u=f,f=getf(u);
					// cerr<<"... "<<u<<" -> "<<f<<endl;
				}
				ans++;
			}
		}
		st[x].clear();
	};
	for(int i=bln[n];i>=1;i--){
		for(int j=0;j<b[i].q.len;j++){
			int x=b[i].q[j],y=getg(x);
			build(x);
			if(!vis[y]){
				vis[y]=true;
				bkt.push_back(y);
				if(y>1)b[bln[y]].q.push_back(y);
			}
			st[y].push_back(x);
		}
		b[i].q.clear();
	}
	build(1);
	for(int i=0;i<bkt.len;i++)vis[bkt[i]]=false;
	bkt.clear();
	return ans;
}
int main(){
#ifdef memset0
	freopen("H.in","r",stdin);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>m;
	for(int i=2;i<=n;i++)cin>>f[i];
	for(int i=2;i<=n;i++)bln[i]=(i-1)/S+1;
	for(int i=2;i<=n;i++)b[bln[i]].r=i;
	for(int i=n;i>=2;i--)b[bln[i]].l=i;
	for(int i=1;i<=bln[n];i++)b[i].rebuild();
	for(int op,l,r,d,k,i=1;i<=m;i++){
		cin>>op;
		if(op==1){
			cin>>l>>r>>d;
			// cerr<<"! "<<"MODIFY "<<l<<" "<<r<<" "<<d<<endl;
			if(bln[l]==bln[r]){
				for(int i=l;i<=r;i++)f[i]=max(1,f[i]-d);
				b[bln[l]].rebuild();
			}else{
				for(int i=l;i<=b[bln[l]].r;i++)f[i]=max(1,f[i]-d);
				b[bln[l]].rebuild();
				for(int i=b[bln[r]].l;i<=r;i++)f[i]=max(1,f[i]-d);
				b[bln[r]].rebuild();
				for(int i=bln[l]+1;i<bln[r];i++)b[i].jump(d);
			}
		}else{
			cin>>k;
			// cerr<<"! QUERY "<<k<<endl;
			vector<int> b(k);
			for(int &x:b)cin>>x;
			cout<<solve(b)<<endl;
		}
	}
}