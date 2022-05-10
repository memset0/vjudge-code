#include<bits/stdc++.h>
#define ll long long
const int N=50,mod=998244353;
int n,ans,res,fac=1,a[N],f[N][N],g[N][N];
inline int inv(int x){return x<2?1:(ll)(mod-mod/x)*inv(mod%x)%mod;}
void dfs(int u,int lim,int lst){
	if(!lst){
		// printf(">>> ");
		// for(int i=1;i<=u;i++)printf("%d%c",a[i]," \n"[i==u]);
		for(int i=1;i<=u;i++){
			for(int j=1;j<=a[i];j++)f[i][j]=a[i]-j+1;
		}
		for(int j=1;j<=a[1];j++){
			g[u+1][j]=0;
			for(int i=u;i>=1;i--)g[i][j]=g[i+1][j]+(a[i]>=j);
		}
		res=1;
		for(int i=1;i<=u;i++){
			for(int j=1;j<=a[i];j++)res=(ll)res*(f[i][j]+g[i][j]-1)%mod;
		}
		// for(int i=1;i<=u;i++)for(int j=1;j<=a[i];j++)printf("%d%c",f[i][j]," \n"[j==a[i]]);
		// for(int i=1;i<=u;i++)for(int j=1;j<=a[i];j++)printf("%d%c",g[i][j]," \n"[j==a[i]]);
		res=(ll)fac*inv(res)%mod,res=(ll)res*res%mod;
		// printf("-> %d / %d\n",a[1],res);
		ans=(ans+(ll)res*a[1])%mod;
		return;
	}
	for(int i=std::min(lst,lim);i>=1;i--)a[u+1]=i,dfs(u+1,i,lst-i);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	std::cin>>n;
	for(int i=1;i<=n;i++)fac=(ll)fac*i%mod;
	dfs(0,n,n);
	std::cout<<(ll)ans*inv(fac)%mod<<std::endl;
}