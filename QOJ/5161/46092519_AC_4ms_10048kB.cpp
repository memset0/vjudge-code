#include "bits/stdc++.h"

const int MAXN = 500011,INF = 1e9+233;
namespace Flow
{
	struct edge
	{
		int v,w,nxt;
	}e[MAXN<<1|1];
	int last[MAXN],cur[MAXN],cnt=1;
	int in[MAXN],out[MAXN];
	int sum=0;
	void add_single_edge(int u,int v,int w)
	{
		e[++cnt].v=v,e[cnt].w=w,e[cnt].nxt=last[u],last[u]=cnt;
	}
	void add_bi_edge(int u,int v,int w)
	{
		add_single_edge(u,v,w),add_single_edge(v,u,0);
	}
	void adde(int u,int v,int low,int up)
	{
		//printf("Adde %d->%d,[%d,%d]\n",u,v,low,up);
		sum+=low;
		out[u]+=low,in[v]+=low;
		add_bi_edge(u,v,up-low);
	}
	int dep[MAXN];
	int Q[MAXN],h,t;
	bool bfs(int s,int t,int n)
	{
		for(int i=1;i<=n;++i)dep[i]=0,cur[i]=last[i];
		int qh=0,qt=0;
		Q[qt++]=s,dep[s]=1;
		while(qh<qt)
		{
			int u=Q[qh++];
			for(int i=last[u];i;i=e[i].nxt)
			{
				int v=e[i].v;
				if(e[i].w&&!dep[v])dep[v]=dep[u]+1,Q[qt++]=v;
			}
		}
		return dep[t]>0;
	}
	int ex_flow(int u,int t,int flow=INF)
	{
		if(u==t)return flow;
		int f=0;
		for(int &i=cur[u];i;i=e[i].nxt)
		{
			int v=e[i].v;
			if(e[i].w&&dep[v]==dep[u]+1)
			{
				int tmp=ex_flow(v,t,std::min(e[i].w,flow-f));
				f+=tmp,e[i].w-=tmp,e[i^1].w+=tmp;
				if(f==flow)return f;
			}
		}
		return f;
	}
	int Dinic(int s,int t,int n)
	{
		int res=0;
		while(bfs(s,t,n))
		{
			res+=ex_flow(s,t,n);
			//printf("res=%d\n",res);
		}
		return res;
	}
	void solve(int n,int m)
	{
		int S=n+1,T=n+2;
		n+=2;
		for(int i=1;i<=n;++i)
		{
			if(in[i])add_bi_edge(S,i,in[i]);
			if(out[i])add_bi_edge(i,T,out[i]);
		}
		//printf("sum=%d\n",sum);
		int ff=Dinic(S,T,n);
		//puts("Pass 79");
		if(ff!=sum)
		{
			fprintf(stderr,"Error:not a full flow!\n");
		}
		for(int u=1;u<=m;++u)
			for(int i=last[u];i;i=e[i].nxt)
		{
			int v=e[i].v;
			if(v>m&&v<=m+26&&!e[i].w)putchar(v-m-1+'a');
		}
		puts("");
	}
};
bool ban[511][26];
char res[511],a[511],b[511];
int cnt[26],type[26],cc[26];
int main()
{
#ifdef memset0
  freopen("L.in", "r", stdin);
#endif
	int n,m;
	scanf("%d%d",&n,&m);
	int S=m+26+1,T=S+1;
	for(int i=1;i<n;++i)
	{
		memset(cc,0,sizeof cc);
		scanf("%s%s",a+1,b+1);
		for(int j=1;j<=m;++j)
			if(b[j]=='G')
			{
				res[j]=a[j];
				for(int c=0;c<26;++c)
					if(c!=a[j]-'a')ban[j][c]=1;
				++cc[a[j]-'a'];
			}
			else
			{
				int x=a[j]-'a';
				if(b[j]=='Y')++cc[x],ban[j][x]=1;
				else type[x]=1,ban[j][x]=1;
			}
		for(int c=0;c<26;++c)cnt[c]=std::max(cnt[c],cc[c]);
	}
	for(int c=0;c<26;++c)
		{
			
			//printf("c=%d(%c)\n",c,c+'a');
			if(!type[c])Flow::adde(m+1+c,T,cnt[c],m);
			else Flow::adde(m+1+c,T,cnt[c],cnt[c]);
		}
	for(int i=1;i<=m;++i)
		for(int c=0;c<26;++c)
			if(!ban[i][c])
			{
				//if(cnt[c])printf("%d -> %c\n",i,c+'a');
				Flow::adde(i,m+1+c,0,1);
			}
	for(int i=1;i<=m;++i)
		Flow::adde(S,i,1,1);
	Flow::adde(T,S,0,m);
	Flow::solve(T,m);
	return 0;
}