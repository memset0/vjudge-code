#pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
#ifndef memset0
	#define endl '\n'
#endif
#define all(x) begin(x),end(x)
using namespace std;
const int N=4e5+9,S=250,B=N/S+9;
int n,m,f[N],g[N],h[N],bln[N];
struct Block{
	int l,r,lazy;
	bool force=true;
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
		// cerr<<"FORCE :: "<<force<<endl;
		// for(int i=l;i<=r;i++)cerr<<f[i]<<" \n"[i==r];
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
	cerr<<"DEPTH "<<u;
	while(u!=1){
		dep+=geth(u);
		u=getg(u);
	}
	cerr<<" = "<<dep<<endl;
	return dep;
}
int lca(int u,int v){
	if(u==v)return u;
	int pu=u,pv=v;
	while(u!=v){
		if(u>v)swap(u,v),swap(pu,pv);
		pv=v,v=getg(v);
		// cerr<<">>>> "<<u<<" "<<v<<endl;
	}
	u=pu,v=pv;
	while(u!=v){
		if(u>v)swap(u,v);
		v=getf(v);
		// cerr<<">> "<<u<<" "<<v<<endl;
	}
	return u;
}
int solve(vector<int> &b){
	sort(all(b));
	b.erase(unique(all(b)),b.end());
	if(b.size()==1)return 1;
	vector<int> c(b.size()-1);
	for(int i=0;i<c.size();i++)c[i]=lca(b[i],b[i+1]);
	b.insert(b.end(),all(c));
	sort(all(b));
	b.erase(unique(all(b)),b.end());
	for(int x:b)cerr<<x<<",";cerr<<endl;
	int ans=1;
	for(int i=0;i+1<b.size();i++){
		int t=lca(b[i],b[i+1]);
		ans+=depth(b[i+1])-depth(t);
	}
	return ans;
}
int main(){
#ifdef memset0
	// freopen("H2.in","r",stdin);
	freopen("H2-big.in","r",stdin);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>m;
	for(int i=2;i<=n;i++)cin>>f[i];
	for(int i=2;i<=n;i++)bln[i]=(i-1)/S+1;
	for(int i=2;i<=n;i++)b[bln[i]].r=i;
	for(int i=n;i>=2;i--)b[bln[i]].l=i;
	for(int i=1;i<=bln[n];i++)b[i].rebuild();
	for(int op,l,r,d,u,v,lastans=0,i=1;i<=m;i++){
		cin>>op;
		if(op==1){
			cin>>l>>r>>d;
			l^=lastans,r^=lastans,d^=lastans;
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
			cin>>u>>v;
			u^=lastans,v^=lastans;
			cout<<(lastans=lca(u,v))<<endl;
		}
	}
}