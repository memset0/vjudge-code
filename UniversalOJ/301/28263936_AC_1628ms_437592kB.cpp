#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0;register char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
}
const int N=5e5+10,M=300;
int n,m,sqn,a[N],S[N],ans[N];
std::vector<std::pair<int,int>> q[N];
inline void add(int k,int x){for(;k<=n;k+=k&-k)S[k]+=x;}
inline int ask(int k){int r=0;for(;k;k-=k&-k)r+=S[k];return r;}
struct young{
	int fl,a[M][N];
	inline void insert(int x,int k=1e9,int u=1){
		k=(fl?std::lower_bound<int*,int>:std::upper_bound<int*,int>)(a[u]+1,a[u]+std::min(a[u][0],k)+1,x)-a[u];
		if(k>a[u][0]){
			a[u][++a[u][0]]=x;
			if(fl)add(a[u][0],1);
		}else{
			if(u<sqn)insert(a[u][k],k-1,u+1);
			a[u][k]=x;
		}
	}
}s,t;
int query(int k){
	int res=ask(k);
	for(int i=1;i<=std::min(k,sqn);i++)res+=std::max(0,t.a[i][0]-sqn);
	return res;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(m),sqn=ceil(sqrt(n)),s.fl=1,t.fl=0;
	for(int i=1;i<=n;i++)read(a[i]);
	for(int i=1,k,v;i<=m;i++){
		read(k),read(v);
		q[k].push_back(std::make_pair(std::min(v,n+1),i));
	}
	for(int i=1;i<=n;i++){
		s.insert(a[i]),t.insert(-a[i]);
		for(std::pair<int,int> it:q[i])ans[it.second]=query(it.first);
	}
	for(int i=1;i<=m;i++)printf("%d\n",ans[i]);
}