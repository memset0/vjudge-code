#include<bits/stdc++.h>
using namespace std;
template<class T> inline void read(T &x){
	x=0; char c=getchar(); bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
namespace mem{
	const int N=5e5+9,M=1e6+9,K=11,mod=1e9+7;
	const long long inf=1e18;
	int n,k,s,ans,w[K],c[N],p[K],d[N],cnt[K],g[M],h[2][M];
	long long f[K][M];
	struct atom{
		int k;
		long long v;
	}a[M*K];
//	void bruteforce(){}
	void init(int o,int m,long long *f){
		for(int i=1;i<=n;i++){
			g[i]=g[i-1];
			if(c[i]==o)g[i]+=d[i];
			h[0][i]=min(h[0][i-1],g[i]);
			h[1][i]=max(h[1][i-1],g[i]);
		}
//		fprintf(stderr,"%d %d %d\n",g[n],h[0][n],h[1][n]);
		for(int i=1;i<=m;i++)
			if(i+g[1]>m||i+g[1]<1){
				f[i]=1;
			}else{
				f[i]=inf;
				long long l=1,r=(long long)n*m,mid,s[2];
				while(l<=r){
					mid=(l+r)>>1;
					long long k=(mid-1)/n,t=mid-k*n;
					s[0]=min(g[n]*k+h[0][t],(long long)h[0][t]);
					s[1]=max(g[n]*k+h[1][t],(long long)h[1][t]);
					if(k){
						s[0]=min(s[0],min((long long)h[0][n],g[n]*(k-1)+h[0][n]));
						s[1]=max(s[1],max((long long)h[1][n],g[n]*(k-1)+h[1][n]));
					}
					if(i+s[1]<=m&&i+s[0]>=1){
						f[i]=mid+1;
						l=mid+1;
					}else{
						r=mid-1;
					}
				}
			}
//		for(int i=1;i<=m;i++)printf("%lld%c",f[i]," \n"[i==m]);
		sort(f+1,f+m+1);
	}
	void aknoip(){
		read(n),read(k);
		for(int i=1;i<=k;i++)read(w[i]),s+=w[i];
		for(int i=1;i<=n;i++)read(c[i]),read(d[i]);
		bool nosol=true;
		for(int i=1;i<=k;i++){
			init(i,w[i],f[i]);
			nosol=nosol&&f[i][w[i]]==inf;
//			for(int j=1;j<=w[i];j++)assert(f[i][j]>=f[i][j-1]);
		}
		if(nosol){
			print(-1,'\n');
			return;
		}
		for(int i=1;i<=k;i++)p[i]=1;
		for(int i=1;i<=s;i++){
			int u=-1;
			long long x=inf;
			for(int i=1;i<=k;i++)
				if(p[i]<=w[i]&&f[i][p[i]]<x){
					x=f[i][p[i]];
					u=i;
				}
			a[i].k=u;
			a[i].v=f[u][p[u]];
//			assert(a[i].v>=a[i-1].v);
			p[u]++;
		}
		for(int i=s;i>=1;i--){
			int cur=1;
			for(int j=1;j<=k;j++)
				if(j!=a[i].k){
					cur=(long long)cur*cnt[j]%mod;
				}
//			assert(!cur||a[i].v!=inf); 
			ans=(ans+a[i].v%mod*cur)%mod;
//			printf("%d %lld :: %lld %lld\n",a[i].k,a[i].v,cur,cur*a[i].v);
			cnt[a[i].k]++;
		}
		print(ans,'\n');
	}
}
int main(){
#ifdef memset0
	freopen("walk3.in","r",stdin);
//	freopen("walk4.out","w",stdout);
#else
	freopen("walk.in","r",stdin);
	freopen("walk.out","w",stdout);
#endif
	return mem::aknoip(),0;
}
