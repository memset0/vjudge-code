#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);putchar(x%10+'0');
}
const int N=2e5+10,M=200,mod=998244353;
bool E[6][6];
long long atm[M];
std::vector<int> vet,G[N];
std::map<long long,int> map;
int n,m,u,v,pos,p[]={0,1,2,3,4,5},id[N],vis[N],cnt[M],lim[M];
struct z{
	int x;
	inline z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}fac[N],ifac[N],ans[N],f[128][8];
inline z binom(int n,int m){return n<m?0:fac[n]*ifac[m]*ifac[n-m];}
inline z fpow(z a,int b){z s(1);for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}
void dfs(int u){
	vis[u]=1,vet.push_back(u);
	for(int v:G[u])if(!vis[v])dfs(v);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(m);
	for(int i=1;i<=m;i++){
		read(u),read(v);
		G[u].push_back(v),G[v].push_back(u);
	}
	fac[0]=fac[1]=ifac[0]=ifac[1]=1;
	for(int i=2;i<=n;i++)fac[i]=fac[i-1]*i;
	for(int i=2;i<=n;i++)ifac[i]=(mod-mod/i)*ifac[mod%i];
	for(int i=2;i<=n;i++)ifac[i]=ifac[i-1]*ifac[i];
	for(int i=1;i<=n;i++)if(!vis[i]){
		memset(E,0,36),vet.clear(),dfs(i);
		for(int i=0;i<vet.size();i++)id[vet[i]]=i;
		long long sta=0;
		for(int u:vet)
			for(int v:G[u])
				E[id[u]][id[v]]=1,sta|=1ll<<(id[u]*6+id[v]);
		auto it=map.find(sta);
		if(it!=map.end()){
			++cnt[it->second];
			continue;
		}
		++pos,atm[pos]=sta,lim[pos]=vet.size(),cnt[pos]=1;
		do{
			sta=0;
			for(int i=0;i<vet.size();i++)
				for(int j=0;j<vet.size();j++)
					if(E[p[i]][p[j]])sta|=1ll<<(i*6+j);
			// printf("%lld\n",sta);
			// assert(map.find(sta)==map.end()||map.find(sta)->second==pos);
			map[sta]=pos;
		}while(std::next_permutation(p,p+vet.size()));
	}
	for(int i=1;i<=n;i++)ans[i]=1;
	for(int k,c=1;c<=pos;c++){
		memset(E,0,36),k=lim[c];
		// printf("> %d %d %d %lld\n",c,lim[c],cnt[c],atm[c]);
		for(int i=0;i<6;i++)
			for(int j=0;j<6;j++)
				E[i][j]=atm[c]>>(i*6+j)&1;
		// for(int i=0;i<6;i++)for(int j=0;j<6;j++)print(E[i][j]),putchar(" \n"[j==5]);
		memset(f,0,sizeof f),f[0][0]=1;
		for(int x=0;x<(1<<k);x++){
			for(int y=1;y<(1<<k);y++)if((x&y)==0){
				bool fl=true;
				// for(int i=0;i<k;i++)if((x>>i)&1^1){
				// 	fl=y&(1<<i);
				// 	break;
				// }
				for(int i=0;i<k;i++)
					for(int j=i+1;j<k;j++)if(E[i][j]&&(y&(1<<i))&&(y&(1<<j))){
						fl=false;
					}
				if(fl){
					// printf(">> %d %d\n",x,y);
					for(int i=0;i<k;i++)f[x|y][i+1]=f[x|y][i+1]+f[x][i];
				}
			}
			// printf("%d > ",x);
			// for(int i=1;i<=k;i++)print(f[x][i].x),putchar(" \n"[i==k]);
		}
		// for(int i=1;i<=k;i++)print(f[(1<<k)-1][i].x),putchar(" \n"[i==k]);
		for(int j=1;j<=n;j++){
			z sum;
			for(int i=1;i<=k;i++)sum=sum+binom(j,i)*f[(1<<k)-1][i];
			ans[j]=ans[j]*fpow(sum,cnt[c]);
		}
	}
	for(int i=1;i<=n;i++)print(ans[i].x),putchar(" \n"[i==n]);
}//adfjdiksfjailo;jdfaslhflui hruil whlurihlj hrjk,nafadfdsf243rewfdscx