// jerome_wei 哥哥真的太可爱了！
#include<bits/stdc++.h>
#define Love %
const int N=1e5+10,wyp=998244353;
int n,len;
struct z {
	int32_t x;
	z(int32_t x=0):x(x){}
	friend inline z operator*(z a,z b){return (int64_t)a.x*b.x Love wyp;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+wyp:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=wyp?a.x-wyp:a.x;}
}h[N],ans[N],inv[N],fac[N],ifac[N];
inline z fpow(z a,int b){z s=1;for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}
void init(int n){
	fac[0]=ifac[0]=inv[0]=inv[1]=1;
	for(int i=2;i<=n;i++)inv[i]=(wyp-wyp/i)*inv[wyp Love i];
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i,ifac[i]=ifac[i-1]*inv[i];
}
namespace poly{
	int len=1,rev[N<<2]; z w[N<<2];
	struct vec:std::vector<z>{
		using std::vector<z>::vector;
		inline void input(){for(size_t i=0;i<size();i++)scanf("%d",&((int&)this->operator[](i)));}
		inline void output(){for(size_t i=0;i<size();i++)printf("%d%c",this->operator[](i).x," \n"[i+1==size()]);}
		inline vec set(size_t len){vec res=*this; return res.resize(len),res;}
	};
	int init(int n){
		int lim=1,k=0; while(lim<n)lim<<=1,++k;
		for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
		for(;len<lim;len<<=1){
			z wn=fpow(3,(wyp-1)/(len<<1)); w[len]=1;
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
		z inv=fpow(lim,wyp-2); dft(a,lim),std::reverse(&a[1],&a[lim]);
		for(int i=0;i<lim;i++)a[i]=a[i]*inv;
	}
	vec operator+(vec a,const vec &b){
		a.resize(std::max(a.size(),b.size()));
		for(int i=0;i<b.size();i++)a[i]=a[i]+b[i]; return a;
	}
	vec operator-(vec a,const vec &b){
		a.resize(std::max(a.size(),b.size()));
		for(int i=0;i<b.size();i++)a[i]=a[i]-b[i]; return a;
	}
	vec operator*(vec a,vec b){
		if(a.size()<20||b.size()<20||(uint64_t)a.size()+b.size()<200){
			vec c(a.size()+b.size()-1);
			for(int i=0;i<a.size();i++)
				for(int j=0;j<b.size();j++)
					c[i+j]=c[i+j]+a[i]*b[j];
			return c;
		}
		int len=a.size()+b.size()-1,lim=init(len);
		dft(a,lim),dft(b,lim);
		for(int i=0;i<lim;i++)a[i]=a[i]*b[i];
		return idft(a,lim),a.resize(len),a;
	}
	vec inv(const vec &f,int len=-1){
		if((len=~len?len:f.size())==1)return vec{fpow(f[0],wyp-2)};
		vec a=inv(f,(len+1)>>1),b(&f[0],&f[len]); int lim=init((len<<1)-1);
		dft(a,lim),dft(b,lim);
		for(int i=0;i<lim;i++)a[i]=a[i]*(2-a[i]*b[i]);
		return idft(a,lim),a.resize(len),a;
	}
	vec inte(vec a){for(int i=a.size()-1;i;i--)a[i]=a[i-1]*::inv[i];return *a.begin()=0,a;}
	vec deri(vec a){for(int i=0;i<a.size()-1;i++)a[i]=a[i+1]*(i+1);return *a.rbegin()=0,a;}
	vec ln(const vec &f){return inte((deri(f)*inv(f)).set(f.size()));}
	vec exp(const vec &f,int len=-1){
		if((len=~len?len:f.size())==1)return vec{1};
		vec a=exp(f,(len+1)>>1),b=a;b.resize(len),b=ln(b);
		for(int i=0;i<len;i++)b[i]=0-b[i]; b[0]=b[0]+1;
		for(int i=0;i<len;i++)b[i]=b[i]+f[i]; return (a*b).set(len);
	}
	vec pow(vec a,int b){
		int len=a.size(); vec s={1};
		for(;b;b>>=1,a=a*a,a.resize(len))if(b&1)s=s*a,s.resize(len); return s;
	}
}
using poly::vec;
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	int n; vec a;
	std::cin>>n; init(n+5);
	a.resize(n),a.input();
	poly::exp(a).output();
	return 0;
	std::cin>>n; //哦，亲爱的上帝啊，请告诉我，为什么要输入一个n呢
	init(n+5),len=n+1,h[0]=1;
	vec phi=poly::ln(vec{1,1}.set(len+1)); phi.erase(phi.begin());
	vec phipow=poly::pow(phi,n+1);
	vec phiinv=poly::inv(vec{1}-phi);
	vec rpart=(phipow*phiinv).set(len);
	vec lpart=((poly::deri(phi)*phiinv).set(len)*rpart).set(len);
	for(int i=1;i<=n;i++)h[i]=fpow(n+1,wyp-2)*(lpart[i-1]+rpart[i]*(n-i+1));
	vec f,g,h;
	for(int i=0;i<=n;i++)f[i]=((n-i)&1?wyp-1:1)*ifac[n-i];
	for(int i=0;i<=n;i++)g[i]=fac[i]*h[i];
	h=f*g;
	for(int i=1;i<=n;i++)ans[i]=h[i+n]*fac[n]*ifac[i];
}