#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
const int N=5e3+9;
int T,n,m,a[N][N];
pii s,t;
inline pii transx(const pii &x){return {n-x.first+1,x.second};}
inline pii transy(const pii &x){return {x.first,m-x.second+1};}
vector<pii> get(int n,int m){
	vector<pii> p;
	if(n%2==1&&m%2==1){
		bool revx=false,revy=false;
		pii u={1,1};
		if(s==u||t==u){
			revx=true;
			s=transx(s);
			t=transx(t);
		}
		if(s==u||t==u){
			revy=true;
			s=transy(s);
			t=transy(t);
		}
		assert(s!=u&&t!=u);
		p.emplace_back(1,2);
		for(int i=2;i<=n;i+=2){
			p.emplace_back(i,2);
			p.emplace_back(i,1);
			p.emplace_back(i+1,1);
			p.emplace_back(i+1,2);
		}
		for(int j=3;j<m;j+=2){
			for(int i=n;i>=2;i--)p.emplace_back(i,j);
			for(int i=2;i<=n;i++)p.emplace_back(i,j+1);
		}
		for(int i=n;i>=1;i--)p.emplace_back(i,m);
		for(int i=m-1;i>=3;i--)p.emplace_back(1,i);
		if(revx){
			s=transx(s);
			t=transx(t);
			for(auto &it:p)it=transx(it);
		}
		if(revy){
			s=transy(s);
			t=transy(t);
			for(auto &it:p)it=transy(it);
		}
	}else{
		bool fl=false;
		if(n%2==1){fl=true,swap(n,m);}
		p.emplace_back(1,1);
		for(int i=1;i<=n;i+=2){
			for(int j=2;j<=m;j++)p.emplace_back(i,j);
			for(int j=m;j>=2;j--)p.emplace_back(i+1,j);
		}
		for(int i=n;i>1;i--)p.emplace_back(i,1);
		if(fl){
			for(auto &it:p)swap(it.first,it.second);
		}
	}
	return p;
}
long long getsum(const vector<pii> &p,int l,int r){
	long long sum=0;
	for(int i=l;i<=r;i++)sum+=a[p[i].first][p[i].second];
	return sum;
}
inline char getmove(const pii &a,const pii &b){
	if(a.first==b.first&&a.second+1==b.second)return 'R';
	if(a.first==b.first&&a.second-1==b.second)return 'L';
	if(a.second==b.second&&a.first+1==b.first)return 'D';
	if(a.second==b.second&&a.first-1==b.first)return 'U';
	exit(-1);
	return -1;
}
int main(){
#ifdef memset0
	freopen("I.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m>>s.first>>s.second>>t.first>>t.second;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)cin>>a[i][j];
		}
		auto p=get(n,m);
		// cerr<<s.first<<" "<<s.second<<endl;
		// cerr<<t.first<<" "<<t.second<<endl;
		// for(auto it:p)cerr<<"> "<<it.first<<" "<<it.second<<endl;
		int ii=find(p.begin(),p.end(),s)-p.begin();
		int jj=find(p.begin(),p.end(),t)-p.begin();
		int i=ii,j=jj;
		if(i>j)swap(i,j);
		long long s1=getsum(p,i+1,j-1);
		long long s2=getsum(p,0,p.size()-1)-getsum(p,i,j);
		// cerr<<s1<<" "<<s2<<endl;
		if((s1>s2&&i==ii)||(s1<=s2&&i==jj)){
			// ii->jj
			// cerr<<ii<<"=>"<<jj<<endl;
			for(int u=ii,v=(u+1)%p.size();u!=jj;u=v,v=(v+1)%p.size()){
				cout<<getmove(p[u],p[v]);
			}
		}else{
			// jj->ii
			// cerr<<ii<<"<="<<jj<<endl;
			for(int u=ii,v=(u-1+p.size())%p.size();u!=jj;u=v,v=(v-1+p.size())%p.size()){
				cout<<getmove(p[u],p[v]);
			}
		}
 		cout<<endl;
  }
}