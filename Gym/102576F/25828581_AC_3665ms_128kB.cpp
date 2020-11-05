#include<bits/stdc++.h>
// #define int __int128
// #define int64_t __int128
#define int128_t __int128
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
template<class T> inline T gcd(T n,T m){return m?gcd(m,n%m):n;}
const int N=20;
int T,n,a,b,c,d,m,p[N];
int64_t fac[N],f[N][N*N];
struct frac{
	int64_t x,y;
	inline frac(int64_t x=0,int64_t y=1):x(x),y(y){}
	inline frac filter()const{
		int64_t gcd=::gcd(x,y);
		return gcd==1?(*this):frac{x/gcd,y/gcd};
	}
	friend inline bool operator<(const frac &a,const frac &b){
		return (int128_t)a.x*b.y<(int128_t)a.y*b.x;
	}
	friend inline bool operator<=(const frac &a,const frac &b){
		return (int128_t)a.x*b.y<=(int128_t)a.y*b.x;
	}
	friend inline frac operator+(const frac &a,const frac &b){
		int64_t lcm=a.y*b.y/gcd(a.y,b.y);
		return {lcm/a.y*a.x+lcm/b.y*b.x,lcm};
	}
	friend inline frac operator-(const frac &a,const frac &b){
		int64_t lcm=a.y*b.y/gcd(a.y,b.y);
		return {lcm/a.y*a.x-lcm/b.y*b.x,lcm};
	}
	friend inline frac operator*(const frac &a,const frac &b){
		return {a.x*b.x,a.y*b.y};
	}
}x,ans;
int32_t main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	f[1][0]=fac[0]=1;
	for(int i=1;i<=16;i++)fac[i]=fac[i-1]*i;
	for(int i=1;i<=15;i++)
		for(int j=0;j<=i*(i-1)/2;j++)
			for(int k=0;k<=i;k++){
				f[i+1][j+k]+=f[i][j];
			}
	for(read(T);T--;){
		read(n),read(a),read(b),read(c),read(d),m=n*(n-1)/2;
		auto calc=[&](int k){return std::min(a*k,b+a*(m-k));};
		std::vector<int64_t> sum(m+1),cnt(m+1);
		std::vector<std::pair<int64_t,int64_t>> vet(m+1);
		for(int i=0;i<=m;i++)vet[i]=std::make_pair(calc(i),f[n][i]);
		std::sort(vet.begin(),vet.end());
		// for(int i=0;i<=m;i++)printf("<%lld,%lld> ",vet[i].first,vet[i].second); puts("");
		for(int i=0;i<=m;i++)sum[i]=(i?sum[i-1]:0)+vet[i].first*vet[i].second;
		for(int i=0;i<=m;i++)cnt[i]=(i?cnt[i-1]:0)+vet[i].second;
		// for(int i=0;i<=m;i++)printf("%lld%c",sum[i]," \n"[i==m]);
		// for(int i=0;i<=m;i++)printf("%lld%c",cnt[i]," \n"[i==m]);
		bool fl=0;
		for(int i=1;i<=m;i++){ // 0...i -> go through || i+1...m -> refresh
			auto y=frac{sum[i]+fac[n]*c-cnt[i]*c,cnt[i]}.filter();
			// printf("%d : %lld/%lld | %lld %lld %lld %lld\n",i,y.x,y.y,sum[i],fac[n]*c,-c*cnt[i],cnt[i]);
			if(vet[i].first<=y+frac{c})x=fl?std::min(x,y):y,fl=1;
		}
		assert(fl);
		// printf("x=%lld/%lld\n",x.x,x.y);
		for(int i=1,q,k;k=0,i<=d;i++){
			for(int i=1;i<=n;i++)read(p[i]);
			for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)k+=p[i]>p[j];
			ans=std::min(x+frac{c},frac{calc(k)}).filter();
			print(ans.x,'/'),print(ans.y,'\n');
		}
	}	
}