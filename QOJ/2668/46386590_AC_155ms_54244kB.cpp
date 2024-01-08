#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=5e5+10;
int T,n,fl,mod;
char s[N];
long long w,ans,t[N],dis[2][N];
std::vector<int> key;
struct atom{
	int b,k,l;
};
std::vector<atom> res;
namespace priority_queue{
	int nod;
	struct node{
		int pre,nxt,i;
		long long x;
	}e[N<<1];
	inline void init(){
		nod=0;
	}
	struct set{
		int lim,hed,til;
		inline void reset(int l){
			hed=til=0,lim=l;
		}
		inline void pop_front(){ // from "til" side
			e[e[til].pre].nxt=0;
			til=e[til].pre;
		}
		inline void pop_back(){ // from "hed" side
			e[e[hed].nxt].pre=0;
			hed=e[hed].nxt;
		}
		inline void push_back(int i,long long x){
			e[++nod].i=i,e[nod].x=x;
			if(!hed||!til){
				hed=til=nod;
				e[nod].pre=e[nod].nxt=0;
			}else{
				e[nod].nxt=hed,e[hed].pre=nod;
				hed=nod;
			}
		}
		inline void insert(int i,long long x){
			while(hed&&e[hed].x>x)pop_back();
			push_back(i,x);
			while(e[til].i<i-lim)pop_front();
		}
		inline long long query(){return e[til].x;}
	};
}
priority_queue::set set[N];
namespace border_finder{
	const int b=131131,p1=998244353,p2=1e9+7;
	int f[N],g[N],pf[N],pg[N];
	std::vector<int> vet;
	inline long long query(int l,int r,int *a,int *pa,int p){
		return a[r]-(long long)a[l-1]*pa[r-l+1];
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
			if((query(1,i,f,pf,p1)-query(n-i+1,n,f,pf,p1))%p1==0&&(query(1,i,g,pg,p2)-query(n-i+1,n,g,pg,p2))%p2==0)
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
	static int l,r,q[N]; static bool inq[N];
	mod=*std::max_element(key.begin(),key.end());
	memset(dis,63,mod<<3);
	q[l=r=1]=dis[0]=0;
	while(l<=r){
		int u=q[(l++)%N]; inq[u]=0;
		for(int w:key){
			int c=(u+w)/mod,v=u+w-c*mod;
			if(dis[u]+c<dis[v]){
				dis[v]=dis[u]+c;
				if(!inq[v])inq[v]=1,q[(++r)%N]=v;
			}
		}
	}
}
void trans(long long *f,long long *g,const atom &it){
	if(!it.l){
		for(int i=0;i<mod;i++){
			g[i]=std::min(f[i],f[(i-it.b+mod)%mod]);
		}
		return;
	}
	memset(t,63,mod<<3),priority_queue::init();
	for(int i=0;i<it.k;i++)set[i].reset(it.l);
	for(int i=-mod,a=0,b=0;i<mod;i++){
		auto &set=::set[a];
		set.insert(b,i<0?f[i+mod]+1:f[i]);
		if(i>=0)t[i]=set.query();
		a++; if(a==it.k)a=0,++b;
	}
	for(int i=0;i<mod;i++){
		g[i]=std::min(f[i],i<it.b?t[i-it.b+mod]+1:t[i-it.b]);
	}
}
int main(){
	for(read(T);T--;ans=0,key.clear()){
		scanf("%d%lld%s",&n,&w,s+1);
		if((w-=n)<0){puts("0"); continue;}
		border_finder::solve(n);
		for(auto x:res){
			// printf("    => | %d %d %d\n",x.k,x.b,x.l);
			key.push_back(x.b);
			if(x.l)key.push_back(x.b+x.k*x.l);
		}
		spfa(key,dis[fl]);
		for(auto x:res){
			trans(dis[fl],dis[fl^1],x);
			fl^=1;
		}
		for(int i=0;i<mod;i++){
			ans+=std::max(0ll,(w-i)/mod+1-dis[fl][i]);
		}
		printf("%lld\n",ans);
	}
}