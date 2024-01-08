#include<bits/stdc++.h>
#define all(x) begin(x),end(x)
using namespace std;
const int N=1e5+9;
int T,n,m,a[N],b[N],c[N],w[N];
vector<int> neg,pos,tot,ans;
long long l,r,mid,sa[N],sb[N],lim[N];
bool check(long long x){
	// cerr<<"! check >> "<<x<<endl;
	for(int i=1;i<=n;i++){
		// lim[i]=x/c[i]-sb[1]+b[i];
		lim[i]=x/c[i]-sb[1]-b[i];
	}
	sort(all(neg),[&](int i,int j){return lim[i]-w[i]==lim[j]-w[j]?w[i]<w[j]:lim[i]-w[i]>lim[j]-w[j];});
	sort(all(pos),[&](int i,int j){return lim[i]==lim[j]?w[i]<w[j]:lim[i]<lim[j];});
	long long sum=0;
	tot.clear();
	tot.insert(tot.end(),all(neg));
	tot.insert(tot.end(),all(pos));
	for(int x:tot){
		// cout<<x<<" "<<w[x]<<" "<<lim[x]<<endl;
		sum+=w[x];
		if(sum>lim[x])return false;
	}
	ans=tot;
	return true;
}
int main(){
#ifdef memset0
	freopen("E.in","r",stdin);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>n;
		pos.clear();
		neg.clear();
		ans.clear();
		for(int i=1;i<=n;i++){
			cin>>a[i]>>b[i]>>c[i];
			w[i]=a[i]-b[i];
			if(w[i]>=0){
				pos.push_back(i);
			}else{
				neg.push_back(i);
			}
		}
		sb[n+1]=0;
		for(int i=1;i<=n;i++)sa[i]=sa[i-1]+a[i];
		for(int i=n;i>=1;i--)sb[i]=sb[i+1]+b[i];
		l=r=0;
		for(int i=1;i<=n;i++){
			r=max(r,(long long)c[i]*(sa[i]+sb[i]));
		}
		// cerr<<"! "<<l<<" "<<r<<endl;
		while(l<=r){
			mid=(l+r)>>1;
			// cerr<<"check "<<mid<<" >> "<<check(mid)<<endl;
			if(check(mid)){
				// cerr<<"find "<<mid<<endl;
				r=mid-1;
			}else{
				l=mid+1;
			}
		}
		assert(ans.size()==n);
		ans.insert(ans.begin(),0);
		for(int i=1;i<=n;i++)cout<<ans[i]<<" \n"[i==n];
		// sb[n+1]=0;
		// for(int i=1;i<=n;i++)sa[i]=sa[i-1]+a[ans[i]];
		// for(int i=n;i>=1;i--)sb[i]=sb[i+1]+b[ans[i]];
		// long long val=0;
		// for(int i=1;i<=n;i++)val=max(val,(long long)c[ans[i]]*(sa[i]+sb[i]));
		// cout<<val<<endl;
	}
}