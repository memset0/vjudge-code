#include <algorithm>
#include<bits/stdc++.h>
#define all(x) begin(x),end(x)
using namespace std;
const int N=1e5+9;
int n,m;
struct point{
	int x,y;
	bool operator<(const point &rhs)const{return x<rhs.x;}
	double at(double k){return y-k*x;}
}a[N];
set<pair<double,int>> st;
int query(double v){
	auto it=st.upper_bound(make_pair(v,114514));
	if(it==st.begin())return 0;
	return prev(it)->second;
}
void insert(double v,int w){
	if(query(v)>=w)return;
	auto it=st.insert(make_pair(v,w)).first;
	if(it==st.end())return;
	while((++it)!=st.end()){
		if(w>=it->second){
			if(next(it)!=st.end()){
				auto tmp=*next(it);
				st.erase(it);
				it=st.find(tmp);
			}else{
				st.erase(it);
				break;
			}
		}else{
			break;
		}
	}
}
bool check(double k){
	st.clear();
	fprintf(stderr,"check %.15lf\n",k);
	for(int i=1;i<=n;i++){
		int dp=query(a[i].at(k));
		if(dp+1>=m)return true;
		insert(a[i].at(k),dp+1);
	}
	return false;
}
int main(){
#ifdef memset0
	freopen("H.in","r",stdin);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
	}
	sort(a+1,a+n+1);
	double l=-1e9,r=1e9,mid,ans=1145141919810.;
	// double l=-10,r=10,mid,ans=1145141919810.;
	for(int _=1;_<=55;_++){
		mid=(l+r)/2;
		if(check(mid)){
			ans=mid;
			l=mid;
		}else{
			r=mid;
		}
	}
	cout<<fixed<<setprecision(15)<<ans<<endl;
}