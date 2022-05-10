#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=2e5+10,mod=998244353;
int n,m,R[N<<2];
struct z {
	int x;
	z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}W[N<<2],fac[N],ifac[N],inv[N];
inline z fpow(z a,int b){z s(1);for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}
struct poly:std::vector<z>{
	using std::vector<z>::vector;
	inline void in(){for(size_t i=0;i<size();i++)read((int&)this->operator[](i));}
	inline void out()const{for(size_t i=0;i<size();i++)print(this->operator[](i).x," \n"[i+1==size()]);}
}a,b;
void initfac(int n){
	fac[0]=fac[1]=ifac[0]=ifac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<=n;i++)fac[i]=fac[i-1]*i;
	for(int i=2;i<=n;i++)inv[i]=inv[mod%i]*(mod-mod/i);
	for(int i=2;i<=n;i++)ifac[i]=ifac[i-1]*inv[i];
}
int initdft(int len){
	int lim=1,k=0;while(lim<=len)lim<<=1,++k;
	for(int i=0;i<lim;i++)R[i]=(R[i>>1]>>1)|((i&1)<<(k-1));
	static int slen=1;for(int len=slen;len<lim;len<<=1){
		z w=fpow(3,(mod-1)/(len<<1)); W[len]=1;
		for(int i=1;i<len;i++)W[i+len]=W[i+len-1]*w;
	}return lim;
}
void dft(poly &a,int lim){
	a.resize(lim);
	for(int i=0;i<lim;i++)if(i<R[i])std::swap(a[i],a[R[i]]);
	for(int len=1;len<lim;len<<=1)for(int i=0;i<lim;i+=(len<<1))for(int j=0;j<len;j++)
		{z x=a[i+j],y=a[i+j+len]*W[j+len];a[i+j]=x+y,a[i+j+len]=x-y;}
}
void idft(poly &a,int lim){
	std::reverse(&a[1],&a[lim]),dft(a,lim);z inv=fpow(lim,mod-2);
	for(int i=0;i<lim;i++)a[i]=a[i]*inv;
}
poly polyMul(poly f,poly g,int len=-1){
	int l=f.size()+g.size()-1,lim=initdft(l);len=~len?len:l;
	dft(f,lim),dft(g,lim);
	for(int i=0;i<lim;i++)f[i]=f[i]*g[i];
	idft(f,lim);return f.resize(len),f;
}
poly polyInv(const poly &f,int len=-1){
	if((len=~len?len:f.size())==1)return poly{fpow(f[0],mod-2)};
	poly a=polyInv(f,(len+1)>>1),b(&f[0],&f[len]);int lim=initdft((len<<1)-1);
	dft(a,lim),dft(b,lim);
	for(int i=0;i<lim;i++)a[i]=a[i]*(2-a[i]*b[i]);
	idft(a,lim);
	return a.resize(len),a;
}
poly polyInt(poly f){for(int i=f.size()-1;i;i--)f[i]=f[i-1]*inv[i];return f[0]=0,f;}
poly polyDer(poly f){for(int i=0;i<f.size()-1;i++)f[i]=f[i+1]*(i+1);return f[f.size()-1]=0,f;}
poly polyLn(poly f,int len=-1){if(~len)f.resize(len);return polyInt(polyMul(polyDer(f),polyInv(f),f.size()));}
poly polyExp(const poly &f,int len=-1){
	if((len=~len?len:f.size())==1)return poly{1};
	poly a=polyExp(f,(len+1)>>1),b=polyLn(a,len);
	for(int i=0;i<len;i++)b[i]=0-b[i];b[0]=b[0]+1;
	for(int i=0;i<len;i++)b[i]=b[i]+f[i];return polyMul(a,b,len);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),initfac(n),a.resize(n);
	a.in(),polyExp(a).out();
}