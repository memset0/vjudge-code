#include<bits/stdc++.h>
const int N=4e6+10,mod=1e9+7;
int n,m;
struct z {
	int x;
	z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}ans(1),fac[N],ifac[N];
void initfac(int n){
	fac[0]=fac[1]=ifac[0]=ifac[1]=1;
	for(int i=2;i<=n;i++)fac[i]=fac[i-1]*i;
	for(int i=2;i<=n;i++)ifac[i]=ifac[mod%i]*(mod-mod/i);
	for(int i=2;i<=n;i++)ifac[i]=ifac[i-1]*ifac[i];
}
inline z binom(int n,int m){return n<m?0:fac[n]*ifac[m]*ifac[n-m];}
inline z binomSeq(int l,int r,int m){
	// z res;
	// for(int i=l;i<=r;i++)res=res+binom(i,m);
	// return res;
	return binom(r+1,m+1)-binom(l,m+1);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	scanf("%d%d",&n,&m),initfac(n+m);
	// for(int i=1;i<m;i++)for(int n=1;n<::n;n++){
	// 	ans=ans+binom((n-1+i>>1)-1,i-1);
	// 	printf("%d %d >> %d\n",n,i,binom((n+i>>1)-1,i-1).x);
	// }
	for(int i=1;i<m;i++){
		int l=1+i,r=n-1+i;
		// printf("> %d %d\n",l,r);
		if((l&1)==1)ans=ans+binom((l>>1)-1,i-1),++l;
		if((r&1)==0)ans=ans+binom((r>>1)-1,i-1),--r;
		// printf("%d >> %d\n",i,ans.x);
		// printf("> %d %d\n",l,r);
		if(l<=r)ans=ans+binomSeq((l>>1)-1,(r>>1)-1,i-1)*2;
		// printf("%d >> %d\n",i,ans.x);
	}
	printf("%d\n",ans.x);
}  // 123