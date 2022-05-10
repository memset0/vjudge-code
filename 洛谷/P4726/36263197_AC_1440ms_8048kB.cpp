#include<bits/stdc++.h>
#define vec std::vector<z>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=1e5+10,mod=998244353;
int rev[N<<2];
struct z{
	int x;
	z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}w[N<<2];
inline z fpow(z a,int b){z s=1;for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}
inline vec operator+(vec a,const vec &b){
	a.resize(std::max(a.size(),b.size()));
	for(int i=0;i<b.size();i++)a[i]=a[i]+b[i]; return a;
}
inline vec operator-(vec a,const vec &b){
	a.resize(std::max(a.size(),b.size()));
	for(int i=0;i<b.size();i++)a[i]=a[i]-b[i]; return a;
}
int init(int n){
	int lim=1,k=0; while(lim<n)lim<<=1,++k;
	for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
	for(int len=1;len<lim;len<<=1){
		z wn=fpow(3,(mod-1)/(len<<1)); w[len]=1;
		for(int i=1;i<len;i++)w[i+len]=w[i+len-1]*wn;
	}return lim;
}
void dft(vec &a,int lim){
	a.resize(lim);
	for(int i=0;i<lim;i++)if(i<rev[i])std::swap(a[i],a[rev[i]]);
	for(int len=1;len<lim;len<<=1)
		for(int i=0;i<lim;i+=(len<<1))
			for(int j=0;j<len;j++){
				z x=a[i+j],y=a[i+j+len]*w[j+len];
				a[i+j]=x+y,a[i+j+len]=x-y;
			}
}
void idft(vec &a,int lim){
	dft(a,lim),std::reverse(&a[1],&a[lim]); z inv=fpow(lim,mod-2);
	for(int i=0;i<lim;i++)a[i]=a[i]*inv;
}
vec mul(vec a,vec b,int l=-1){
	int len=a.size()+b.size()-1,lim=init(len);
	// printf("mul %zu %zu %d\n",a.size(),b.size(),l);
	dft(a,lim),dft(b,lim);
	for(int i=0;i<lim;i++)a[i]=a[i]*b[i];
	return idft(a,lim),a.resize(~l?l:len),a;
}
vec inv(const vec &f,int len=-1){
	if((len=~len?len:f.size())==1)return {fpow(f[0],mod-2)};
	vec a(&f[0],&f[len]),b=inv(f,(len+1)>>1); int lim=init((len<<1)-1);
	dft(a,lim),dft(b,lim);
	for(int i=0;i<lim;i++)a[i]=b[i]*(2-a[i]*b[i]);
	return idft(a,lim),a.resize(len),a;
}
vec deri(vec f){for(int i=0;i<=(int)f.size()-2;i++)f[i]=f[i+1]*(i+1); return f.back()=0,f;}
vec inte(vec f){for(int i=(int)f.size()-1;i>=1;i--)f[i]=f[i-1]*fpow(i,mod-2); return f.front()=0,f;}
vec ln(const vec &f){return inte(mul(inv(f),deri(f),f.size()));}
vec exp(const vec &f,int len=-1){
	if((len=~len?len:f.size())==1)return {1};
	vec a(&f[0],&f[len]),b=exp(f,(len+1)>>1);
	return b.resize(len),mul(b,a+vec{1}-ln(b),len);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	int n; vec a;
	read(n),a.resize(n);
	for(int i=0;i<n;i++)read((int&)a[i]);
	a=exp(a);
	for(int i=0;i<n;i++)print((int&)a[i]," \n"[i+1==n]);
}