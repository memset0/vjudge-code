#include<bits/stdc++.h>
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

const int N=100010,mod=998244353;
int n,m;

struct z {
	int x;
	z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
};
inline z fpow(z a,int b){z s=1;for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}

struct vet:std::vector<z>{
	using std::vector<z>::vector;
	inline void input(int n){resize(n);for(int i=0;i<n;i++)read(this->operator[](i).x);}
	inline void output(){for(int i=0;i<size();i++)print(this->operator[](i).x," \n"[i+1==size()]);}
};

namespace ntt{
	int rev[N<<2]; z w[N<<2];
	int init(int len){
		int lim=1,k=0; while(lim<len)lim<<=1,++k;
		for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
		for(int len=1;len<lim;len<<=1){
			z wn=fpow(3,(mod-1)/(len<<1)); w[len]=1;
			for(int i=1;i<len;i++)w[i+len]=w[i+len-1]*wn;
		}
		return lim;
	}
	void dft(vet &a,int lim){
		a.resize(lim);
		for(int i=0;i<lim;i++)if(i<rev[i])std::swap(a[i],a[rev[i]]);
		for(int len=1;len<lim;len<<=1)
			for(int i=0;i<lim;i+=(len<<1))
				for(int j=0;j<len;j++){
					z x=a[i+j],y=w[j+len]*a[i+j+len];
					a[i+j]=x+y,a[i+j+len]=x-y;
				}
	}
	void idft(vet &a,int lim){
		dft(a,lim),std::reverse(&a[1],&a[lim]); z inv=fpow(lim,mod-2);
		for(int i=0;i<lim;i++)a[i]=a[i]*inv;
	}
}

namespace poly{
	using namespace ntt;
	vet operator+(vet a,const vet &b){
		a.resize(std::max(a.size(),b.size()));
		for(int i=0;i<b.size();i++)a[i]=a[i]+b[i]; return a;
	}
	vet operator-(vet a,const vet &b){
		a.resize(std::max(a.size(),b.size()));
		for(int i=0;i<b.size();i++)a[i]=a[i]-b[i]; return a;
	}
	vet operator*(vet a,vet b){
		int len=a.size()+b.size()-1,lim=init(len);
		dft(a,lim),dft(b,lim);
		for(int i=0;i<lim;i++)a[i]=a[i]*b[i];
		idft(a,lim),a.resize(len); return a;
	}
	vet inv(const vet &f,int len=-1){
		if((len=~len?len:f.size())==1)return {fpow(f[0],mod-2)};
		vet a(&f[0],&f[len]),b=inv(f,(len+1)>>1); int lim=init((len<<1)-1);
		dft(a,lim),dft(b,lim);
		for(int i=0;i<lim;i++)a[i]=b[i]*(2-a[i]*b[i]);
		idft(a,lim),a.resize(len); return a;
	}
	vet operator%(vet a,vet b){
		int len=(int)a.size()-b.size()+1; if(len<=0)return a;
		vet f=a; std::reverse(f.begin(),f.end()),f.resize(len);
		vet g=b; std::reverse(g.begin(),g.end()),g.resize(len);
		vet q=f*inv(g); q.resize(len),std::reverse(q.begin(),q.end());
		q.output();
		vet r=a-q*b; r.resize(b.size()-1); return r;
	}
}

namespace MPE{
	using namespace poly;
	vet p[N<<2],res;
	void seg(int u,int l,int r){
		if(l==r){p[u]={0-res[l],1}; return;}
		int mid=(l+r)>>1; seg(u<<1,l,mid),seg(u<<1|1,mid+1,r),p[u]=p[u<<1]*p[u<<1|1];
	}
	void divide(int u,int l,int r,const vet &a){
		if(l==r){res[l]=a[0]; return;}
		int mid=(l+r)>>1;
		divide(u<<1,l,mid,a%p[u<<1]);
		divide(u<<1|1,mid+1,r,a%p[u<<1|1]);
	}
	vet solve(vet a,vet b){
		int l=std::max(a.size(),b.size()),e=b.size(); b.resize(l);
		res=b,seg(1,0,l-1),divide(1,0,l-1,a),res.resize(e); return res;
	}
}

int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	// read(n),read(m);
	// for(int i=0;i<=n;i++)read(f[i]);
	// for(int i=1;i<=m;i++)read(g[i]);
	read(n),read(m);
	vet a,b;
	a.input(n+1);
	b.input(m+1);
	poly::operator%(a,b).output();
}