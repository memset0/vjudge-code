#include<bits/stdc++.h>
using namespace std;
const int N=1e3+9,mod=998244353;
int n,g[N],r[N],e[N];
struct mat:array<array<int,3>,3>{
};
inline mat operator*(const mat &a,const mat &b){
	mat c;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++){
			c[i][j]=0;
		}
	for(int i=0;i<3;i++)
		for(int k=0;k<3;k++)
			for(int j=0;j<3;j++){
				c[i][j]=(c[i][j]+(long long)a[i][k]*b[k][j])%mod;
			}
	return c;
}
inline mat power(mat a,int b){
	mat s;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			s[i][j]=i==j;
	for(;b;b>>=1,a=a*a)
		if(b&1)s=s*a;
	return s;
}
int main(){
#ifdef memset0
	freopen("F.in","r",stdin);
#else
	freopen("figure.in","r",stdin);
	freopen("figure.out","w",stdout);
#endif
	mat trs;
	trs[0][0]=1;
	trs[0][1]=1;
	trs[0][2]=1;
	trs[1][0]=1;
	trs[1][1]=2;
	trs[1][2]=2;
	trs[2][0]=mod-1;
	trs[2][1]=1;
	trs[2][2]=2;
	while(cin>>n,n){
		mat ans;
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++){
				ans[i][j]=0;
			}
		ans[0][0]=1;
		ans[1][0]=1;
		ans=power(trs,n-1)*ans;
		// cerr<<"! n="<<n<<endl;
		cout<<ans[0][0]<<endl;
		// for(int i=0;i<3;i++)
		// 	for(int j=0;j<3;j++)
		// 		cerr<<ans[i][j]<<" \n"[j==2];
		// cout<<ans[0][0]<<'\n';
	}
	// cin>>n;
	// for(int i=0;i<=n;i++)++g[i];
	// for(int i=0;i<=n;i++){
	// 	for(int j=0;i+j+1<=n;j++){
	// 		(g[i+j+1]+=r[i])%=mod;
	// 		(g[i+j+1]+=e[i])%=mod;
	// 		(r[i+j+1]+=2ll*e[i]*power(2,j)%mod)%=mod;
	// 		(r[i+j+1]+=1ll*g[i]*power(2,j)%mod)%=mod;
	// 		for(int k=0;i+j+k+2<=n;k++){
	// 			(e[i+j+k+2]+=r[i])%=mod;
	// 			(e[i+j+k+2]+=2ll*e[i]%mod)%=mod;
	// 		}
	// 	}
	// }
	// for(int i=0;i<=n;i++){
	// 	fprintf(stderr,"i=%d g=%d r=%d e=%d\n",i,g[i],r[i],e[i]);
	// }
}