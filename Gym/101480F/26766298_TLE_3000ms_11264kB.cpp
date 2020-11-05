#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=2e5+10,mod=1e6+3;
int n,f[N],g[N],h[N];
struct z{
	int x;
	z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}a,b,c,ans,x[N],y[N],fac[N<<1],ifac[N<<1];
inline z C(int n,int m){return n<m?0:fac[n]*ifac[m]*ifac[n-m];}
inline z fpow(z a,int b){z s=1;for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}
inline z calc(int x,int y){return fpow(b,x)*fpow(a,y)*C(x+y,x);}
void mul(int *f,int *g,int *h,int n){
	int m=(n>>3)<<3;
	for(int i=0;i<m;i++){
		for(int j=0;j<m;j+=8){
			h[i+j]=(h[i+j]+(long long)f[i]*g[j])%mod;
			h[i+j+1]=(h[i+j+1]+(long long)f[i]*g[j+1])%mod;
			h[i+j+2]=(h[i+j+2]+(long long)f[i]*g[j+2])%mod;
			h[i+j+3]=(h[i+j+3]+(long long)f[i]*g[j+3])%mod;
			h[i+j+4]=(h[i+j+4]+(long long)f[i]*g[j+4])%mod;
			h[i+j+5]=(h[i+j+5]+(long long)f[i]*g[j+5])%mod;
			h[i+j+6]=(h[i+j+6]+(long long)f[i]*g[j+6])%mod;
			h[i+j+7]=(h[i+j+7]+(long long)f[i]*g[j+7])%mod;
		}
	}
	for(int i=0;i<m;i++)
		for(int j=m;j<n;j++)
			h[i+j]=(h[i+j]+(long long)f[i]*g[j])%mod;
	for(int i=m;i<n;i++)
		for(int j=0;j<m;j++)
			h[i+j]=(h[i+j]+(long long)f[i]*g[j])%mod;
	for(int i=m;i<n;i++)
		for(int j=m;j<n;j++)
			h[i+j]=(h[i+j]+(long long)f[i]*g[j])%mod;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read((int&)a),read((int&)b),read((int&)c);
	fac[0]=ifac[0]=ifac[1]=1;
	for(int i=2;i<=(n<<1);i++)ifac[i]=(mod-mod/i)*ifac[mod%i];
	for(int i=1;i<=(n<<1);i++)fac[i]=fac[i-1]*i,ifac[i]=ifac[i-1]*ifac[i];
	for(int i=1;i<=n;i++)read((int&)x[i]);
	for(int i=1;i<=n;i++)read((int&)y[i]);
	for(int i=2;i<=n;i++)ans=ans+x[i]*a*calc(n-i,n-2);
	for(int i=2;i<=n;i++)ans=ans+y[i]*b*calc(n-2,n-i);
	for(int i=0;i<=n-2;i++)f[i]=(fpow(a,i)*ifac[i]).x;
	for(int i=0;i<=n-2;i++)g[i]=(fpow(b,i)*ifac[i]).x;
	mul(f,g,h,n-1);
	for(int i=0;i<=n*2-4;i++)ans=ans+h[i]*fac[i]*c;
	printf("%d\n",(int&)ans);
}