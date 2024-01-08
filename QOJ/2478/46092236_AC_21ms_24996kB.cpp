#include "bits/stdc++.h"
typedef __int128 ll;/// remember __int128 !
const int MAXN = 200011;

ll f[111][111][111];
void init()
{
	for(int len=1;len<=101;++len)
	{
		//if(len<=20)printf("len=%d\n",len);
		for(int i=1;i<=len;++i)f[len][0][i]=0;
		f[len][0][1]=1;
		for(int d=1;d<=101;++d)
		{
			//if(len<=20&&d<=20)printf("D=%d:",d);
			for(int i=1;i<=len;++i)
			{
				f[len][d][i]=f[len][d-1][i-1]+f[len][d-1][i]+f[len][d-1][i+1];
				//if(len<=20&&d<=20)printf("%lld ",f[len][d][i]);
			}
			//if(len<=20&&d<=20)puts("");
		}
	}
}
int cnt[111];
int main()
{
	//freopen("E.out","w",stdout);
	init();
	long long tmp;
	scanf("%lld",&tmp);
	ll n=tmp;
	for(int d=2;d<=100;++d)
	{
		n=tmp;
		memset(cnt,0,sizeof cnt);
		int len=d+1,c=0;
		while(n&&c<10000)
		{
			int p=0;
			ll mx=0;
			for(int i=1;i<=len;++i)
				if(f[len][d][i]<=n&&f[len][d][i]>mx)mx=f[len][d][i],p=i;
			n-=mx,++cnt[p],++c;
		}
		if(n)continue;
		int v=0;
		for(int i=1;i<=len;++i)v=std::max(v,cnt[i]);
		int m=ll(v)*len,sx=0;
		if(m>2e5)continue;
		printf("%d\n",m);
		for(int i=1;i<=v;++i,sx+=2)
		{
			printf("%d 1 1\n",sx);	
			for(int j=2;j<=len;++j)
				printf("%d %d 0\n",sx,j);
		}
		printf("%d %d\n",c,d);
		sx=0;
		for(int i=1;i<=v;++i,sx+=2)
			for(int j=1;j<=len;++j)
				if(cnt[j])--cnt[j],printf("%d %d\n",sx,j);
		return 0;
	}
	return 0;
}