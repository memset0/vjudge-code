#include "bits/stdc++.h"
typedef long long ll;
typedef std::pair<int,int> pii;
const int MAXN=1000011,mod=998244353;
struct hash
{
	const int mod1=1e9+7,mod2=1e9+9,b=131131;
	int pw1[MAXN],pw2[MAXN];
	int f1[MAXN],f2[MAXN];
	void init(char* s,int n)
	{
		pw1[0]=1;
		for(int i=1;i<=n;++i)pw1[i]=ll(pw1[i-1])*b%mod1;
		pw2[0]=1;
		for(int i=1;i<=n;++i)pw2[i]=ll(pw2[i-1])*b%mod2;
		for(int i=1;i<=n;++i)
			f1[i]=(ll(f1[i-1])*b+s[i])%mod1,
			f2[i]=(ll(f2[i-1])*b+s[i])%mod2;
	}
	pii get(int l,int r)
	{
		return pii(((f1[r]-ll(f1[l-1])*pw1[r-l+1])%mod1+mod1)%mod1,((f2[r]-ll(f2[l-1])*pw2[r-l+1])%mod2+mod2)%mod2);
	}
}fs,ft;
char s[MAXN],t[MAXN];
int f0[MAXN],f1[MAXN],f2[MAXN];
int d0[MAXN],d1[MAXN],d2[MAXN];
int main()
{
	#ifdef memset0
	freopen("A.in","r",stdin);
#endif
	//ios::sync_with_stdio(0),cin.tie(0);
	scanf("%s%s",s+1,t+1);
	int n=strlen(s+1),m=strlen(t+1);
	fs.init(s,n),ft.init(t,m);
	f0[0]=1,d0[1]=mod-1;
	for(int i=1;i<=n;++i)
	{
		int l=i-1,r=n;
		//printf("i=%d:F[i-1]:(%d,%d,%d)\n",i,f0[i-1],f1[i-1],f2[i-1]);
		while(l<r)
		{
			int mid=(l+r+1)>>1;
			if(fs.get(i,mid)==ft.get(1,mid-i+1))l=mid;
			else r=mid-1;
		}
		d0[i]=(d0[i]+f0[i-1])%mod,d1[i]=(ll(d1[i])+f1[i-1]+f0[i-1])%mod;
		d2[i]=(ll(d2[i])+f2[i-1]+2ll*f1[i-1]+f0[i-1])%mod;
		int p=l;
		if(p-i+1<m)++p;

		//printf("i=%d,p=%d\n",i,p);
		if(p>=n)
		{
			f0[i]=(f0[i-1]+d0[i])%mod;
			f1[i]=(f1[i-1]+d1[i])%mod;
			f2[i]=(f2[i-1]+d2[i])%mod;
			continue;
		}
		//p:first diff pos
		l=p,r=n;
		while(l<r)
		{
			int mid=(l+r+1)>>1;
			if(fs.get(p+1,mid)==ft.get(1+(p-i+1),mid-p+(p-i+1)))l=mid;
			else r=mid-1;
		}
		//printf("i=%d,L=%d\n",i,l);
		d0[l+1]=(d0[l+1]-f0[i-1])%mod,d1[l+1]=(ll(d1[l+1])-f1[i-1]-f0[i-1])%mod;
		d2[l+1]=(ll(d2[l+1])-f2[i-1] -2ll*f1[i-1]-f0[i-1])%mod;
		f0[i]=(f0[i-1]+d0[i])%mod;
			f1[i]=(f1[i-1]+d1[i])%mod;
			f2[i]=(f2[i-1]+d2[i])%mod;
	}
	printf("%d\n",(f2[n]+mod)%mod);
	return 0;
}