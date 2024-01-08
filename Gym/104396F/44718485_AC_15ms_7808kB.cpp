#include "bits/stdc++.h"

const int MAXN = 1000011;
double f[MAXN];
int main()
{
	int n,m;
	double p,q;
	std::cin>>n>>m>>p>>q;
	p/=100,q/=100;
	f[0]=0;
	for(int i=m;i<=n;++i)
	{
		if(m>1)f[i]=std::max(f[i-m]+1+p,1+q*f[i-m+1]+(1-q)*f[i-m]);
		else f[i]=std::max(f[i-m]+1+p,1.0/(1-q)+f[i-m]);
	}
	printf("%.10lf\n",f[n]);
	return 0;
}