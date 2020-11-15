#include<bits/stdc++.h>
#define poly std::vector<z>
// #define log(...) (void(0))
#define log(...) fprintf(stderr,__VA_ARGS__)
#define debug log("\33[2mPassing [%s] in LINE %d\33[0m\n",__FUNCTION__,__LINE__);
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=1e5+10,mod=998244353;
int n,l,lim,m[N];
struct z {
	int x;
	z(int x=0):x(x){}
	inline int half(){return x&1?(x+mod)>>1:x>>1;}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}a[N],b[N],c[N],d[N],fac[N],inv[N],ifac[N],t1[N];
inline z fpow(z a,int b){z s=1;for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}
namespace Polynomial{
	int rev[N<<2]; z w[N<<2];
	int polyInit(int l){
		int lim=1,k=0; while(lim<l)lim<<=1,++k;
		for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
		static int len=1;
		for(;len<lim;len<<=1){
			z wn=fpow(3,(mod-1)/(len<<1)); w[len]=1;
			for(int i=1;i<len;i++)w[i+len]=w[i+len-1]*wn;
		}return lim;
	}
	void dft(poly &a,int lim){ 
		a.resize(lim);
		for(int i=0;i<lim;i++)if(i<rev[i])std::swap(a[i],a[rev[i]]);
		for(int len=1;len<lim;len<<=1)
			for(int i=0;i<lim;i+=(len<<1))
				for(int j=0;j<len;j++){
					z x=a[i+j],y=a[i+j+len]*w[j+len];
					a[i+j]=x+y,a[i+j+len]=x-y;
				}
	}
	void idft(poly &a,int lim){
		dft(a,lim),std::reverse(&a[1],&a[lim]); z inv=fpow(lim,mod-2);
		for(int i=0;i<lim;i++)a[i]=a[i]*inv;
	}
	poly polyInc(poly a,const poly &b){
		a.resize(std::max(a.size(),b.size()));
		for(int i=0;i<b.size();i++)a[i]=a[i]+b[i]; return a;
	}
	poly polyDec(poly a,const poly &b){
		a.resize(std::max(a.size(),b.size()));
		for(int i=0;i<b.size();i++)a[i]=a[i]-b[i]; return a;
	}
	poly polyMul(poly a,poly b){
		int lim=polyInit(a.size()+b.size()-1);
		dft(a,lim),dft(b,lim);
		for(int i=0;i<lim;i++)a[i]=a[i]*b[i];
		idft(a,lim),a.resize(l); return a;
	}
	poly polyInv(poly f,int len=-1){
		if((len=~len?len:f.size())==1)return {fpow(f[0],mod-2)};
		poly a(&f[0],&f[len]),b=polyInv(f,(len+1)>>1);
		int lim=polyInit((len<<1)-1);
		dft(a,lim),dft(b,lim);
		for(int i=0;i<lim;i++)a[i]=b[i]*(2-a[i]*b[i]);
		idft(a,lim),a.resize(len); return a;
	}
	poly polyDer(poly f){for(int i=0;i<=f.size()-2;i++)f[i]=f[i+1]*(i+1); *--f.end()=0; return f;}
	poly polyInt(poly f){for(int i=f.size()-1;i>=1;i--)f[i]=f[i-1]*inv[i]; *f.begin()=0; return f;}
	poly polyLn(poly f){return polyInt(polyMul(polyInv(f),polyDer(f)));}
}
using namespace Polynomial;
poly A,B,C,D,E,F,G,H;
struct info{
	z n,a,b,c;
	inline z dump(){return a+b+c;}
	inline void load(int x){n=G[x]*fac[x]*x,a=C[x]*fac[x],b=D[x]*fac[x],c=G[x-1]*fac[x];}
	friend inline info operator^(const info &a,const info &b){
		static info s;
		s.n=a.n*b.n;
		s.a=2*a.a*b.a+a.a*b.b+a.b*b.a;
		s.b=a.b*b.b;
		s.c=a.c*b.c+a.c*(b.n-b.c)+b.c*(a.n-a.c);
		return s;
	}
}ans,tmp;
int main(){
#ifdef local
	freopen("1.in","r",stdin);
#endif
	read(n);
	for(int i=1;i<=n;i++)read(m[i]),l=std::max(l,m[i]+1);
	fac[0]=ifac[0]=inv[0]=inv[1]=1;
	for(int i=1;i<=l;i++)fac[i]=fac[i-1]*i;
	for(int i=2;i<=l;i++)inv[i]=(mod-mod/i)*inv[mod%i];
	for(int i=1;i<=l;i++)ifac[i]=ifac[i-1]*inv[i];
	G.resize(l),B.resize(l);
	for(int i=0;i<l;i++)t1[i]=fpow(2,(long long)i*(i-1)/2%(mod-1));
	for(int i=0;i<l;i++)G[i]=t1[i]*ifac[i];
	for(int i=0;i<l;i++)B[i]=ifac[i]*fpow(t1[i],mod-2);
	B=polyMul(B,B),B.resize(l);
	for(int i=0;i<l;i++)B[i]=B[i]*t1[i];
	F=polyLn(G),H=G,F[1]=0,A=polyLn(B),A[1]=0;
	for(int i=0;i<l;i++)A[i]=A[i].half();
	C=polyMul(G,A),C.resize(l),E=polyMul(G,F),E.resize(l),D=polyDec(E,C);
	ans.load(m[1]);
	for(int i=2;i<=n;i++)ans=ans^(tmp.load(m[i]),tmp);
	printf("%d\n",ans.dump().x);
}