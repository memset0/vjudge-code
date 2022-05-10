#include<bits/stdc++.h>
const int N=1e7+10,mod=998244353;
bool vis[N];
int n,m,k,cnt,pri[N];
struct z{
	int x;
	inline z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}s,p,ans,f[N],g[N],inv[N],pw[N];
inline z fpow(z a,int b){z s=1;for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}
z binom(int n,int m){
	z s=1;
	for(int i=1;i<=n;i++)s=s*i;
	for(int i=1;i<=m;i++)s=s*fpow(i,mod-2);
	for(int i=1;i<=n-m;i++)s=s*fpow(i,mod-2);
	return s;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	scanf("%d%d%d",&n,&m,&k);
	p=fpow(m,mod-2),g[1]=inv[0]=inv[1]=1;
	for(int i=2;i<=k;i++)inv[i]=(mod-mod/i)*inv[mod%i];
	for(int i=2;i<=k;i++){
		if(!vis[i]){g[i]=fpow(i,k),pri[++cnt]=k;}
		for(int j=1;j<=cnt&&(long long)i*pri[j]<=k;j++){
			vis[i*pri[j]]=1,g[i*pri[j]]=g[i]*g[pri[j]];
			if(i%pri[j]==0)break;
		}
	}
	if(n<=k){
		z s=1,a=1,b=fpow(1-p,n),t=fpow(1-p,mod-2);
		for(int i=1;i<=n;i++){
			s=s*(n-i+1)*inv[i],a=a*p,b=b*t;
			ans=ans+s*a*(i==n?1:b)*g[i];
		}
	}else{
		pw[0]=f[k]=s=1;
		for(int i=1;i<=k;i++)pw[i]=pw[i-1]*p;
		for(int i=k-1;i>=0;i--){
			s=s*(n-i-1)*inv[k-i];
			f[i]=(1-p)*f[i+1]+(k-i&1?0-pw[k-i]:pw[k-i])*s;
		}
		s=1;
		for(int i=0;i<=k;i++){
			if(i)s=s*(n-i+1)*inv[i];
			ans=ans+g[i]*s*pw[i]*f[i];
		}
	}
	printf("%d\n",(ans).x);
}