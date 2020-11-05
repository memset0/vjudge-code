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
const int N=1e6+10,mod=998244353;
int T,n,ans,a[N],R[N<<2];
struct z {
	int x;
	z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}W[N<<2];
inline z fpow(z a,int b){z s(1);for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}
struct poly:std::vector<z>{
	using std::vector<z>::vector;
	inline void in(){for(size_t i=0;i<size();i++)read((int&)this->operator[](i));}
	inline void out()const{for(size_t i=0;i<size();i++)print(this->operator[](i).x," \n"[i+1==size()]);}
}res,f[N<<2],g[N<<2];
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
poly polyPlus(poly f,const poly &g){
	f.resize(std::max(f.size(),g.size()));
	for(int i=0;i<g.size();i++)f[i]=f[i]+g[i];
	return f;
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
void solve(int u,int l,int r){
	if(l==r){
		f[u]=poly{z(1)};
		g[u]=poly{z(1),z(0)-a[l]};
	}else{
		int mid=(l+r)>>1;
		solve(u<<1,l,mid);
		solve(u<<1|1,mid+1,r);
		int l=g[u<<1].size()+g[u<<1|1].size()-1,lim=initdft(l);
		f[u].resize(lim),g[u].resize(lim);
		dft(f[u<<1],lim),dft(f[u<<1|1],lim);
		dft(g[u<<1],lim),dft(g[u<<1|1],lim);
		for(int i=0;i<lim;i++){
			f[u][i]=f[u<<1][i]*g[u<<1|1][i]+g[u<<1][i]*f[u<<1|1][i];
			g[u][i]=g[u<<1][i]*g[u<<1|1][i];
		}
		idft(f[u],lim),idft(g[u],lim);
		f[u].resize(l-1),g[u].resize(l);
	}
	// printf("> %d : %d %d\n",u,l,r),f[u].out(),g[u].out();
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
	// freopen("1.out","w",stdout);
#endif
	for(read(T);T--;){
		read(n),ans=0;
		// printf("> %d\n",n);
		for(int i=1;i<=n;i++)read(a[i]),a[i]%=mod;
		solve(1,1,n);
		res=polyMul(f[1],polyInv(g[1]),n+1);
		// for(int i=1;i<=n;i++)printf("%d%c",res[i].x," \n"[i==n]);
		for(int i=1;i<=n;i++)ans^=res[i].x;
		printf("%d\n",ans);
	}
	std::cerr<<clock()/(double)CLOCKS_PER_SEC<<std::endl;
}