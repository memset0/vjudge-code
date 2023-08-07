#include<bits/stdc++.h>
using namespace std;
const int N=2e5+9;
int n,m,lim,ans[N],a[N],b[N],p[N],v[N],dp[N];
int main(){
#ifdef memset0
	freopen("D.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>lim;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
	}
	set<int> st;
	for(int i=1;i<=n;i++){
		if(st.count(a[i])){
			a[i]=b[i];
			b[i]=-1;
		}
		if(st.count(a[i])){
			a[i]=-1;
			break;
		}
		st.insert(a[i]);
		++m;
		v[m]=a[i];
		p[m]=-1;
		if(b[i]&&!st.count(b[i]))p[m]=b[i];
	}
	if(m==n){
		for(int i=1;i<=n;i++){
			if(b[i]==-1||st.count(b[i])){
				b[i]=-1;
				break;
			}
			st.insert(b[i]);
			++m;
			v[m]=b[i];
			p[m]=-1;
		}
	}
	map<int,int> mp;
	for(int i=m;i>=1;i--){
		if(p[i]!=-1){
			auto it=mp.find(p[i]);
			if(it==mp.end()){
				dp[i]=m+1;
			}else{
				dp[i]=dp[it->second];
			}
		}else{
			dp[i]=i;
		}
		mp[v[i]]=i;
	}
	for(int i=1;i<=m;i++)ans[dp[i]]++;
	ans[m+1]+=lim-m;
	// for(int i=1;i<=m;i++)cerr<<ans[i]<<" \n"[i==m];
	for(int i=1;i<=n;i++){
		int cur=ans[i]+ans[n+i];
		if(i==1)cur+=ans[n<<1|1];
		cout<<cur<<'\n';
	}
}