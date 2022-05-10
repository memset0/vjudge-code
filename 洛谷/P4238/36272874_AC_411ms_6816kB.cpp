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
const int N=1e5+10,mod=998244353;
int n,m,rev[N<<2];
struct z{
	int x;
	inline z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}p[N],w[N<<2];
inline z fpow(z a,int b){z s(1);for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}
struct poly:std::vector<z>{
	using std::vector<z>::vector;
	inline void read(){for(int i=0;i<size();i++)::read((int&)this->operator[](i));}
	inline void print(){for(int i=0;i<size();i++)::print(this->operator[](i).x," \n"[i==size()-1]);}
};
int pinit(int len){
	int lim=1,k=0;while(lim<len)lim<<=1,++k;
	for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
	for(int len=1;len<lim;len<<=1){
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
	std::reverse(&a[1],&a[lim]),dft(a,lim); z inv=fpow(lim,mod-2);
	for(int i=0;i<lim;i++)a[i]=a[i]*inv;
}
poly operator+(poly f,const poly &g){
	if(g.size()>f.size())f.resize(g.size());
	for(int i=0;i<g.size();i++)f[i]=f[i]+g[i];return f;
}
poly operator*(poly f,poly g){
	int l=f.size()+g.size()-1,lim=pinit(l);
	dft(f,lim),dft(g,lim);
	for(int i=0;i<lim;i++)f[i]=f[i]*g[i];
	idft(f,lim),f.resize(l);return f;
}
poly pinv(const poly &a,int l=-1){
	if((l=~l?l:a.size())==1)return poly{fpow(a[0],mod-2)};
	poly f=pinv(a,(l+1)>>1),g=poly(&a[0],&a[l]); int lim=pinit((l<<1)-1);
	dft(f,lim),dft(g,lim);
	for(int i=0;i<lim;i++)f[i]=f[i]*(2-f[i]*g[i]);
	idft(f,lim),f.resize(l);return f;
}
struct mat{
	poly x[2][2];
	friend inline mat operator*(const mat &a,const mat &b){
		mat c;
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				for(int k=0;k<2;k++)
					c.x[i][j]=c.x[i][j]+a.x[i][k]*b.x[k][j];
		return c;
	}
};
mat cdq(int l,int r){
	if(l==r){
		mat res;
		res.x[0][0]=(poly){fpow(p[l+1],mod-2)};
		res.x[0][1]=(poly){0,fpow(p[l+1],mod-2)*(p[l-1]-1)};
		res.x[1][0]=(poly){0,1};
		res.x[1][1]=(poly){0};
		return res;
	}
	int mid=(l+r)>>1;
	return cdq(mid+1,r)*cdq(l,mid);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	// read(n),read(m);
	// for(int i=1;i<=n;i++)read((int&)p[i]);
	poly f;
	read(n),f.resize(n),f.read();
	pinv(f).print();
}