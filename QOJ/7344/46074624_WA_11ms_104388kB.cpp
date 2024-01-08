#include "bits/stdc++.h"
const double PI=acos(-1.0);
const int MAXN = 2097211;
struct comp
{
	double x,y;
	comp(double _x=0,double _y=0){x=_x,y=_y;}
	comp operator+ (comp you){return comp(x+you.x,y+you.y);}
	comp operator- (comp you){return comp(x-you.x,y-you.y);}
	comp operator* (comp you){return comp(x*you.x-y*you.y,x*you.y+y*you.x);}
};
comp tf[MAXN],tg[MAXN],RT[MAXN];
int init(int n)
{
	int len=1;
	while(len<=n+2)len<<=1;
	for(int i=1;i<len;i<<=1)
	{
		comp R(cos(PI/i),sin(PI/i));
		RT[i]=1;
		for(int j=1;j<i;++j)
			RT[i+j]=RT[i+j-1]*R;
	}
	return len;
}
int rev[MAXN];
void DFT(comp* a,int len)
{
	for(int i=0;i<len;++i)
		rev[i]=(rev[i>>1]>>1)|(i&1?len>>1:0);
	for(int i=0;i<len;++i)
		if(rev[i]>i)std::swap(a[i],a[rev[i]]);
	for(int cur=1;cur<len;cur<<=1)
		for(int j=0;j<len;j+=cur<<1)
			for(int k=0;k<cur;++k)
			{
				comp x=a[j+k],y=RT[cur+k]*a[j+cur+k];
				a[j+k]=x+y,a[j+cur+k]=x-y;
			}
}
void IDFT(comp* a,int len)
{
	std::reverse(a+1,a+len);
	DFT(a,len);
	for(int i=0;i<len;++i)a[i].x/=len;
}
int len;
void Mul(double* f,double* g,double* res)
{
	for(int i=0;i<len;++i)tf[i]=comp(f[i],0);
	for(int i=0;i<len;++i)tg[i]=comp(g[i],0);
	DFT(tf,len),DFT(tg,len);
	for(int i=0;i<len;++i)tf[i]=tf[i]*tg[i];
	IDFT(tf,len);
	for(int i=0;i<len;++i)res[i]=tf[i].x;
}
double p[MAXN],q[MAXN],r[MAXN],sq[MAXN];
double tp[MAXN],tq[MAXN];
double win[MAXN],f[MAXN];
double dp[MAXN],prod[MAXN];
int main()
{
#ifdef memset0
	freopen("B.in","r",stdin);
#endif
	int n,k;
	scanf("%d%d",&n,&k);
	len=init(6*n+10);
	for(int i=0;i<n;++i)scanf("%lf",&p[i]);
	for(int i=1;i<=2*n-2;++i)scanf("%lf",&q[i]),sq[i]=sq[i-1]+q[i];
	for(int i=2*n-1;i>=0;--i)r[i]=r[i+1]+p[i];
	for(int d=0;d<=2*n;++d)
		tq[2*n-d]=r[d];
	for(int d=0;d<=n;++d)
		tq[2*n+d]=1;
	 Mul(q,tq,win);
	// for(int t=0;t<n;++t)
	// {
	// 	for(int k=1;k<=2*n-2;++k)
	// 		if(k<t)win[t]+=q[k];
	// 		else win[t]+=q[k]*r[k-t];
	// 	//printf("win[%d]=%.10lf\n",t,win[t]);
	// }

	f[0]=0;
	for(int i=1;i<k;++i)
	{
		for(int j=0;j<n;++j)
			f[i]+=p[j]*std::max(win[2*n+n-j-1],f[i-1]);
		f[i]=std::max(f[i],win[2*n]);
		//printf("F[%d]=%.10lf\n",i,f[i]);
	}
	for(int i=0;i<n;++i)
	{
		tp[i]=0;
		for(int k=1;i+k-1<=n;++k)	
			tp[i]+=q[k]*r[i+k]/r[i];
	}
	for(int i=n-1;i>=0;--i)
	{
		if(r[i]<1e-7)
		{
			dp[i]=sq[n-i];
			continue;
		}
		dp[i]=p[i]/r[i]*sq[n-i-1]+(r[i+1]/r[i])*dp[i+1];
		dp[i]=std::max(dp[i],tp[i]);
	}
	printf("%.10lf\n",std::max(f[k-1],dp[0]));
	return 0;
}