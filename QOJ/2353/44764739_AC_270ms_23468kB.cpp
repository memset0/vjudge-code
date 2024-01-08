#include "bits/stdc++.h"
const int MAXN = 2015;
typedef std::pair<int,int> pii;
std::bitset<4015>row[MAXN],col[MAXN],diag[MAXN<<1|1], tp;
int f[MAXN][MAXN];
void init()
{
	int n=2005;
	for(int i=1;i<=n;++i)row[i].set(),col[i].set();
	for(int i=1;i<=n*2;++i)diag[i].set();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
		{
			tp=row[i]&col[j]&diag[i-j+n];
			if(i>1&&j>2)tp[f[i-1][j-2]]=0;
			if(i>2&&j>1)tp[f[i-2][j-1]]=0;
			int &cur=f[i][j];
			cur=tp._Find_first();
			row[i][cur]=0;
			col[j][cur]=0;
			diag[i-j+n][cur]=0;
		}
}
pii a[MAXN];
int bestx=MAXN,besty=MAXN;
void update(int x,int y)
{
	if(x<bestx)bestx=x,besty=y;
	else if(x==bestx&&y<besty)besty=y;
}
int main()
{
	//freopen("in","r",stdin);
	std::ios::sync_with_stdio(0),std::cin.tie(0);
	init();
	 int task;
	 std::cin>>task;
	 while(task--)
	 {
		int k,res=0;
		std::cin>>k;
		for(int i=1;i<=k;++i)
		{
			std::cin>>a[i].first>>a[i].second;
			res^=f[a[i].first][a[i].second];
		}
		if(!res){std::cout<<"-1 -1 -1\n";continue;}
		bestx=MAXN,besty=MAXN;
		for(int w=1;w<=k;++w)
		{
			int x=a[w].first,y=a[w].second;
			int r=res^f[x][y];
			for(int j=1;j<y;++j)
				if(f[x][j]==r)update(x,j);
			
			for(int i=1;i<x;++i)
				if(f[i][y]==r)update(i,y);
			for(int k=1;x>k&&y>k;++k)
				if(f[x-k][y-k]==r)update(x-k,y-k);
			// printf("i=%d,x=%d,y=%d\n",w,bestx,besty);
			if(x>1&&y>2&&f[x-1][y-2]==r)update(x-1,y-2);
			if(x>2&&y>1&&f[x-2][y-1]==r)update(x-2,y-1);
			if(bestx<MAXN&&besty<MAXN)
			{
				std::cout<<w<<" "<<bestx<<" "<<besty<<'\n';
				//printf("%d %d %d\n",w,bestx,besty);
				break;
			}
		}
	 }
	return 0;
}