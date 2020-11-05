#include<bits/stdc++.h>
#define ll long long
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=1<<18,mod=998244353;
int n,s,inv_s,lim,a[N],f[N],g[N];
inline int mid(int x){return x&1?(x+mod)>>1:x>>1;}
inline int dec(int a,int b){return (a-=b)<0?a+mod:a;}
inline int inc(int a,int b){return (a+=b)>=mod?a-mod:a;}
inline int fpow(int a,int b){int s=1;for(;b;b>>=1,a=(ll)a*a%mod)if(b&1)s=(ll)s*a%mod;return s;}
void fwt(int *a,void foo(int&,int&)){
	for(int len=1;len<lim;len<<=1)
		for(int i=0;i<lim;i+=len<<1){
			for(int j=0;j<len;j++)foo(a[i+j],a[i+j+len]);
		}
}
void trans(int &a,int &b){int x=a;a=inc(a,b),b=dec(x,b);}
void i_trans(int &a,int &b){int x=a;a=mid(inc(a,b)),b=mid(dec(x,b));}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),lim=1<<n;
	for(int i=0;i<lim;i++)read(a[i]),s=inc(s,a[i]);
	inv_s=fpow(s,mod-2);
	for(int i=0;i<lim;i++)a[i]=(ll)a[i]*inv_s%mod,f[i]=lim-1;
	f[0]=mod-1,a[0]=dec(a[0],1);
	fwt(f,trans),fwt(a,trans);
	for(int i=0;i<lim;i++)g[i]=(ll)f[i]*fpow(a[i],mod-2)%mod;
	fwt(g,i_trans);
	// for(int i=0;i<lim;i++)print(g[i]," \n"[i==lim-1]);
	for(int i=lim-1;i>=0;i--)g[i]=dec(g[0],g[i]);
	for(int i=0;i<lim;i++)print(g[i],'\n');
}