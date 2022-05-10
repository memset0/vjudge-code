#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=5e5+10;
int T,n,fl,mod;
char s[N];
long long w,ans,dis[2][N];
std::vector<int> key;
struct atom{
	int b,k,l;
};
std::vector<atom> res;
namespace border_finder{
	const int b=131131,p1=998244353,p2=1e9+7;
	int f[N],g[N],pf[N],pg[N];
	std::vector<int> vet;
	inline int query(int l,int r,int *a,int *pa,int p){
		int res=(a[r]-(long long)a[l-1]*pa[r-l+1])%p;
		return res<0?res+p:res;
	}
	void solve(int n){
		pf[0]=pg[0]=1,vet.clear(),res.clear();
		for(int i=1;i<=n;i++){
			pf[i]=(long long)pf[i-1]*b%p1;
			pg[i]=(long long)pg[i-1]*b%p2;
			f[i]=((long long)f[i-1]*b+s[i]-'a')%p1;
			g[i]=((long long)g[i-1]*b+s[i]-'a')%p2;
		}
		for(int i=n-1;i>=1;i--)
			if(query(1,i,f,pf,p1)==query(n-i+1,n,f,pf,p1)&&query(1,i,g,pg,p2)==query(n-i+1,n,g,pg,p2))
				vet.push_back(n-i);
		vet.push_back(n);
		// for(auto x:vet)printf("%d,",x); putchar('\n');
		int first=vet[0],delta=0,cnt=0;
		for(int i=1;i<vet.size();i++)if(!delta){
			delta=vet[i]-vet[i-1],cnt=1;
		}else{
			if(vet[i]-vet[i-1]==delta)++cnt;
			else{
				res.push_back((atom){first,delta,cnt});
				first=vet[i],delta=0,cnt=0;
			}
		}
		res.push_back((atom){first,delta,cnt});
	}
}
void spfa(std::vector<int> &key,long long *dis){
	static int l,r,q[N<<3]; static bool inq[N];
	mod=*std::max_element(key.begin(),key.end());
	memset(dis,63,mod<<3);
	q[l=r=1]=dis[0]=0;
	while(l<=r){
		int u=q[l++]; inq[u]=0;
		for(int w:key){
			int c=(u+w)/mod; int v=u+w-c*mod;
			if(dis[u]+c<dis[v]){
				dis[v]=dis[u]+c;
				// printf("%d[%d] -> %d[%d] | %d\n",u,dis[u],v,dis[v],w);
				if(!inq[v])inq[v]=1,q[++r]=v;
			}
		}
	}
	// printf("   DIS | ");
	// for(int i=0;i<mod;i++)printf("%lld%c",dis[i]," \n"[i==mod-1]);
}
void trans(long long *f,long long *g,const atom &x){
	
}
int main(){
#ifdef local
	freopen("1.in","r",stdin);
#endif
	for(read(T);T--;ans=0,key.clear()){
		scanf("%d%lld%s",&n,&w,s+1);
		border_finder::solve(n);
		// for(auto x:res){
		// 	key.push_back(x.b);
		// 	if(x.l)key.push_back(x.b+x.k*x.l);
		// }
		// spfa(key,dis[fl]);
		// for(auto x:res){
		// 	trans(dis[fl],dis[fl^1],x);
		// 	fl^=1;
		// }
		for(auto x:res){
			// printf("    => | %d %d %d\n",x.k,x.b,x.l);
			for(int i=0;i<=x.l;i++)key.push_back(x.b+x.k*i);
		}
		spfa(key,dis[fl]);
		for(int i=0;i<mod;i++)if(dis[fl][i]!=4557430888798830399){
			ans+=std::max(0ll,(w-n-i)/mod+1-dis[fl][i]);
		}
		printf("%lld\n",ans);
	}
}