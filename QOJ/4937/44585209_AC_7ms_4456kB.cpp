#include<bits/stdc++.h>
using namespace std;
const int N=1e5+9,mod=998244353;
int n,pre,p[N],rnk[N];
bool vis[N];
map<int,int> mp;
inline int getans(int m){
	fill(rnk,rnk+m,0);
	for(int i=1,x=1%m;;i++,x=(x<<1)%m){
		if(rnk[x]){
			pre=max(pre,rnk[x]-1);
			// cerr<<"getans "<<m<<" : "<<rnk[x]-1<<" "<<i-rnk[x]<<endl;
			return i-rnk[x];
		}
		rnk[x]=i;
	}
	return -1;
}
inline void pushpri(int p,int c){
	auto it=mp.find(p);
	if(it==mp.end()){
		mp[p]=c;
		return;
	}
	it->second=max(it->second,c);
}
inline void pushlcm(int x){
	for(int i=2;i*i<=x;i++)
		if(x%i==0){
			int cnt=0;
			while(x%i==0){
				x/=i;
				++cnt;	
			}
			pushpri(i,cnt);
		}
	if(x>1)pushpri(x,1);
}
int main(){
#ifdef memset0
	freopen("G.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>p[i];
	}
	for(int i=1;i<=n;i++)
		if(!vis[i]){
			int u=i,cnt=0;
			do{
				vis[u]=true;
				cnt++;
				u=p[u];
			}while(u!=i);
			// cerr<<"find circle "<<cnt<<endl;
			pushlcm(getans(cnt));
		}
	int ans=1;
	for(auto it:mp){
		while(it.second--){
			ans=(long long)ans*it.first%mod;
		}
	}
	cout<<(ans+pre)%mod<<endl;
}