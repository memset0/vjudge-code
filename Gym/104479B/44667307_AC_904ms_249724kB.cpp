#include "bits/stdc++.h"
typedef long long ll;
typedef std::vector<int> P;
const int MAXN = 20,L = 1<<MAXN,mod = 998244353,inv2=(mod+1)>>1;///?!!!!
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
int inv=Qpow(L,mod-2);
void FWT(int* a)
{
	for(int cur=1;cur<L;cur<<=1)
		for(int j=0;j<L;j+=cur<<1)
			for(int k=0;k<cur;++k)
			{
				int x=a[j+k],y=a[j+cur+k];
				a[j+k]=S(x+y),a[j+cur+k]=D(x-y);
			}
	//for(int i=0;i<L;++i)a[i]=ll(a[i])*inv%mod;
}
void IFWT(int* a)
{
	FWT(a);
	for(int i=0;i<L;++i)a[i]=ll(a[i])*inv%mod;
}
int n,k;
P operator*(const P& a,const P& b)
{
	P res(k);
	for(int i=0;i<a.size();++i)
		for(int j=0;j<b.size();++j)
			res[(i+j)%k]=(res[(i+j)%k]+ll(a[i])*b[j])%mod;
	return res;
}
P Qpow(P a,int p)
{
	P res(k);
	res[0]=1;
	while(p)
	{
		if(p&1)res=res*a;
		a=a*a,p>>=1;
	}
	return res;
}
P pw1[L],pw2[L],p1={1,1},p2={1,mod-1};
int a[L],f[L],cnt[L];

void init()
{
	cnt[0]=0;
	for(int i=1;i<L;++i)
		cnt[i]=cnt[i>>1]+(i&1);
}

int main()
{
#ifdef memset0
	freopen("B.in","r",stdin);
#endif
	std::ios::sync_with_stdio(0),std::cin.tie(0);
	init();
	std::cin>>n>>k;
	for(int i=1;i<=n;++i)std::cin>>a[i],++f[a[i]],++f[0];
	FWT(f);
	pw1[0].resize(k),pw2[0].resize(k);
	pw1[0][0]=pw2[0][0]=1;
	for(int i=1;i<=n;++i)
		pw1[i]=pw1[i-1]*p1,pw2[i]=pw2[i-1]*p2;
	int ans=0;
	for(int i=0;i<L;++i)
	{
		int s=f[i];
		int x=ll(s)*inv2%mod,y=n-x;
		ans=(ans+ll(pw1[x][0])*pw2[y][0])%mod;
		for(int j=1;j<k;++j)
			ans=(ans+ll(pw1[x][j])*pw2[y][k-j])%mod;
	}
	ans=ll(ans)*inv%mod;
	printf("%d\n",ans);
	return 0;
}