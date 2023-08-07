#include "bits/stdc++.h"
typedef std::pair<int,int> pii;
const int MAXN = 111;
std::vector<pii>res[MAXN];
int a[MAXN][MAXN];
void addedge(int x,int y,int c)
{
	if(a[x][y])
	{
		fprintf(stderr,"ERROR: addedge (%d,%d,%d)\n",x,y,c);
		exit(0);
	}
	a[x][y]=a[y][x]=c;
}
int main()
{
	std::ios::sync_with_stdio(0),std::cin.tie(0),std::cout.tie(0);
	int task;
	std::cin>>task;
	while(task--)
	{
		int n,k;std::cin>>n>>k;
		for(int u=1;u<=n;++u)
			for(int v=1;v<=n;++v)a[u][v]=0;
		if(k>n/2)
		{
			puts("NO");continue;
		}
		int w=n/2-1;
		for(int x=1;x+1<=n;x+=2)
		{
			int i=(x+1)/2;
			res[i].clear();
			int c1=0,c2=0;
			//printf("i=%d,(%d,%d),w=%d\n",i,x,x+1,w);
			addedge(x,x+1,i);
			for(int y=1;y+1<=n;y+=2)
				if(x!=y)
				{
					//printf("consider y=%d [%d,%d]\n",y,a[x][y],a[x+1][y]);
					if(!a[x][y])addedge(x,y,i),addedge(x+1,y+1,i);
					else addedge(x+1,y,i),addedge(x,y+1,i);
				}
			if(n&1)addedge(x,n,i),addedge(x+1,n,i);
		}
		puts("YES");
		for(int u=1;u<=n;++u)
			for(int v=1;v<u;++v)printf("%d%c",std::min(a[u][v],k),v==u-1?'\n':' ');
	}
	return 0;
}