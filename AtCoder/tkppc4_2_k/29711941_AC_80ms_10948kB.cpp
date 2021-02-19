#include<bits/stdc++.h>
using namespace std;
const int N=5e5+9;
int n,m,l[N],r[N],sr[N],nxt[N];
struct atom{
	int l,r,id;
}a[N],b[N];
inline int mov(int x,int y){
	// fprintf(stderr,"mov %d %d => %d\n",x,y,max(0,x-y));
	return max(0,x-y);
}
vector<int> solve(){
	set<pair<int,int>> s;
	for(int i=1;i<=n;i++){
		s.insert(make_pair(r[i],i));
	}
	vector<int> p;
	for(int u=1;u<=n;u++)if(r[u]==m){
		p.push_back(u);
		s.erase(make_pair(r[u],u));
		while(s.size()){
			auto it=s.lower_bound(make_pair(l[u],-1));
			p.push_back(u=it->second);
			s.erase(it);
		}
		break;
	}
	reverse(p.begin(),p.end());
	return p;
}
int main(){
#ifdef memset0
	freopen("2.in","r",stdin);
#else
	// freopen("girlfriends.in","r",stdin);
	// freopen("girlfriends.out","w",stdout);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i].l>>a[i].r,sr[i]=a[i].r,a[i].id=i;
	sort(a+1,a+n+1,[&](const atom &x,const atom &y){
		return x.l<y.l;
	});
	int lim=0,loc=-1;
	for(int i=1;i<=n;i++){
		if(~loc&&lim<a[i].l)a[loc].r=a[i].l;
		if(a[i].r>lim)lim=a[i].r,loc=i;
	}
	a[loc].r=m;
	for(int i=1;i<=n;i++)l[a[i].id]=a[i].l,r[a[i].id]=a[i].r;
	auto p=solve();
	long long sum=mov(m,l[p[0]]);
	for(int i=1;i<n;i++)sum+=mov(sr[p[i-1]],l[p[i]]);
	cout<<sum<<endl;
	for(int i=0;i<n;i++)cout<<p[i]<<'\n';
}