#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define pair std::pair<int,int>
const int N=310,M=32000,L=5000,mod=1e9+7;
namespace io {
	const int SIZE = (1 << 21) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int f, qr;
	// getchar
	#define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	// print the remaining part
	inline void flush () {
		fwrite (obuf, 1, oS - obuf, stdout);
		oS = obuf;
	}
	// putchar
	inline void putc (char x) {
		*oS ++ = x;
		if (oS == oT) flush ();
	}
	// input a signed integer
	inline char gch(){
		char c=gc();for(;isspace(c);c=gc());
		return c;
	}
	inline void gs(char*c){
		char x=gc();for(;isspace(x);x=gc());
		for(;!isspace(x);x=gc())*c++=x;*c=0;
	}
	template <class I>
	inline void gi (I &x) {
		for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;
		for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15); x *= f;
	}
	// print a signed integer
	template <class I>
	inline void print (I x) {
		if (!x) putc ('0'); if (x < 0) putc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10;
		while (qr) putc (qu[qr --]);
	}
	//no need to call flush at the end manually!
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
}
struct ExactDiv {
  ExactDiv() {}
  ExactDiv(ull n){
  	for(z=0;!(n&1);++z,n>>=1);
  	t=((ull)-1) / n;
	i=mul_inv(n);
  }
  ull mul_inv(ull n) {
    ull x = n;
    for (int i = 0; i < 6; ++i) x *= 2 - n * x;
    return x;
  }
  inline bool divide(const ull&n) { return ((n>>z<<z)==n) && (n>>z)*this->i<=this->t; }
  inline bool ck(const ll&n){
  	return n>=0 && divide(n);
  }
  ull t, i,z;
}ediv[M],el[L];
int T,n,m,l,tl,pc,sqn,p[L],ans[N],vis[M],bln[N],pri[M];ll a[N],ls[L],pw[L][65],ipw[L][65];
std::vector<ll> fac;
std::vector<pair> v[N];
const int Z=1005;
int gg[Z][Z];
int C;
template<class T> inline T gcd(T x,T y){++C;return x<Z && y<Z?gg[x][y]:(y?gcd(y,x%y):x);}
struct query{
	int l,r,id;
	inline bool operator<(const query &other)const{
		return bln[l]==bln[other.l]?(r<other.r)==(bln[l]&1):l<other.l;
//		return bln[l]==bln[other.l]?r<other.r:l<other.l;
	}
}q[N];
inline int fpow(int a,int b){
	int s=1;
	for(;b;b>>=1,a=(ll)a*a%mod)if(b&1)s=(ll)s*a%mod;
	return s;
}
int buc[L][65],mx[L];
int tot=1,zcnt;
inline void add(const std::vector<pair> &vet){
	for(auto it:vet){
		if(mx[it.first]){	
			if(ls[it.first])tot=tot*ipw[it.first][mx[it.first]]%mod;
				else --zcnt;
		}
		++buc[it.first][it.second];
		mx[it.first]=std::max(mx[it.first],it.second);
		if(mx[it.first]){	
			if(ls[it.first])tot=tot*pw[it.first][mx[it.first]]%mod;
				else ++zcnt;
		}
	}
}
inline void del(const std::vector<pair> &vet){
	for(auto it:vet){
		if(mx[it.first]){	
			if(ls[it.first])tot=tot*ipw[it.first][mx[it.first]]%mod;
				else --zcnt;
		}
		--buc[it.first][it.second];
		for(mx[it.first]=p[it.first];mx[it.first] && !buc[it.first][mx[it.first]];--mx[it.first]);
		if(mx[it.first]){	
			if(ls[it.first])tot=tot*pw[it.first][mx[it.first]]%mod;
				else ++zcnt;
		}
	}
}
struct hmp{
static const int mo=1999;
int h[mo],nxt[mo],xb;ll v[mo];
inline void insert(ll x){
	if(x==1)return;
	int z=x%mo,i=h[z];
	for(;i && v[i]!=x;i=nxt[i]);
	if(!i)nxt[++xb]=h[z],h[z]=xb,v[xb]=x;
}
}ss;
int main(){
	for(int i=2;i<M;i++){
		if(!vis[i])pri[++pc]=i;
		for(int j=1;j<=pc&&i*pri[j]<M;j++){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0)break;
		}
	}
	for(int i=1;i<=pc;++i)ediv[i]=pri[i];
	for(int i=0;i<Z;++i)for(int j=0;j<Z;++j)gg[i][j]=!i || !j?i+j:(i>j?gg[i-j][j]:gg[i][j-i]);
	for(io::gi(T);T--;){
		io::gi(n),io::gi(m),sqn=sqrt(n),l=0,fac.clear();
		for(int i=1;i<=n;i++)io::gi(a[i]),bln[i]=i/sqn,v[i].clear();
		for(int i=1;i<=m;i++)io::gi(q[i].l),io::gi(q[i].r),q[i].id=i,ans[i]=1;
		static int id[M];memset(id+1,0,pc<<2);
		for(int i=1;i<=n;i++)
			for(int j=1,cnt;j<=pc;j++)if(ediv[j].divide(a[i])){
				cnt=0;while(a[i]%pri[j]==0)++cnt,a[i]/=pri[j];
				if(!id[j])ls[id[j]=++l]=pri[j],el[l]=ls[l],p[l]=0;
				v[i].push_back(std::make_pair(id[j],cnt)),p[id[j]]=std::max(p[id[j]],cnt);
			}
		ss.xb=0;memset(ss.h,0,sizeof ss.h);
		int step=8;
		static ll aa[N];int nn=0;
		for(int i=1;i<=n;++i)if(a[i]>1)aa[++nn]=a[i];
		for(int i=1;i<=nn;++i)ss.insert(aa[i]);
		for(int i=1;i<=nn;i++){
			for(int j=i+1;j<=nn;j+=step){
				ll pi=1;
				for(int k=0;k<step && j+k<=nn;++k)pi=(__int128)pi*aa[j+k]%aa[i];
				if(gcd(pi,aa[i])!=1){
				    for(int k=0;k<step && j+k<=nn;++k){
    					ll x=gcd(aa[i],aa[j+k]);
    					ss.insert(x);ss.insert(aa[i]/x);ss.insert(aa[j+k]/x);
    				}
				}
			}
		}
		fac=std::vector<ll>(ss.v+1,ss.v+ss.xb+1);
		tl=l;
		if(!fac.empty())for(int i=fac[0]==1?1:0,fl;fl=0,i<fac.size();i++){
			fl=1;
			if(fl)ls[++l]=fac[i],p[l]=0,el[l]=ls[l];
		}
		for(int i=1;i<=n;i++){
			for(int j=tl+1,cnt;j<=l;j++)if(el[j].divide(a[i])){
				cnt=0;while(a[i]%ls[j]==0)++cnt,a[i]/=ls[j];
				v[i].push_back(std::make_pair(j,cnt)),p[j]=std::max(p[j],cnt);
			}
		}
		for(int i=1;i<=l;i++)for(int j=0;j<=p[i];j++)ipw[i][j]=fpow(pw[i][j]=fpow(ls[i]%mod,j),mod-2);
		std::stable_sort(q+1,q+m+1);
		int ul=1,ur=0;
		for(int i=1;i<=m;i++){
			while(ul>q[i].l)add(v[--ul]);while(ur<q[i].r)add(v[++ur]);
			while(ul<q[i].l)del(v[ul++]);while(ur>q[i].r)del(v[ur--]);
			ans[q[i].id]=tot;
		}
		while(ul<=ur)del(v[ur--]);
		for(int i=1;i<=m;i++)io::print(ans[i]),io::putc('\n');
	}
	return 0;
}