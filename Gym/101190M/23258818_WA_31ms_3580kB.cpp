#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();if(f)x=-x;
}
const int N=1e5+10;
int n,m,c[N],x[N],rev[N][2];
long long ans;
struct atom{
	int v,k;
	inline atom(int v=1000000000,int k=-1):v(v),k(k){}
	inline atom add(int x)const{return atom(v+x,k);}
	inline bool update(const atom &other){
		if(other.v<v){v=other.v,k=other.k;return true;}
		return false;
	}
}res,f[N],g[N];
void maintain(int u,int v){
	for(int p=u;p!=v;p>>=1){
		f[p>>1]=g[p>>1];
		f[p>>1].update(f[p].add(rev[p][1]?-1:1));
		f[p>>1].update(f[p^1].add(rev[p^1][1]?-1:1));
	}
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#else
	freopen("mole.in","r",stdin),freopen("mole.out","w",stdout);
#endif
	read(n),read(m);
	for(int i=1;i<=n;i++)read(c[i]);
	for(int i=1;i<=m;i++)read(x[i]);
	for(int i=n;i;i--){
		if(c[i])f[i]=g[i]=atom(0,i);
		f[i>>1].update(f[i].add(1));
	}
	for(int u,v,lca,i=1;i<=m;i++){
		u=x[i],lca=-1,res=*new atom();
		for(int p=u,step=0;p;p>>=1){
			// printf("p=%d step=%d f=%d,%d\n",p,step,f[p].v,f[p].k);
			if(res.update(f[p].add(step)))lca=p;
			step+=rev[p][0]?-1:1;
		}
		v=res.k,ans+=res.v;
		// printf("%d : %d -> %d -> %d : %d %d : %lld\n",i,u,lca,v,res.k,res.v,ans);
		if(--c[v]==0){
			f[v]=g[v]=*new atom();
			if((v<<1)<=n)f[v].update(f[v<<1].add(rev[v<<1][1]?-1:1));
			if((v<<1|1)<=n)f[v].update(f[v<<1|1].add(rev[v<<1|1][1]?-1:1));
			maintain(v,0);
		}
		for(int p=u;p!=lca;p>>=1)rev[p][0]?rev[p][0]--:rev[p][1]++;
		for(int p=v;p!=lca;p>>=1)rev[p][1]?rev[p][1]--:rev[p][0]++;
		maintain(u,lca),maintain(v,lca);
		// for(int i=1;i<=n;i++)printf("[%d %d]%c",f[i].v,f[i].k," \n"[i==n]);
		// for(int i=1;i<=n;i++)printf("[%d %d]%c",g[i].v,g[i].k," \n"[i==n]);
		// for(int i=1;i<=n;i++)printf("[%d %d]%c",rev[i][0],rev[i][1]," \n"[i==n]);
		printf("%lld%c",ans," \n"[i==m]);
	}
}