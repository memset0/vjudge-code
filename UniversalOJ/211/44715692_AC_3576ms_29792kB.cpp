// Author -- xyr2005

#include<bits/stdc++.h>

#define lowbit(x) ((x)&(-(x)))
#define DEBUG fprintf(stderr,"Running on Line %d in Function %s\n",__LINE__,__FUNCTION__)
#define SZ(x) ((int)x.size())
#define mkpr std::make_pair
#define pb push_back

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef std::pair<int,int> pi;
typedef std::pair<ll,ll> pl;
using std::min;
using std::max;

const int inf=0x3f3f3f3f,Inf=0x7fffffff;
const ll INF=0x3f3f3f3f3f3f3f3f;

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
template <typename _Tp>_Tp gcd(const _Tp &a,const _Tp &b){return (!b)?a:gcd(b,a%b);}
template <typename _Tp>inline _Tp abs(const _Tp &a){return a>=0?a:-a;}
template <typename _Tp>inline void chmax(_Tp &a,const _Tp &b){(a<b)&&(a=b);}
template <typename _Tp>inline void chmin(_Tp &a,const _Tp &b){(b<a)&&(a=b);}
template <typename _Tp>inline void read(_Tp &x)
{
	char ch(getchar());bool f(false);while(!isdigit(ch)) f|=ch==45,ch=getchar();
	x=ch&15,ch=getchar();while(isdigit(ch)) x=(((x<<2)+x)<<1)+(ch&15),ch=getchar();
	f&&(x=-x);
}
template <typename _Tp,typename... Args>inline void read(_Tp &t,Args &...args){read(t);read(args...);}
inline int read_str(char *s)
{
	char ch(getchar());while(ch==' '||ch=='\r'||ch=='\n') ch=getchar();
	char *tar=s;*tar++=ch,ch=getchar();while(ch!=' '&&ch!='\r'&&ch!='\n'&&ch!=EOF) *tar++=ch,ch=getchar();
	return *tar=0,tar-s;
}

const int N=105;
const int mod=998244353;
template<typename _Tp1,typename _Tp2>inline void add(_Tp1 &a,_Tp2 b){(a+=b)>=mod&&(a-=mod);}
template<typename _Tp1,typename _Tp2>inline void sub(_Tp1 &a,_Tp2 b){(a-=b)<0&&(a+=mod);}
ll ksm(ll a,ll b=mod-2){ll res=1;while(b){if(b&1)res=res*a%mod;a=a*a%mod,b>>=1;}return res;}
int f[N][N+N][N+N],g[N][N+N][N+N],h[N][N+N][N+N],sum[N];
int main()
{
	int n,w0,w1,w2,w3;read(n,w0,w1,w2,w3);
	f[0][0+N][0+N]=1,g[0][0+N][0+N]=1,sum[0]=1;
	for(int i=1;i<=n;++i)for(int x=-i;x<=i;++x)for(int y=-i;y<=i;++y)
	{
		f[i][x+N][y+N]=g[i][x+N][y+N]=(1LL*g[i-1][x+N-1][y+N]*w0+1LL*g[i-1][x+N+1][y+N]*w1+1LL*g[i-1][x+N][y+N-1]*w2+1LL*g[i-1][x+N][y+N+1]*w3)%mod;
		for(int j=0;j<i;++j) sub(f[i][x+N][y+N],1LL*f[j][x+N][y+N]*g[i-j][N][N]%mod);
		add(sum[i],f[i][x+N][y+N]);
	}
	for(int i=1;i<=n;++i)for(int x=-i;x<=i;++x)for(int y=-i;y<=i;++y) for(int j=0;j<i;++j)add(h[i][x+N][y+N],1LL*(sum[j]-h[j][-x+N][-y+N]+mod)*f[i-j][x+N][y+N]%mod);
	int s1=0,s2=0;
	for(int i=0;i<=n;++i) add(s1,1LL*sum[i]*ksm(w0+w1+w2+w3,n-i)%mod);
	for(int i=0;i<=n;++i)for(int x=-i;x<=i;++x)for(int y=-i;y<=i;++y)add(s2,1LL*h[i][x+N][y+N]*ksm(w0+w1+w2+w3,n-i)%mod);
	add(s2,s2),add(s2,s1);
	ll ans=1LL*ksm(w0+w1+w2+w3,n)*s2-1LL*s1*s1;
	ans%=mod,ans+=mod,ans%=mod;
	printf("%lld\n",ans);
	return 0;
}
