#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
#define hash_t unsigned long long
const int N=1e5+10,M=1e4+10;
int n,cnt,u[N],v[N],w[N],x[N],pri[N],hsh[N];
bool vis[N];
long long ans;
hash_t val[N];
std::mt19937_64 rng(1145141919810);
std::unordered_map<int,hash_t> big;
std::vector<int> t[N];
std::vector<std::pair<int,hash_t>> G[N];
hash_t query(int x){
	if(x<M)return hsh[std::lower_bound(pri+1,pri+cnt+1,x)-pri];
	auto it=big.find(x);
	if(it==big.end())return big[x]=rng();
	return it->second;
}
void dfs(int u,int fa){
	for(const auto &e:G[u])if(e.first!=fa)
		val[e.first]=val[u]^e.second,dfs(e.first,u);
}
long long solve(){
	ans=0,big.clear();
	for(int i=1;i<=n;i++)G[i].clear();
	for(int i=1;i<=cnt;i++)hsh[i]=rng();
	for(int i=1;i<n;i++){
		int u=::u[i],v=::v[i],w=::w[i];
		hash_t x=::x[i]!=1?query(::x[i]):0;
		for(int k:t[i])x^=hsh[k];
		G[u].push_back({v,x});
		G[v].push_back({u,x});
	}
	dfs(rng()%n+1,0);
	std::sort(val+1,val+n+1);
	for(int i=1,j;i<=n;i=j+1){
		for(j=i;j<n&&val[j+1]==val[i];j++);
		ans+=(long long)(j-i+1)*(j-i);
	}
	return ans;
}
int main(){
#ifdef Ciel
	freopen("2.in","r",stdin);
	// freopen("comp/data.in","r",stdin);
#endif
	for(int i=2;i<M;i++){
		if(!vis[i])pri[++cnt]=i;
		for(int j=1;j<=cnt&&pri[j]*i<M;j++){
			vis[pri[j]*i]=1;
			if(pri[j]%i==0)break;
		}
	}
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		scanf("%d%d%d",&u[i],&v[i],&w[i]);
		int w=::w[i];
		for(int j=1;pri[j]*pri[j]<=w;j++)if(w%pri[j]==0)
			while(w%pri[j]==0)w/=pri[j],t[i].push_back(j);
		::x[i]=w;
	}
	long long res=LLONG_MAX;
	for(int T=1;T<=20;T++)res=std::min(res,solve());
	printf("%lld\n",res);
}