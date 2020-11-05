#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=2e5+10,mod=1e6+3;
int n;
struct z{
	int x;
	z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}a,b,c,ans,x[N],y[N],f[N],fac[N<<1],ifac[N<<1];
inline z C(int n,int m){return n<m?0:fac[n]*ifac[m]*ifac[n-m];}
inline z fpow(z a,int b){z s=1;for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}
inline z calc(int x,int y){return fpow(b,x)*fpow(a,y)*C(x+y,x);}
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
	for(int i=0;i<=n-2;i++)f[0]=f[0]+fpow(b,i);
	for(int i=1;i<=n-2;i++)f[i]=(f[i-1]-fpow(b,n-1)*C(i+n-2,n-2))*fpow(1-b,mod-2);
	for(int i=0;i<=n-2;i++)ans=ans+fpow(a,i)*f[i]*c;
	printf("%d\n",(int&)ans);
}//fadfadsdfadsfadfadfasdfasdfadfafd