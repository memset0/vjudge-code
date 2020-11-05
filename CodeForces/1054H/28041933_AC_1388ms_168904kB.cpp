/*
垃圾洛谷何时支持c++17？
#include<bits/stdc++.h>
const int S=1<<21; char ibuf[S],*iS,*iT,obuf[S],*oS=obuf,*oT=oS+S-1;
#define getchar() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,S,stdin),(iS==iT?EOF:*iS++)):*iS++)
#define i64 long long
#define i128 __int128
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=1<<21,p=490019;
const long long mod=4179340454199820289;
int n,m,c,lim=1,ans,k,a[N],b[N],g[N],f[N],rev[N];
long long F[N],G[N],w[N];
inline int fpow(int a,int b,int p){int s=1;for(;b;b>>=1,a=(i64)a*a%p)if(b&1)s=(i64)s*a%p;return s;}
inline i64 fpow(i64 a,i64 b,i64 p){i64 s=1;for(;b;b>>=1,a=(i128)a*a%p)if(b&1)s=(i128)s*a%p;return s;}
void DFT(i64 *a){
	for(int i=0;i<lim;i++)if(i<rev[i])std::swap(a[i],a[rev[i]]);
	for(int len=1;len<lim;len<<=1)
		for(int i=0;i<lim;i+=(len<<1))
			for(int j=0;j<len;j++){
				i64 x=a[i+j],y=(i128)a[i+j+len]*w[j+len]%mod;
				a[i+j]=x+y,a[i+j+len]=x-y;
				if(a[i+j]>=mod)a[i+j]-=mod;
				if(a[i+j+len]<0)a[i+j+len]+=mod;
			}	
}
int main(){
#ifdef memset0
	// freopen("1.in","r",stdin);
	freopen("comp/data.in","r",stdin);
#endif
	read(n),read(m),read(c);
	for(int i=0;i<n;i++)read(a[i]);
	for(int i=0;i<m;i++)read(b[i]);
	for(int i=0;i<m;i++)F[fpow(i,3,p-1)]+=b[i];
	f[0]=F[0],g[0]=1,g[1]=2;
	for(int i=1;i<p-1;i++)g[i]=(i64)g[i-1]*g[1]%p;
	for(int i=0;i<p-1;i++)F[i]=F[i]%p*g[(p-1-(i64)i*(i-1)/2%(p-1))%(p-1)]%p;
	for(int i=0;i<(p<<1)-1;i++)G[i]=g[(i64)i*(i-1)/2%(p-1)];
	std::reverse(F,F+p-1);
	while(lim<=(p*3-3))lim<<=1,++k;
	for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
	for(int len=1;len<lim;len<<=1){
		i64 wn=fpow(3ll,(mod-1)/(len<<1),mod); w[len]=1;
		for(int i=1;i<len;i++)w[i+len]=(i128)w[i+len-1]*wn%mod;
	}
	DFT(F),DFT(G);
	for(int i=0;i<lim;i++)F[i]=(i128)F[i]*G[i]%mod;
	std::reverse(F+1,F+lim),DFT(F);
	i64 invlim=fpow((i64)lim,mod-2,mod);
	for(int i=0;i<lim;i++)F[i]=(i128)F[i]*invlim%mod;
	for(int i=0;i<p-1;i++)f[g[i]]=F[i+p-2]%p*g[(p-1-(i64)i*(i-1)/2%(p-1))%(p-1)]%p;
	for(int i=0;i<n;i++)ans=(ans+(i64)a[i]*f[fpow(fpow(c,i,p),i,p)])%p;
	printf("%d\n",ans);
}
*/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<vector>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
using namespace std;
typedef int ll;
typedef long long int li;
typedef long double db;
const ll MAXN=1e5+51,G499=7,G491=2,MOD=490019;
const db PI=acos(-1.0);
struct Complex{
	db re,im;
	Complex(db x=0,db y=0)
	{
		this->re=x,this->im=y;
	}
};
Complex f0,f1,g0,g1;
Complex omgs[1025],invo[1025],tmp[1024];
Complex f[2][1024][1024],g[2][1024][1024];
vector<ll>xx,yy;
ll n,m,c,kk=250,kk2=399,cur,p,q,res,h,xp;
li kd,qq;
ll rev[1024],x[MAXN],y[MAXN];
ll lg499[500],lg491[500],pw499[500],pw491[500];
li fx[2][1024][1024],fy[2][1024][1024];
li pw[490021];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline ll CRT(ll x,ll y,ll z)
{
	ll r=kk*(y-x);
	r=((r%499)+499)%499;
	ll p=2*r+x,r2=kk2*(z-p);
	r2=((r2%491)+491)%491;
	return r2*998+p;
}
inline Complex operator +(Complex x,Complex y)
{
	return Complex(x.re+y.re,x.im+y.im);
}
inline Complex operator -(Complex x,Complex y)
{
	return Complex(x.re-y.re,x.im-y.im);
}
inline Complex operator *(Complex x,Complex y)
{
	return Complex(x.re*y.re-x.im*y.im,x.re*y.im+x.im*y.re);
}
inline Complex operator /(Complex x,db y)
{
	return Complex(x.re/y,x.im/y);
}
inline void FFT(Complex *cp,ll cnt,ll inv)
{
	ll cur=0;
	Complex res,omg;
	for(register int i=0;i<cnt;i++)
	{
		if(i<rev[i])
		{
			swap(cp[i],cp[rev[i]]);
		}
	}
	for(register int i=2;i<=cnt;i<<=1)
	{
		cur=i>>1,res=inv==1?omgs[i]:invo[i];
		for(register Complex *p=cp;p!=cp+cnt;p+=i)
		{
			omg=Complex(1,0);
			for(register int j=0;j<cur;j++)
			{
				Complex t=omg*p[j+cur],t2=p[j];
				p[j+cur]=t2-t,p[j]=t+t2;
				omg=omg*res;
			}
		}
	}
	if(inv==-1)
	{
		for(register int i=0;i<cnt;i++)
		{
			cp[i]=cp[i]/cnt;
		}
	}
}
inline void FFT2D(ll n,ll m,Complex cp[][1024],ll inv)
{
	for(register int i=0;i<m;i++)
	{
		for(register int j=0;j<n;j++)
		{
			tmp[j]=cp[j][i];
		}
		FFT(tmp,n,inv);
		for(register int j=0;j<n;j++)
		{
			cp[j][i]=tmp[j];
		}
	}
	for(register int i=0;i<n;i++)
	{
		FFT(cp[i],m,inv);
	}	
}
int main()
{
	n=read(),m=read(),c=read(),cur=1;
	for(register int i=0;i<490;i++)
	{
		lg491[cur]=i,pw491[i]=cur,cur=(cur*G491)%491;
	}
	cur=1;
	for(register int i=0;i<498;i++)
	{
		lg499[cur]=i,pw499[i]=cur,cur=(cur*G499)%499;
	}
	for(register int i=0;i<1024;i++)
	{
		rev[i]=(rev[i>>1]>>1)|((i&1)<<9);
	}
	for(register int i=0;i<n;i++)
	{
		x[i]=read();
		if(i%499&&i%491)
		{
			fx[i&1][lg499[(li)i*i%499]][lg491[(li)i*i%491]]+=x[i];
			continue;
		}
		xx.push_back(i);
	}
	for(register int i=0;i<m;i++)
	{
		y[i]=read();
		if(i%499&&i%491)
		{
			fy[i&1][lg499[(li)i*i*i%499]][lg491[(li)i*i*i%491]]+=y[i];
			continue;
		}
		yy.push_back(i);
	}
	for(register int i=0;i<499;i++)
	{
		for(register int j=0;j<491;j++)
		{
			f[0][i][j].re=fx[0][i][j]%MOD,f[1][i][j].re=fx[1][i][j]%MOD;
			g[0][i][j].re=fy[0][i][j]%MOD,g[1][i][j].re=fy[1][i][j]%MOD;
		}	
	}
	for(register int i=1;i<=1024;i<<=1)
	{
		omgs[i]=Complex(cos(2*PI/i),sin(2*PI/i));
		invo[i]=Complex(cos(2*PI/i),-sin(2*PI/i));
	}
	FFT2D(1024,1024,f[0],1),FFT2D(1024,1024,f[1],1);
	FFT2D(1024,1024,g[0],1),FFT2D(1024,1024,g[1],1);
	for(register int i=0;i<1024;i++)
	{
		for(register int j=0;j<1024;j++)
		{
			f0=f[0][i][j],f1=f[1][i][j],g0=g[0][i][j],g1=g[1][i][j];
			f[0][i][j]=(f0+f1)*(g0+g1)-f1*g1,f[1][i][j]=f1*g1;
		}
	}
	FFT2D(1024,1024,f[0],-1),FFT2D(1024,1024,f[1],-1),pw[0]=1;
	for(register int i=1;i<MOD;i++)
	{
		pw[i]=(li)pw[i-1]*c%MOD;
	}
	for(register int i=0;i<1024;i++)
	{
		for(register int j=0;j<1024;j++)
		{
			for(register int k=0;k<2;k++)
			{
				h=((li)(f[k][i][j].re+0.5))%MOD;
				xp=CRT(k,pw499[i%498],pw491[j%490]);
				res=(res+h*pw[xp])%MOD;
			}
		}
	}
	for(register int i=0;i<xx.size();i++)
	{
		for(register int j=0;j<m;j++)
		{
			kd=(li)xx[i]*xx[i]*j%(MOD-1)*j*j%(MOD-1);
			qq=x[xx[i]]*y[j]*pw[kd]%MOD;
			res=(li)(res+qq)%MOD;
		}
	}
	for(register int i=0;i<yy.size();i++)
	{
		for(register int j=0;j<n;j++)
		{
			if(!(j%499&&j%491))
			{
				continue;
			}
			kd=(li)yy[i]*yy[i]*yy[i]%(MOD-1)*j*j%(MOD-1);
			res=(res+(li)x[j]*y[yy[i]]*pw[kd])%MOD;
		}
	}
	printf("%d\n",res);
}