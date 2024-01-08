#include "bits/stdc++.h"

const int MAXN = 111;
char s[MAXN],t[MAXN];
int dis[MAXN],pre[MAXN], Q[MAXN];
std::vector<int>seq;
void bfs(int n,int m,int c)
{
	dis[c]=1;
		int h=0,t=0;
		Q[t++]=c;
		while(h<t)
		{
			int x=Q[h++];
			for(int k=0;k<=m&k<=x;++k)
			{
				int y=(x-k+m-k);
				//printf("x=%d,y=%d\n",x,y);
				if(n-x>=m-k&&y>=0&&y<=n&&!dis[y])dis[y]=dis[x]+1,pre[y]=x, Q[t++]=y;
			}
		}
}
int main()
{
	int task;
	scanf("%d",&task);
	while(task--)
	{
		int n,m;
		scanf("%d%d",&n,&m);
		scanf("%s",s+1);
		int c=0;
		for(int i=0;i<=n;++i)dis[i]=0,pre[i]=0;
		for(int i=1;i<=n;++i)c+= (s[i]=='0');
		if(c==0)
		{
			puts("0");continue;
		}
		bfs(n,m,c);
		int f=dis[0]-1;
		if(f>n||!dis[0]){puts("CATACLYSM IMMINENT - TIME TO HOARD FACE MASKS");continue;}
		seq.clear();
		int p=0;
		while(p!=c)seq.emplace_back(p),p=pre[p];
		printf("%d\n",f);
		for(int d=0;d<f;++d)
		{
			int x=c,y=seq.back();
			seq.pop_back();
			int k=(x+m-y)>>1,r=m-k;
			t[n+1]=0;
			for(int i=1;i<=n;++i)
				if(s[i]=='1')
				{
					if(r)--r,t[i]='1',s[i]='0';
					else t[i]='0';
				}
				else
				{
					if(k)--k,t[i]='1',s[i]='1';
					else t[i]='0';
				}
			puts(t+1);
			c=y;
		}
		for(int i=1;i<=n;++i)
			if(s[i]=='0')
			{
				fprintf(stderr,"ERROR:ZERO FOUND!\n");
			}
	}
	return 0;
}