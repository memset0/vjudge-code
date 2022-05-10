#include<bits/stdc++.h>
using namespace std;
#define inf (1e9)
template<class T> inline void read(T &x){
	x=0; char c=getchar(); bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	if(f)x=-x;
}
#define N 5005
int x[N],y[N],v[N],sx,sy,tx,ty;
double vp,vf,vh;
int vis[N];
double dis[N];
double dist(int x1,int y1,int x2,int y2){
	return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}
void work()
{
	cin>>sx>>sy>>tx>>ty>>vf>>vp>>vh;
	int n; read(n);
	for(int i=0;i<=n;i++)
	{
		read(x[i]),read(y[i]),read(v[i]);
		if(v[i]<vp) i--,n--;
	}
	n++;
	x[n]=tx,y[n]=ty;
	for(int i=0;i<=n;i++) dis[i]=1e9,vis[i]=0;
	dis[0]=0;
	for(int i=1;i<=n;i++)
	{
		double minn=inf;
		int id=-1;
		for(int j=0;j<=n;j++)
		{
			if(!vis[j]&&dis[j]<minn) minn=dis[j],id=j;
		}
		vis[id]=1;
		if(id==n) break;
		double V=v[id]-vp;
//		cout<<V<<endl;
		for(int j=0;j<=n;j++)
		{
			if(vis[j]) continue;
			double D=dist(x[id],y[id],x[j],y[j]);
			double tim=D/vh;
			double used=tim*vp;
			double A=used/V;
//			printf("%d %d - %lf %lf %lf %lf\n",i,j,D,tim,used,A);
			if(dis[id]+A+tim<dis[j]) dis[j]=dis[id]+A+tim;
		}
	}
	printf("%.12lf\n",dis[n]);
}
int main()
{
	int T; read(T); while(T--) work();
}
