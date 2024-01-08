#include "bits/stdc++.h"
typedef long long ll;
bool check(int a,int b)
{
	int n=b;
	return a<=ll(n)*(n-1)/2;
}
int main()
{
#ifdef memset0
	freopen("E.in","r",stdin);
#endif
	int a,b;
	scanf("%d/%d",&a,&b);
	if(a<b)
	{
		if(a==b-1)
		{
			int n=b;
			printf("%d %d\n",n,n-1);
			for(int i=2;i<=n;++i)printf("%d %d\n",1,i);
		}
		else puts("impossible");
		return 0;
	}
	while(!check(a,b))a<<=1,b<<=1;
	int n=b,rest=a-(n-1);
	printf("%d %d\n",n,n-1);
	printf("1 2\n");
	for(int i=3;i<=n;++i)
	{
		int k=std::min(i-2,rest);
		printf("%d %d\n",k+1,i);
		rest-=k;
	}

	return 0;
}