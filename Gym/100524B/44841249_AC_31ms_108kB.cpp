#include<bits/stdc++.h>
using namespace std;
const int N=100;
const int mod=175781251,i2=(mod+1>>1);
int n,f[N+5][N+5],g[N+5][N+5],p[N+5],ans[N+5],C[N+5][N+5];
int POW(int x,int y){
	int ret=1;
	while(y)y&1?ret=1ll*ret*x%mod:0,x=1ll*x*x%mod,y>>=1;
	return ret;
}
int main(){
	freopen("bipartite.in","r",stdin);
	freopen("bipartite.out","w",stdout);
	for(int i=0;i<=N;++i){
		C[i][0]=1;
		for(int j=1;j<=i;++j)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	g[0][0]=g[1][0]=g[0][1]=1;
	for(int i=0;i<=N;++i)for(int j=0;i+j<=N;++j){
		f[i][j]=1ll*POW(3,i*j)*C[i+j][i]%mod;
		if(!i||!j)continue;
		g[i][j]=f[i][j];
		for(int p=0;p<=i;++p)for(int q=0;q<=j;++q){
			if(p+q==0||p+q==i+j)continue;
			g[i][j]=(g[i][j]-1ll*g[p][q]*f[i-p][j-q]%mod*C[i+j-1][p+q-1]%mod+mod)%mod;
		}
	}
	p[0]=ans[0]=1;
	for(int i=1;i<=N;++i){
		for(int j=0;j<=i;++j)p[i]=(p[i]+g[j][i-j])%mod;
		p[i]=1ll*p[i]*i2%mod;
		for(int j=1;j<=i;++j)ans[i]=(ans[i]+1ll*p[j]*ans[i-j]%mod*C[i-1][j-1])%mod;
	}
	while(true){
		scanf("%d",&n);
		if(!n)return 0;
		printf("%d\n",ans[n]);
	}
	return 0;
}