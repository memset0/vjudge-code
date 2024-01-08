#include "bits/stdc++.h"
typedef long double lf;
typedef long long ll;
typedef std::pair<lf,lf> comp;
typedef std::pair<ll,ll> pii;
const lf PI = acos(-1.0);
const int MAXN = 2011;
comp operator+ (comp a,comp b){return comp(a.first+b.first,a.second+b.second);}
void operator+= (comp& a,comp b){a.first+=b.first,a.second+=b.second;}
comp operator* (comp a,comp b){return comp(a.first*b.first-a.second*b.second,a.first*b.second+a.second*b.first);}
comp Exp(lf x)
{
	return comp(cosl(x),sinl(x));
}
void DFT(comp* a,comp* b,int n)
{
	for(int t=0;t<n;++t)b[t]=comp(0,0);
	for(int t=0;t<n;++t)
		for(int s=0;s<n;++s)
			b[t]+=a[s]*Exp(-2.0*PI*s*t/n);
}

pii solve(lf b,lf c)//x*x+b*x+c<=0
{
	lf d=b*b-4*c;
	if(d<0)return pii(0,-1);
	d=sqrtl(d);
	lf x1=(-b-d)/2,x2=(-b+d)/2;
	return pii(ceil(x1),floor(x2));
}
comp a[MAXN],fa[MAXN],b[MAXN], fb[MAXN];
lf len2(comp a){return a.first*a.first+a.second*a.second;}
int main()
{
	
// #ifdef memset0
// 	freopen("D.in","r",stdin);
// #endif
	std::ios::sync_with_stdio(0),std::cin.tie(0);
	int n,k;std::cin>>n>>k;
	for(int i=0;i<n;++i)std::cin>>a[i].first;
	a[k]=comp(0,0),b[k]=comp(1,0);
	DFT(a,fa,n),DFT(b,fb,n);
	lf l=0,r=1e18;
	for(int w=1;w<=500;++w)
	{
		lf mid=(l+r)/2;
		// printf("Mid=%.10f\n",double(mid));
		// getchar();
		ll lb=-1e9,rb=1e9;
		for(int i=0;i<n;++i)
		{
			pii now=solve(2*fa[i].first*fb[i].first+2*fa[i].second*fb[i].second,len2(fa[i])-mid);
			// printf("i=%d,[%d,%d]\n",i,now.first,now.second);
			// printf("[%.3lf,%.3lf,%.3lf,%.3lf]\n",double(fa[i].first),double(fa[i].second),double(fb[i].first),double(fb[i].second));
			lb=std::max(lb,now.first);
			rb=std::min(rb,now.second);
		}
		if(lb<=rb)r=mid;
		else l=mid;
	}
	printf("%.12lf\n",double(sqrtl(l)));
	return 0;
}