#include "bits/stdc++.h"

const int MAXN = 600011;
int a[MAXN],p[MAXN];
int seq[MAXN];
int main()
{
#ifdef memset0
	freopen("D.in","r",stdin);
#endif
	int n;
	scanf("%d",&n);
	int r=0;
	for(int i=1;i<n;++i)
	{
		int x;
		scanf("%d",&x);
		if(x==(r+1)*2)seq[++r]=i;
		else if(x==r*2)p[i]=i;
		else if(x==(r-1)*2)p[seq[r]]=i,p[i]=seq[r],--r;
		else
		{
			puts("No");
			return 0;
		}
	}
	if(!r)p[n]=n;
	else if(r==1)p[seq[r]]=n,p[n]=seq[r];
	else
	{
		puts("No");
		return 0;
	}
	puts("Yes");
	for(int i=1;i<=n;++i)printf("%d ",p[i]);
	puts("");
	return 0;
}