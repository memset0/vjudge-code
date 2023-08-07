#include<bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
const int N=5e5+9,mod=998244353;
int n,m[N],cho[N],rnk[N],irnk[N];
vector<int> a[N],ans[N];
vector<long long> b[N],val;
struct TRI{
	int n;
	long long s[N];
	void init(int _n){
		n=_n;
		n+=4;
		fill(s,s+n+8,0);
	}
	void add(int k,int x){
		// fprintf(stderr,"add %d %d\n",k,x);
		k+=2;
		for(;k<=n;k+=k&-k){
			s[k]+=x;
		}
	}
	int ask(int k){
		// fprintf(stderr,"ask %d => ",k);
		k+=2;
		long long r=0;
		for(;k;k-=k&-k){
			r+=s[k];
		}
		// fprintf(stderr,"%lld\n",r%mod);
		return r%mod;
	}
}tri;
int main(){
#ifdef memset0
	freopen("J.in","r",stdin);
#endif
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>m[i];
		a[i].resize(m[i]);
		b[i].resize(m[i]);
		for(int j=0;j<m[i];j++){
			cin>>b[i][j];
			b[i][j]=b[i][j]*(n<<1)+i;
			val.push_back(b[i][j]);
		}
	}
	sort(all(val));
	for(int i=1;i<=n;i++){
		for(int j=0;j<m[i];j++){
			a[i][j]=lower_bound(all(val),b[i][j])-val.begin()+1;
		}
		sort(all(a[i]));
	}
	set<int> st;
	for(int i=1;i<=n;i++){
		auto it=st.upper_bound(a[i][0]);
		int lim=it==st.end()?INT_MAX:*it;
		auto k=--lower_bound(all(a[i]),lim);
		st.insert(*k);
		cho[i]=*k;
	}
	vector<int> flat;
	for(int x:st){
		flat.push_back(x);
	}
	for(int i=1;i<=n;i++){
		rnk[i]=lower_bound(all(flat),cho[i])-flat.begin()+1;
		irnk[rnk[i]]=i;
		while(a[i].size()&&a[i].back()>cho[i]){
			a[i].pop_back();
		}
		ans[i].resize(m[i]);
	}
	// for(int i=1;i<=n;i++)cerr<<cho[i]<<" \n"[i==n];
	// for(int i=1;i<=n;i++)cerr<<rnk[i]<<" \n"[i==n];
	// for(int i=1;i<=n;i++)cerr<<irnk[i]<<" \n"[i==n];
	// for(int i=1;i<=n;i++)for(int j=0;j<a[i].size();j++)cerr<<a[i][j]<<" \n"[j+1==a[i].size()];
	a[0]={-1};
	tri.init(1);
	tri.add(0,1);
	for(int i=1;i<=n;i++){
		int ui=irnk[i],vi=irnk[i-1];
		// fprintf(stderr,"%d -> %d\n",vi,ui);
		// for(int j=0;j<a[ui].size();j++)cerr<<a[ui][j]<<" \n"[j+1==a[ui].size()];
		for(int j=0;j<a[ui].size();j++){
			int k=lower_bound(all(a[vi]),a[ui][j])-a[vi].begin();
			// cerr<<"! "<<k<<endl;
			ans[ui][j]=tri.ask(k-1);
		}
		// for(int j=0;j<a[ui].size();j++)cerr<<ans[ui][j]<<" \n"[j+1==a[ui].size()];
		tri.init(m[ui]);
		for(int j=0;j<a[ui].size();j++){
			tri.add(j,ans[ui][j]);
		}
	}
	long long final=0;
	for(int j=0;j<a[irnk[n]].size();j++){
		final+=ans[irnk[n]][j];
	}
	cout<<(final%mod)<<endl;
}
