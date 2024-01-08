#include<bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
using ull=unsigned long long;
const int N=3e3+9;
int n,m,x[N],y[N],ans[N],col[N];
vector<int> bkt[N<<1];
struct query{
	ull a,b,c;
	int id;
}q[N];
vector<ull> vs,vc;
inline ull dis(int x,int y){
	if(x<0)x=-x;
	if(y<0)y=-y;
	return (ull)x*x+(ull)y*y;
}
int main(){
#ifdef memset0
	freopen("A.in","r",stdin);
#else
	freopen("astronomy.in","r",stdin);
	freopen("astronomy.out","w",stdout);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	while(true){
		cin>>n;
		if(!n){
			break;
		}
		for(int i=1;i<=n;i++){
			cin>>x[i]>>y[i];
		}
		cin>>m;
		vs.clear();
		vc.clear();
		ull a,b,c;
		for(int i=1;i<=m;i++){
			cin>>a>>b>>c;
			ans[i]=0;
			q[i]={a,b,c,i};
			vs.push_back(a);
			vs.push_back(b);
			vc.push_back(c);
		}
		sort(all(vs)),vs.erase(unique(all(vs)),vs.end());
		sort(all(vc)),vc.erase(unique(all(vc)),vc.end());
		for(int i=0;i<vs.size();i++){
			bkt[i].clear();
		}
		for(int i=1;i<=n;i++){
			ull w=dis(x[i],y[i]);
			// cerr<<"! "<<w<<endl;
			int k=lower_bound(all(vs),w)-vs.begin();
			if(k==vs.size()||vs[k]!=w){
				continue;
			}
			bkt[k].push_back(i);
		}
		map<pair<ull,ull>,vector<pair<ull,int>>> mp;
		for(int i=1;i<=m;i++){
			mp[make_pair(q[i].a,q[i].b)].push_back(make_pair(q[i].c,q[i].id));
		}
		for(const auto &it:mp){
			auto [a,b]=it.first;
			for(auto [c,id]:it.second){
				c=lower_bound(all(vc),c)-vc.begin();
				col[c]=0;
			}
			a=lower_bound(all(vs),a)-vs.begin();
			b=lower_bound(all(vs),b)-vs.begin();
			for(int i:bkt[a])
				for(int j:bkt[b]){
					if(a==b&&i>=j)continue;
					ull w=dis(x[i]-x[j],y[i]-y[j]);
					int k=lower_bound(all(vc),w)-vc.begin();
					if(k==vc.size()||vc[k]!=w){
						continue;
					}
					col[k]++;
				}
			for(auto [c,id]:it.second){
				c=lower_bound(all(vc),c)-vc.begin();
				ans[id]+=col[c];
			}
		}
		for(int i=1;i<=m;i++){
			cout<<ans[i]<<endl;
		}
	}
}/**/