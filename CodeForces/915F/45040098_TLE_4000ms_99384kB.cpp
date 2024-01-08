#include<bits/stdc++.h>
using namespace std;
const int N=1e6+9;
int n,root,total,a[N],fa[N],siz[N],mxp[N];
bool vis[N];
long long ans;
vector<int> G[N];
void getroot(int u){
	siz[u]=1;
	mxp[u]=0;
	for(int v:G[u])
		if(!vis[v]&&v!=fa[u]){
			fa[v]=u;
			getroot(v);
			siz[u]+=siz[v];
			mxp[u]=max(mxp[u],siz[v]);
		}
	mxp[u]=max(mxp[u],total-siz[u]);
	if(!root||mxp[u]<mxp[root])root=u;
}
long long calc(vector<pair<int,int>>::iterator begin,vector<pair<int,int>>::iterator end){
//	cerr<<"calc "<<(end-begin)<<endl;
	long long sum=0;
	sort(begin,end);
	int cnt=0;
	for(auto it=begin;it!=end;++it){
//		cerr<<"> "<<it->first<<" "<<it->second<<endl;
		sum+=(long long)(++cnt)*it->first;
	}
	sort(begin,end,[](const pair<int,int> &a,const pair<int,int> &b){
		return a.second>b.second;
	});
	cnt=0;
	for(auto it=begin;it!=end;++it){
		sum-=(long long)(++cnt)*it->second;
	}
	return sum;
}
vector<pair<int,int>> cur;
void collect(int u,int mx,int mn){
	siz[u]=1;
	mx=max(mx,a[u]);
	mn=min(mn,a[u]);
	cur.emplace_back(mx,mn);
//	cerr<<"> "<<u<<" "<<mx<<" "<<mn<<endl;
	for(int v:G[u])
		if(!vis[v]&&v!=fa[u]){
			fa[v]=u;
			collect(v,mx,mn);
			siz[u]+=siz[v];
		}
}
void solve(int u){
	vis[u]=true;
	cur.clear();
	cur.emplace_back(a[u],a[u]);
//	cerr<<"solve "<<u<<endl;
	for(int v:G[u])
		if(!vis[v]){
			fa[v]=u;
			size_t t=cur.size();
			collect(v,a[u],a[u]);
			ans-=calc(cur.begin()+t,cur.end());
		}
	ans+=calc(cur.begin(),cur.end());
	for(int v:G[u])
		if(!vis[v]){
			root=0,total=siz[v];
			getroot(v);
			solve(root);
		}
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int u,v,i=1;i<n;i++){
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	root=0,total=n;
	getroot(1);
	solve(root);
	for(int i=1;i<=n;i++)assert(vis[i]);
	cout<<ans<<endl;
}


//template<class T> struct tri{
//	T s[N];
//	inline void add(int k,int x){
//		for(;k<N;k+=k&-k)s[k]+=x;
//	}
//	inline T ask(int k){
//		T r=0;
//		for(;k;k-=k&-k)r+=s[k];
//		return r;
//	}
//};
//tri<int> c;
//tri<long long> s;
//long long old_calc(vector<pair<int,int>> &cur){
//	sort(cur.begin(),cur.end());
////	long long ans=0;
////	for(int i=0;i<cur.size();i++)
////		for(int j=i;j<cur.size();j++){
////			ans+=max(cur[i].first,cur[j].first)-min(cur[i].second,cur[j].second);
////		}
////	cerr<<"! "<<ans<<endl;
//	vector<long long> pre(cur.size());
//	pre[0]=cur[0].second;
//	for(int i=1;i<cur.size();i++){
//		pre[i]=pre[i-1]+cur[i].second;
//	}
//	long long sum=0;
//	for(int i=0;i<cur.size();i++){
//		c.add(cur[i].second,1);
//		s.add(cur[i].second,cur[i].second);
////		cerr<<cur[i].first<<" "<<cur[i].second<<" "<<c.ask(cur[i].second)<<" "<<s.ask(cur[i].second)<<endl;
//		sum+=(long long)(i+1)*cur[i].first;
//		sum-=(long long)(i+1-c.ask(cur[i].second))*cur[i].second;
//		sum-=s.ask(cur[i].second);
//	}
//	for(int i=0;i<cur.size();i++){
//		c.add(cur[i].second,-1);
//		s.add(cur[i].second,-cur[i].second);
//	}
////	cerr<<"! "<<sum<<endl;
//	return sum;
//}