#include<bits/stdc++.h>
#define log(...) fprintf(stderr,__VA_ARGS__)
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
const int N=2e5+10,mod=998244353;
int n,m,k,a[N],b[N],rev[N<<2];
struct z{
	int x;
	inline z():x(0){}
	inline z(int x):x(x){}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}ans,len[N],fac[N],ifac[N],w[N<<2],S[N];
inline z C(int n,int m){return n<m?0:fac[n]*ifac[m]*ifac[n-m];}
inline z fpow(z a,int b){z s=1;for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}
struct vec:std::vector<z>{
	using std::vector<z>::vector;
	inline void print(){for(int i=0;i<size();i++)::print(at(i).x,' ');putchar('\n');}
};
inline vec resize(vec a,int n){a.resize(n); return a;}
void initfac(int n){
	fac[0]=fac[1]=ifac[0]=ifac[1]=1;
	for(int i=2;i<=n;i++)fac[i]=fac[i-1]*i;
	for(int i=2;i<=n;i++)ifac[i]=(mod-mod/i)*ifac[mod%i];
	for(int i=2;i<=n;i++)ifac[i]=ifac[i-1]*ifac[i];
}
int init(int n){
	int lim=1,k=0; while(lim<n)lim<<=1,++k;
	for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
	static int len=1;for(;len<lim;len<<=1){
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
inline vec mul(vec a,vec b,int l){
	if(a.size()<10||b.size()<10){
		vec c(a.size()+b.size()-1);
		for(int i=0;i<a.size();i++)
			for(int j=0;j<b.size();j++)
				c[i+j]=c[i+j]+a[i]*b[j];
		return c.resize(l),c;
	}
	int len=a.size()+b.size()-1,lim=init(len);
	dft(a,lim),dft(b,lim);
	for(int i=0;i<lim;i++)a[i]=a[i]*b[i];
	return idft(a,lim),a.resize(l),a;
}
inline vec operator*(const vec &a,const vec &b){return mul(a,b,a.size()+b.size()-1);}
inline vec operator+(vec a,const vec &b){
	a.resize(std::max(a.size(),b.size()));
	for(int i=0;i<b.size();i++)a[i]=a[i]+b[i]; return a;
}
inline vec operator-(vec a,const vec &b){
	a.resize(std::max(a.size(),b.size()));
	for(int i=0;i<b.size();i++)a[i]=a[i]-b[i]; return a;
}
vec inv(const vec &f,int len=-1){
	if((len=~len?len:f.size())==1)return {fpow(f[0],mod-2)};
	vec a(&f[0],&f[len]),b=inv(f,(len+1)>>1);
	int lim=init((len<<1)-1);
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
vec fpow(vec a,int b){
	int n=a.size(); vec s;
	for(int c=0;c<n;c++)if(a[c].x){
		int l=n-c*b;
		if(l<=0)return s.resize(n),s;
		for(int i=0;i<l;i++)a[i]=a[i+c];
		a.resize(l);
		a=ln(a);
		for(int i=0;i<l;i++)a[i]=a[i]*b;
		a=exp(a),s.resize(c*b);
		s.insert(s.end(),a.begin(),a.end());
		return s;
	}
	return a;
}
vec complex(const vec &g){ //F(G(x))
	vec s,c={1};
	for(int i=1;i<=k;i++)c=mul(c,g,g.size()),s=s+c;
	return s;
}
vec complex_inv(int len){ //G^{-1}(F(x))
	if(len==1)return {0};
	vec g=resize(complex_inv((len+1)>>1),len),gk=fpow(g,k),gk1=mul(gk,g,len);
	vec res=g-mul(mul(g-gk1-vec{0,1}*(vec{1}-g),vec{1}-g,len),inv(vec{1}-vec{k+1}*gk+vec{k}*gk1),len);
	return res;
}
inline vec sol(int n){ //	n+1个球，分m组，每组1~k个。
	vec bf(n+1);
	for(int m=1;m<=n+1;m++)
    for(int i=0,t;i<=m;i++){
			t=n-i*k;
			if(t<m-1)break;
			if(i&1){
				bf[n+1-m]=bf[n+1-m]-C(m,i)*fac[t]*ifac[m-1]*ifac[t-m+1];
			}else{
				bf[n+1-m]=bf[n+1-m]+C(m,i)*fac[t]*ifac[m-1]*ifac[t-m+1];
			}
    }
	return bf;
}
std::pair<vec,vec> solve(int l,int r){
	if(l==r){
		int n=b[l];
		vec F(n+1),G=sol(n);
		for(int i=0;i<=n;i++){
			F[i]=fac[n]*ifac[n-i]-G[i]*fac[i]-(i?S[i-1]:0)*ifac[n-i];
			S[i]=(i?S[i-1]:0)+F[i]*fac[n-i];
		}
		for(int i=0;i<n;i++)F[i]=F[i+1]*ifac[i];
		return F.pop_back(),std::pair<vec,vec>{F,G};
	}
	int mid=(l+r)>>1;
	auto L=solve(l,(l+r)>>1),R=solve(((l+r)>>1)+1,r);
	return {L.first*R.second+L.second*R.first,L.second*R.second};
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(k),initfac(n+5);
	for(int i=1;i<=n;i++)read(a[i]);
	std::sort(a+1,a+n+1);
	for(int i=1,j;i<=n;i=j+1){
		for(j=i;j<n&&a[j+1]==a[i]+j-i+1;j++);
		b[++m]=j-i+1;
	}
	auto res=solve(1,m);
	for(int i=1;i<=n;i++){
		len[i]=len[i-1]+n*fpow(n-i+1,mod-2);
		ans=ans+res.first[i-1]*fac[i-1]*fac[n-i]*len[i];
	}
	print((ans*ifac[n]).x,'\n');
	fprintf(stderr,"clock = %.2lf\n",clock()/double(CLOCKS_PER_SEC));
}