//缺spj

#include<bits/stdc++.h>
using namespace std;
typedef long long lint;
inline int ty()
{
	register int a=0,b=1,c=getchar();
	while(!isdigit(c))b^=c=='-',c=getchar();
	while(isdigit(c))a=a*10+c-48,c=getchar();
	return b?a:-a;
}
const int _ = 53;
const double dinf = 1e9 , eps = 1e-14;
struct netflow
{
	static const int _n = 133 , _e = 9999999;
	int to[_e],ne[_e],he[_n],ecnt;
	double ev[_e];
	void adde(int a,int b,double c)
	{
		to[++ecnt]=b,ev[ecnt]=c,ne[ecnt]=he[a],he[a]=ecnt;
	}
	void addde(int a,int b,double c)
	{
		adde(a,b,c),adde(b,a,0);
	}
	int S,T,dcnt,dis[_n],gap[_n];
	double dfs(int x,double f)
	{
		if(x==T || f<=0)return f;
		int i,b,mid=dcnt-1;
		double g,r=f;
		for(i=he[x];i;i=ne[i])
		{
			if(ev[i]<eps)continue;
			b=to[i];
			if(dis[b]+1==dis[x])
			{
				g=dfs(b,min(r,ev[i])),r-=g,ev[i]-=g,ev[i^1]+=g;
				if(dis[S]>=dcnt)return f-r;
				if(r<eps)break;
			}
			mid=min(mid,dis[b]);
		}
		if(abs(f-r)<eps)
		{
			if(--gap[dis[x]]==0)dis[S]=dcnt;
			dis[x]=mid+1,gap[dis[x]]++;
		}
		return f-r;
	}
	double run(int s,int t)
	{
		S=s,T=t;
		memset(dis,0,sizeof(dis)),memset(gap,0,sizeof(gap)),gap[0]=dcnt;
		register double ans=0;
		while(dis[S]<dcnt)ans+=dfs(S,dinf);
		return ans;
	}
	void cls(){memset(he,0,sizeof(he)),ecnt=1,S=T=dcnt=0;}
	netflow(){cls();}
}nf;
int n,m,atk[_],ran[_][_],HP[_];
int able(double tim)
{
	register int i,j,s,t,ss,tt;
	register double tar=0;
	nf.cls();
	nf.dcnt=n+m,s=++nf.dcnt,t=++nf.dcnt,ss=++nf.dcnt,tt=++nf.dcnt;
	for(i=1;i<=m;i++)nf.addde(s,i,tim*atk[i]);
	for(i=1;i<=n;i++)
		nf.addde(ss,t,HP[i]),nf.addde(m+i,tt,HP[i]),tar+=HP[i];
	for(i=1;i<=m;i++)
		for(j=1;j<=n;j++)
			if(ran[i][j])
				nf.addde(i,m+j,dinf);
	nf.addde(t,s,dinf),nf.run(ss,tt);
	return tar-nf.run(s,t)<eps;
}
int main()
{
	register int i,j;
	register double l,r,mid;
	n=ty(),m=ty();
	for(i=1;i<=n;i++)HP[i]=ty();
	for(i=1;i<=m;i++)atk[i]=ty();
	for(i=1;i<=m;i++)
		for(j=1;j<=n;j++)
			ran[i][j]=ty();
	l=0,r=1e5;
	while(abs(r-l)>=1e-7)
	{
		mid=(r+l)/2;
		if(able(mid))r=mid;
		else l=mid;
	}
	printf("%.6lf\n",r+0.0000003);
	return 0;
}
