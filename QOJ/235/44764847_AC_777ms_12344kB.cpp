#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
const int N=1e6+9;
bool vis[N];
vector<int> pri,d;
long long cache[N];
vector<pair<int,int>> fac;
void dfs(int i,int x){
	if(i==fac.size()){
		d.push_back(x);
		return;
	}
	for(int k=0;k<=fac[i].second;k++){
		dfs(i+1,x);
		x*=fac[i].first;
	}
}
long long solve(int n){
	if(cache[n]){
		return cache[n];
	}
	d.clear();
	fac.clear();
	int x=n;
	for(int i=0;pri[i]*pri[i]<=x;i++)
		if(x%pri[i]==0){
			fac.emplace_back(pri[i],0);
			while(x%pri[i]==0){
				x/=pri[i];
				++fac.back().second;
			}
		}
	if(x>1){
		fac.emplace_back(x,1);
	}
	// for(auto [x,y]:fac)cerr<<"fac:"<<x<<" "<<y<<endl;
	dfs(0,1);
	sort(d.begin(),d.end());
	// for(int x:d)cerr<<"d:"<<x<<endl;
	long long ans=-1;
	for(int i=0;i<d.size();i++)
		for(int j=i;j<d.size()&&d[i]+d[j]<n;j++){
			int z=n-d[i]-d[j];
			if(n%z==0){
				ans=max(ans,(long long)d[i]*d[j]*z);
			}
		}
	return cache[n]=ans;
}
int main(){
#ifdef memset0
	freopen("A.in","r",stdin);
	// freopen("A.out","w",stdout);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	for(int i=2;i<N;i++){
		if(!vis[i]){
			pri.push_back(i);
		}
		for(int j=i*2;j<N;j+=i){
			vis[j]=true;
		}
	}
	// for(int i=1;i<=1e6;i++)cout<<solve(i)<<endl;
	int T,n;
	cin>>T;
	while(T--){
		cin>>n;
		cout<<solve(n)<<endl;
	}
}