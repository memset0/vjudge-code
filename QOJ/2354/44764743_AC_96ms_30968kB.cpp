#include<bits/stdc++.h>
typedef long long ll;
const int MAXN = 525011,mod = 998244353;
inline int S(int x){return x<mod?x:x-mod;}
inline int D(int x){return x>=0?x:x+mod;}
ll Qpow(ll a,ll p)
{
	ll res=1;
	while(p)
	{
		if(p&1)res=res*a%mod;
		a=a*a%mod,p>>=1;
	}
	return res;
}
int RT[MAXN],inv[MAXN];
void init(int n)
{
	int len=1;
	while(len<=n+2)len<<=1;
	for(int i=1;i<len;i<<=1)
	{
		int R=Qpow(3,(mod-1)/(i<<1));
		RT[i]=1;
		for(int j=1;j<i;++j)RT[i+j]=ll(RT[i+j-1])*R%mod;
	}
	inv[1]=1;
	for(int i=2;i<=len;++i)inv[i]=ll(mod-mod/i)*inv[mod%i]%mod;
}
int rev[MAXN];
void DFT(int* a,int n)
{
	for(int i=0;i<n;++i)
		rev[i]=(rev[i>>1]>>1)|(i&1?n>>1:0);
	for(int i=0;i<n;++i)
		if(rev[i]>i)std::swap(a[i],a[rev[i]]);
	for(int cur=1;cur<n;cur<<=1)
		for(int j=0;j<n;j+=cur<<1)
			for(int k=0;k<cur;++k)
			{
				int x=a[j+k],y=ll(RT[cur+k])*a[j+cur+k]%mod;
				a[j+k]=S(x+y),a[j+cur+k]=D(x-y);
			}
}
void IDFT(int* a,int n)
{
	std::reverse(a+1,a+n);
	DFT(a,n);
	for(int i=0;i<n;++i)a[i]=ll(a[i])*inv[n]%mod;
}
void Mul(int* f,int* g,int n,int m)
{
	int len=1;
	while(len<=n+m+1)len<<=1;
	DFT(f,len),DFT(g,len);
	for(int i=0;i<len;++i)f[i]=ll(f[i])*g[i]%mod;
	IDFT(f,len);
}
int cnt0[MAXN],cnt1[MAXN],c0,c1;
int err0[MAXN],err1[MAXN];
int fs[MAXN],ft[MAXN];
ll f[MAXN];
char s[MAXN],t[MAXN];
long long dp[MAXN],sum[MAXN];
int main()
{
	int w0,w1;
	scanf("%d%d",&w0,&w1);
	scanf("%s%s",s+1,t+1);
	int n=strlen(s+1),m=strlen(t+1);
	init(n+m);
	for(int i=1;i<=n;++i)
	{
		cnt0[i]=cnt0[i-1]+(s[i]=='o');
		cnt1[i]=cnt1[i-1]+(s[i]=='k');
	}
	for(int i=1;i<=m;++i)
		if(t[i]=='o')++c0;
		else if(t[i]=='k')++c1;
	memset(fs,0,sizeof fs),memset(ft,0,sizeof ft);
	for(int i=1;i<=n;++i)
		if(s[i]=='o')fs[i]=1;
	for(int i=1;i<=m;++i)
		if(t[i]=='k')ft[m-i]=1;
	Mul(fs,ft,n,m);
	for(int i=1;i<=n;++i)err0[i]=fs[m+i-1];
	memset(fs,0,sizeof fs),memset(ft,0,sizeof ft);
	for(int i=1;i<=n;++i)
		if(s[i]=='k')fs[i]=1;
	for(int i=1;i<=m;++i)
		if(t[i]=='o')ft[m-i]=1;
	Mul(fs,ft,n,m);
	for(int i=1;i<=n;++i)err1[i]=fs[m+i-1];
	ll ans=0;
	for(int i=1;i<=n-m+1;++i)
		if(err0[i]+err1[i]<=60)
		{
			//printf("i=%d,[%d,%d]\n",i,err0[i],err1[i]);
			ll sum=ll(cnt0[std::min(n,i+m-1)]-cnt0[i-1])*w0+
				ll(cnt1[std::min(n,i+m-1)]-cnt1[i-1])*w1;
			f[i]=sum>>(err0[i]+err1[i]);
		}
	dp[0]=0;
	for(int i=1;i<=n;++i){
		dp[i]=std::max(dp[i],dp[i-1]);
		if(i<=n-m+1)dp[i+m-1]=std::max(dp[i+m-1],dp[i-1]+f[i]);
	}
	printf("%lld\n",dp[n]);
	return 0;
}