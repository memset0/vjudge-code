#include<bits/stdc++.h>
#define ll long long
#define pair std::pair<int,int>
const int N=310,M=32000,mod=1e9+7;
int T,n,m,l,tl,pc,sqn,ans[N],vis[M],bln[N],pri[M];ll a[N],ls[N];
std::vector<ll> fac;
std::vector<pair> v[N];
std::multiset<int> c[M];
template<class T> inline T gcd(T x,T y){return y?gcd(y,x%y):x;}
struct query{
	int l,r,id;
	inline bool operator<(const query &other)const{
		return bln[l]==bln[other.l]?r<other.r:l<other.l;
	}
}q[N];
inline int fpow(int a,int b){
	int s=1;
	for(;b;b>>=1,a=(ll)a*a%mod)if(b&1)s=(ll)s*a%mod;
	return s;
}
inline void add(const std::vector<pair> &vet){
	// printf("add > ");for(int j=0;j<vet.size();j++)printf("[%d %d]%c",vet[j].first,vet[j].second," \n"[j==vet.size()-1]);
	for(auto it:vet)c[it.first].insert(it.second);
}
inline void del(const std::vector<pair> &vet){
	// printf("del > ");for(int j=0;j<vet.size();j++)printf("[%d %d]%c",vet[j].first,vet[j].second," \n"[j==vet.size()-1]);
	for(auto it:vet)c[it.first].erase(c[it.first].find(it.second));
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	for(int i=2;i<M;i++){
		if(!vis[i])pri[++pc]=i;
		for(int j=1;j<=pc&&i*pri[j]<M;j++){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0)break;
		}
	}
	for(scanf("%d",&T);T--;){
		scanf("%d%d",&n,&m),sqn=sqrt(n),l=0,fac.clear();
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]),bln[i]=i/sqn,v[i].clear();
		for(int i=1,fl;fl=0,i<=pc;i++){
			for(int j=1;j<=n;j++)if(a[j]%pri[i]==0){fl=true;break;}
			if(fl)ls[++l]=pri[i];
		}
		for(int i=1;i<=n;i++)
			for(int j=1,cnt;j<=l;j++)if(a[i]%ls[j]==0){
				cnt=0;while(a[i]%ls[j]==0)++cnt,a[i]/=ls[j];
				v[i].push_back(std::make_pair(j,cnt));
			}
		for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++){
			fac.push_back(gcd(a[i],a[j]));
			fac.push_back(a[i]/gcd(a[i],a[j]));
			fac.push_back(a[j]/gcd(a[i],a[j]));
		}
		std::sort(fac.begin(),fac.end()),fac.erase(std::unique(fac.begin(),fac.end()),fac.end()),tl=l;
		for(int i=fac[0]==1?1:0,fl;fl=0,i<fac.size();i++){
			for(int j=1;j<=n;j++)if(a[j]%fac[i]==0){fl=true;break;}
			if(fl)ls[++l]=fac[i];
		}
		for(int i=1;i<=n;i++)
			for(int j=tl+1,cnt;j<=l;j++)if(a[i]%ls[j]==0){
				cnt=0;while(a[i]%ls[j]==0)++cnt,a[i]/=ls[j];
				v[i].push_back(std::make_pair(j,cnt));
			}
		for(int i=1;i<=m;i++)scanf("%d%d",&q[i].l,&q[i].r),q[i].id=i,ans[i]=1;
		std::sort(q+1,q+m+1);
		// for(int i=1;i<=n;i++){
		// 	printf("%d %d > ",i,a[i]);
		// 	for(int j=0;j<v[i].size();j++)printf("[%d %d]%c",v[i][j].first,v[i][j].second," \n"[j==v[i].size()-1]);
		// }
		int ul=1,ur=0;
		for(int i=1;i<=m;i++){
			while(ul>q[i].l)add(v[--ul]);while(ur<q[i].r)add(v[++ur]);
			while(ul<q[i].l)del(v[ul++]);while(ur>q[i].r)del(v[ur--]);
			for(int j=1;j<=l;j++)if(c[j].size()){
				ans[q[i].id]=(ll)ans[q[i].id]*fpow(ls[j]%mod,*c[j].rbegin())%mod;
				// printf("[%d] %d %d\n",q[i].id,ls[j],*c[j].begin());
			}
		}
		while(ul<=ur)del(v[ur--]);
		for(int i=1;i<=m;i++)printf("%d\n",ans[i]);
	}
}