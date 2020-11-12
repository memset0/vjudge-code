#include<bits/stdc++.h>
#define log(...) (void(0))
// #define log(...) fprintf(stderr,__VA_ARGS__)
const int S=1<<21; char ibuf[S],*iS,*iT;
#define getchar() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,S,stdin),(iS==iT?EOF:*iS++)):*iS++)
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
#ifdef local
const int N=1e3+10,mod=998244353;
#else
const int N=2.1e6+10,mod=998244353;
#endif
int n,q,ans,rev[N];
struct z {
	int x;
	z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}q0,qx,qy/*orz qy*/,qc,w[N],f[N],g[N],t1[N],t2[N],t3[N],t4[N],fac[N],ifac[N];
inline z fpow(z a,int b){z s=1;for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}
void initFac(int n){
	fac[0]=ifac[0]=ifac[1]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
	for(int i=2;i<=n;i++)ifac[i]=(mod-mod/i)*ifac[mod%i];
	for(int i=2;i<=n;i++)ifac[i]=ifac[i-1]*ifac[i];
}
void initPow(z c,int n,z *a,z *b){
	a[0]=b[0]=1;
	for(int i=1;i<n;i++)a[i]=a[i-1]*c;
	for(int i=1;i<n;i++)b[i]=b[i-1]*a[i-1];
}
int init(int n){
	static int wk=1; int k=-1,l=1; while(l<n)l<<=1,++k;
	for(int i=0;i<l;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<k);
	for(int &k=wk;k<l;k<<=1){
		z c=fpow(3,(mod-1)/k/2); w[k]=1;
		for(int i=1;i<k;i++)w[i+k]=w[i+k-1]*c;
	}return l;
}
void ntt(z *a,z *b,int l){
	for(int i=0;i<l;i++)b[rev[i]]=a[i];
	for(int k=1;k<l;k<<=1)
		for(int i=0;i<l;i+=(k<<1))
			for(int j=0;j<k;j++){
				z x=b[i+j],y=b[i+j+k]*w[j+k];
				b[i+j]=x+y,b[i+j+k]=x-y;
			}
}
void mul(z *a,z *b,z *c,int n,int m,bool fl=false){
	static z t[N];
	int l=init(n+m-1); z v=fpow(l,mod-2);
	if(fl){
		memset(a+n,0,(l-n)<<2);
		memset(b+m,0,(l-m)<<2);
	}
	ntt(a,c,l),ntt(b,t,l);
	for(int i=0;i<l;i++)t[i]=t[i]*c[i];
	std::reverse(t+1,t+l),ntt(t,c,l);
	for(int i=0;i<l;i++)c[i]=c[i]*v;
}
int main(){
#ifdef local
	freopen("1.in","r",stdin);
#endif
	read(n),read(q),initFac(std::max(n,q));
	for(int i=0;i<=n;i++)read((int&)f[i]);
	read((int&)q0),read((int&)qx),read((int&)qy),qc=(q0*(qx-1)+qy)*fpow(qx-1,mod-2);
	for(int i=0;i<=n;i++)log("%d%c",f[i]," \n"[i==n]);
	const auto move=[&](z *a,z c,z k,int n){
		log("\e[33mMOVE %d %d %d\e[0m\n",c,k,n);
		int i; z t;
		for(i=0,t=1;i<n;i++)t1[i]=a[i]*fac[i],t2[n-i-1]=ifac[i]*t,t=t*c;
		mul(t1,t2,t3,n,n);
		for(i=0,t=1;i<n;i++)a[i]=t3[n-1+i]*ifac[i]*t,t=t*k;
	};
	move(f,q0-qc,qc,n+1);
	for(int i=0;i<=n;i++)log("%d%c",f[i]," \n"[i==n]);
	const auto czt=[&](z *a,z *b,z c,int n,int q){
		log("\e[33mCZT %d %d %d\e[0m\n",c,n,q);
		initPow(c,n+q,t3,t1);
		std::reverse(t1,t1+n+q);
		initPow(fpow(c,mod-2),std::max(n,q),t3,t4);
		for(int i=0;i<n;i++)t2[i]=a[i]*t4[i];
		mul(t1,t2,t3,n+q,n,1);
		for(int i=0;i<q;i++)b[i]=t3[n+q-1-i]*t4[i];
	};
	czt(f,g,qx,n+1,q+1);
	for(int i=1;i<=q;i++)ans^=g[i].x;
	printf("%d\n",ans);
}