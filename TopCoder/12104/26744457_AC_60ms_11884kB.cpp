#include<bits/stdc++.h>
#define ll long long
class KingdomAndCities{
public:
	static const int N=60,M=2510,mod=1e9+7;
	int dp[N][N];
	struct z {
		int x;
		z(int x=0):x(x){}
		friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
		friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
		friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
	}fac[M],ifac[M];
	inline z binom(int n,int m){return n<m?0:fac[n]*ifac[m]*ifac[n-m];}
	void initfac(int n){
		fac[0]=fac[1]=ifac[0]=ifac[1]=1;
		for(int i=2;i<=n;i++)fac[i]=fac[i-1]*i;
		for(int i=2;i<=n;i++)ifac[i]=(mod-mod/i)*ifac[mod%i];
		for(int i=2;i<=n;i++)ifac[i]=ifac[i-1]*ifac[i];
	}
	KingdomAndCities(){
		memset(dp,-1,sizeof(dp));
	}
	int calc(int n,int m){
		if(n<1||m<n-1||m>n*(n-1)/2)return 0;
		if(~dp[n][m])return dp[n][m];
		z res=binom(n*(n-1)/2,m);
		for(int i=1;i<n;i++)
			for(int j=i-1;j<=std::min(m,i*(i-1)/2);j++){
				res=res-calc(i,j)*binom((n-i)*(n-i-1)/2,m-j)*binom(n-1,i-1);
			}
		// printf(">> %d %d : %d\n",n,m,res.x);
		return dp[n][m]=res.x;
	}
	int howMany(int n,int k,int m){
		initfac(std::max(n*n,m*m)+5),dp[1][0]=1;
		if(k==0)return calc(n,m);
		if(k==1){
			z res;
			res=res+(z)calc(n-1,m-1)*(m-1);
			res=res+(z)calc(n-1,m-2)*(m-2);
			return res.x;
		}
		if(k==2){
			z res;
			res=res+(z)calc(n-2,m-3)*(n-2);
			res=res+(z)calc(n-2,m-2)*2*(m-2);
			res=res+(z)calc(n-2,m-3)*2*(m-3);
			res=res+(z)calc(n-2,m-4)*(m-4)*(m-4);
			res=res+(z)calc(n-2,m-3)*2*(m-3)*(m-4);
			res=res+(z)calc(n-2,m-3)*(m-3);
			res=res+(z)calc(n-2,m-2)*(m-2)*(m-3);
			return res.x;
		}
		return -1;
	}
};
#ifdef memset0
int main(){
	freopen("1.in","r",stdin);
	int n,m,k; auto it=new KingdomAndCities();
	std::cin>>n>>m>>k;
	std::cout<<it->howMany(n,m,k)<<std::endl;
}
#endif