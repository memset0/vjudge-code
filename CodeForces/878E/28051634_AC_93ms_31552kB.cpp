#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;
const int N=5e5+7,md=1e9+7,inf=2e9+5;
int n,a[N],pr[N],_2[N],L[N],fa[N],f[N],ans[N],ps[N],s[N],m;
vector<pair<int,int> >vec[N];
inline void upd(int&a){a+=a>>31&md;}
void init(int n){for(int i=*_2=1;i<=n;++i)upd(_2[i]=(_2[i-1]<<1)-md);}
inline int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
void merge(int x,int y){
	fa[y]=x;
	if(L[x]>30&&s[x]>0||s[x]+((LL)s[y]<<L[x])>=inf)s[x]=inf;else s[x]+=s[y]<<L[x];
	f[x]=(f[x]+(LL)f[y]*_2[L[x]])%md;
	L[x]+=L[y];
}
inline int calc(int l,int r){return(pr[l]-(LL)pr[r+1]*_2[r-l+1]%md+md)%md;}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	init(n);
	for(int i=1;i<=n;++i)
		cin>>a[i],upd(f[i]=s[i]=a[i]);
	for(int i=n;i;--i)
		pr[i]=((LL)(pr[i+1]<<1)+a[i]+md)%md;
	for(int i=1;i<=n;++i)fa[i]=i,L[i]=1;
	for(int i=1;i<=m;++i){
		int l,r;
		cin>>l>>r;
		vec[r].emplace_back(l,i);
	}
	for(int i=1;i<=n;++i){
		while(find(i)>1&&s[find(i)]>=0)merge(find(find(i)-1),find(i));
		upd(ps[find(i)]=ps[find(find(i)-1)]+f[find(i)]-md);
		for(auto q:vec[i]){
			int l=q.first,id=q.second;
			ans[id]=((LL)(ps[find(i)]-ps[find(l)]+md)*2+calc(l,find(l)+L[find(l)]-1)+md)%md;
		}
	}
	for(int i=1;i<=m;++i)
		cout<<ans[i]<<'\n';
	return 0;
}