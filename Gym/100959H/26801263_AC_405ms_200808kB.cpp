#include<bits/stdc++.h>
#define int long long
const int N=5e3+10;
int n,mod;
struct z{
	int x;
	inline z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator+(z a,z b){
		return ((long long)a.x+b.x)%mod;
		// unsigned int x=(unsigned int)a.x+b.x;
		// return x>=mod?x-mod:0;
	}
	friend inline z operator-(z a,z b){
		return ((long long)a.x-b.x+mod)%mod;
		// return a+(mod-b.x);
	}
}ans,cur,f[N],g[N],p[N],C[N][N];
signed main(){
#ifdef memset0
	freopen("1.in","r",stdin);
	// freopen("1.out","w",stdout);
#endif
	std::cin>>n>>mod,f[0]=p[0]=1;
	for(int i=1;i<=n;i++)p[i]=p[i-1]*4;
	for(int i=0;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	for(int i=2;i<=n;i+=2)
		for(int j=0;j<=i;j+=2)
			f[i]=f[i]+C[j][j>>1]*C[i-j][i-j>>1]*C[i][j];
	for(int i=2;i<=n;i+=2){
		g[i]=f[i];
		for(int j=2;j<i;j++)g[i]=g[i]-g[j]*f[i-j];
	}
	// for(int i=1;i<=n;i++)printf("%d%c",f[i]," \n"[i==n]);
	// for(int i=1;i<=n;i++)printf("%d%c",g[i]," \n"[i==n]);
	ans=(n+1)*p[n];
	for(int i=0;i<=n;i++)ans=ans-g[i]*(n-i+1)*p[n-i];
	printf("%d\n",ans.x);
}
// bjkhjkhbkhhkhkj