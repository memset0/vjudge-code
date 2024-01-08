#include<bits/stdc++.h>
#ifndef memset0
	#define endl '\n'
#endif
using namespace std;
const int N=1e5+9;
int n,m,a[N],cnt[N];
vector<int> fac[N],lft[N];
struct query{
	int l,r,x,ans;
	vector<int> pre,fac,mul;
}q[N];
namespace FAC{
	vector<int> pri;
	vector<pair<int,int>> res;
	void dfs(int k,int u,int x){
		if(k==pri.size()){
			if(u>1){
				res.emplace_back(u,x);
			}
			return;
		}
		dfs(k+1,u,x);
		dfs(k+1,u*pri[k],-x);
	}
	vector<pair<int,int>> factor(int x){
		// cerr<<"factor "<<x<<endl;
		pri.clear();
		for(int i=2;i*i<=x;i++)
			if(x%i==0){
				pri.push_back(i);
				while(x%i==0)x/=i;
			}
		if(x>1)pri.push_back(x);
		res.clear();
		dfs(0,1,-1);
		// for(auto it:res)fprintf(stderr,"(%d,%d) ",it.first,it.second);cerr<<endl;
		return res;
	}
}
using FAC::factor;
void solve(int l,int r,const vector<int> &qu){
	if(l==r){
		for(int x:fac[l])cnt[x]++;
		for(int t:qu){
			int sum=0;
			for(int k=0;k<q[t].fac.size();k++){
				sum+=q[t].mul[k]*(cnt[q[t].fac[k]]-q[t].pre[k]);
			}
			if(sum==r-q[t].l+1){
				q[t].ans=r;
			}
		}
		return;
	}
	vector<int> ql,qr;
	int mid=(l+r)>>1;
	if(qu.size()){
		// fprintf(stderr,"solve %d %d mid=%d\n",l,r,mid);
		// for(int t:qu)cerr<<t<<", ";cerr<<endl;
		for(int i=l;i<=mid;i++)
			for(int x:fac[i])
				cnt[x]++;
		for(int t:qu){
			if(q[t].l>mid){
				qr.push_back(t);
				continue;
			}
			int sum=0;
			for(int k=0;k<q[t].fac.size();k++){
				sum+=q[t].mul[k]*(cnt[q[t].fac[k]]-q[t].pre[k]);
				// fprintf(stderr,"q[%d] fac=%d cnt=%d pre=%d mul=%d\n",t,q[t].fac[k],cnt[q[t].fac[k]],q[t].pre[k],q[t].mul[k]);
			}
			// fprintf(stderr,"q[%d] -> sum=%d\n",t,sum);
			if(sum==mid-q[t].l+1){
				q[t].ans=mid;
				qr.push_back(t);
			}else{
				ql.push_back(t);
			}
		}
		for(int i=l;i<=mid;i++)
			for(int x:fac[i])
				cnt[x]--;
	}
	solve(l,mid,ql);
	solve(mid+1,r,qr);
}
int main(){
#ifdef memset0
	freopen("I.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	reverse(a+1,a+n+1);
	++n,a[n]=1;
	for(int i=1;i<=n;i++){
		for(auto &it:factor(a[i]))fac[i].push_back(it.first);
	}
	// for(int i=1;i<=n;i++)cerr<<a[i]<<" \n"[i==n];
	for(int i=1;i<=m;i++){
		cin>>q[i].l>>q[i].r>>q[i].x;
		tie(q[i].l,q[i].r)=make_pair((n-1)-q[i].r+1,(n-1)-q[i].l+1);
		lft[q[i].l-1].push_back(i);
		auto vec=factor(q[i].x);
		q[i].fac.resize(vec.size());
		q[i].mul.resize(vec.size());
		q[i].pre.resize(vec.size());
		// cerr<<"q "<<i<<"::"<<q[i].l<<" "<<q[i].r<<" "<<q[i].x<<endl;
		for(int j=0;j<vec.size();j++){
			q[i].fac[j]=vec[j].first;
			q[i].mul[j]=vec[j].second;
			// cerr<<"q "<<i<<"::"<<j<<" "<<q[i].fac[j]<<" "<<q[i].mul[j]<<" fac"<<endl;
		}
	}
	for(int i=1;i<=n;i++){
		for(int x:fac[i])cnt[x]++;
		for(int t:lft[i]){
			// fprintf(stderr,"lft[%d]->%d\n",i,t);
			for(int k=0;k<q[t].fac.size();k++){
				// cerr<<"q "<<t<<"::pre"<<k<<"="<<q[t].pre[k]<<endl;
				q[t].pre[k]=cnt[q[t].fac[k]];
			}
		}
	}
	memset(cnt,0,sizeof(cnt));
	vector<int> qu;
	for(int i=1;i<=m;i++){
		if(__gcd(a[q[i].l],q[i].x)==1){
			q[i].ans=q[i].l-1;
		}else{
			qu.push_back(i);
		}
	}
	solve(1,n,qu);
	for(int i=1;i<=m;i++){
		// cerr<<"q "<<i<<"::"<<q[i].l<<" "<<q[i].r<<" "<<q[i].x<<" "<<q[i].ans<<endl;
		int ans=q[i].ans+1;
		if(ans>q[i].r){
			ans=-1;
		}else{
			ans=(n-1)-ans+1;
		}
		cout<<ans<<endl;
	}
}