#include<bits/stdc++.h>
#define all(x) begin(x),end(x)
using namespace std;
const int N=1e5+9,M=4e6;
int n,m,k,tag[M],sum[M];
long long tot;
vector<int> tmp;
vector<pair<int,int>> p[N<<1];
vector<tuple<int,int,int>> q;
void update(int u,int ql,int qr,int x,int l,int r){
	// cerr<<"! update "<<u<<" "<<ql<<" "<<qr<<" "<<x<<" "<<l<<" "<<r<<endl;
	if(ql==l&&qr==r){
		tag[u]+=x;
		sum[u]+=x*(r-l+1);
		return;
	}
	int mid=(l+r)>>1;
	if(tag[u]){
		tag[u<<1]+=tag[u];
		sum[u<<1]+=tag[u]*(mid-l+1);
		tag[u<<1|1]+=tag[u];
		sum[u<<1|1]+=tag[u]*(r-mid);
		tag[u]=0;
	}
	if(qr<=mid){
		update(u<<1,ql,qr,x,l,mid);
	}else if(ql>mid){
		update(u<<1|1,ql,qr,x,mid+1,r);
	}else{
		update(u<<1,ql,mid,x,l,mid);
		update(u<<1|1,mid+1,qr,x,mid+1,r);
	}
	sum[u]=sum[u<<1]+sum[u<<1|1];
}
int query(int u,int ql,int qr,int l,int r){
	// cerr<<"! query "<<u<<" "<<ql<<" "<<qr<<" "<<l<<" "<<r<<endl;
	if(ql==l&&qr==r)return sum[u];
	int mid=(l+r)>>1;
	if(tag[u]){
		tag[u<<1]+=tag[u];
		sum[u<<1]+=tag[u]*(mid-l+1);
		tag[u<<1|1]+=tag[u];
		sum[u<<1|1]+=tag[u]*(r-mid);
		tag[u]=0;
	}
	if(qr<=mid)return query(u<<1,ql,qr,l,mid);
	if(ql>mid)return query(u<<1|1,ql,qr,mid+1,r);
	return query(u<<1,ql,mid,l,mid)+query(u<<1|1,mid+1,qr,mid+1,r);
}
void check(const vector<pair<int,int>> &a,const vector<pair<int,int>> &b){
	for(auto it:a){
		update(1,it.first,it.second,1,1,tmp.size());
	}
	for(auto it:b){
		tot-=query(1,it.first,it.second,1,tmp.size());
		if(tot<1){
			cout<<"NO"<<endl;
			exit(0);
		}
	}
	for(auto it:a){
		update(1,it.first,it.second,-1,1,tmp.size());
	}
}
int main(){
#ifdef memset0
	freopen("G.in","r",stdin);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>m>>k;
	tmp={0,m+1};
	for(int x1,x2,y,i=1;i<=k;i++){
		cin>>x1>>x2>>y;
		tmp.push_back(y);
		q.emplace_back(x1,x2,y);
	}
	sort(all(tmp));
	tmp.erase(unique(all(tmp)),tmp.end());
	if(n==1){
		cout<<"YES"<<endl;
		return 0;
	}
	// for(int x:tmp)cerr<<"! "<<x<<endl;
	for(int i=0;i+1<tmp.size();i++)
		if(tmp[i+1]-tmp[i]>2){
			cout<<"NO"<<endl;
			return 0;
		}
	for(auto [x1,x2,y]:q){
		p[y].emplace_back(x1,x2);
	}
	for(int i=1;i<=m;i++){
		vector<pair<int,int>> vec=p[i];
		vec.emplace_back(0,0);
		vec.emplace_back(n+1,n+1);
		sort(all(vec));
		p[i].clear();
		for(int j=1;j<vec.size();j++)
			if(vec[j-1].second+1<vec[j].first){
				p[i].emplace_back(vec[j-1].second+1,vec[j].first-1);
			}
		tot+=p[i].size();
	}
	tmp.clear();
	for(int i=1;i<=m;i++)
		for(int j=0;j<p[i].size();j++)
			for(int d=-2;d<=2;d++){
				tmp.push_back(p[i][j].first+d);
				tmp.push_back(p[i][j].second+d);
			}
	sort(all(tmp));
	tmp.erase(unique(all(tmp)),tmp.end());
	while(tmp.size()&&tmp.front()<1)tmp.erase(tmp.begin());
	while(tmp.size()&&tmp.back()>n)tmp.pop_back();
	for(int i=1;i<=m;i++)
		for(int j=0;j<p[i].size();j++){
			// cerr<<">>> "<<p[i][j].first<<" "<<p[i][j].second<<endl;
			p[i][j].first=lower_bound(all(tmp),p[i][j].first)-tmp.begin()+1;
			p[i][j].second=lower_bound(all(tmp),p[i][j].second)-tmp.begin()+1;
			// cerr<<"<<< "<<p[i][j].first<<" "<<p[i][j].second<<endl;
		}
	for(int i=1;i+1<=m;i++){
		check(p[i],p[i+1]);
	}
	cout<<(tot==1?"YES":"NO")<<endl;
	cerr<<"tot = "<<tot<<endl;
}