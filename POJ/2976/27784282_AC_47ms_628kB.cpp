#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#include<queue>
using namespace std;
#define ll long long
#define RG register
#define MAX 1111
inline int read()
{
    RG int x=0,t=1;RG char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}
int a[MAX],b[MAX],n,K;
double c[MAX];
int main()
{
	while(233)
	{
		n=read();K=read();
		if(!n&&!K)break;
		for(int i=1;i<=n;++i)a[i]=read();
		for(int i=1;i<=n;++i)b[i]=read();
		double l=0,r=100;
		while(r-l>1e-5)
		{
			double mid=(l+r)/2;
			for(int i=1;i<=n;++i)c[i]=a[i]-mid*b[i];
			sort(&c[1],&c[n+1]);
			double t=0;
			for(int i=n;i>K;--i)t+=c[i];
			if(t>=0)l=mid;
			else r=mid;
		}
		printf("%.0f\n",l*100);
	}
	return 0;
}