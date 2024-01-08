#include<bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 200011,B = 105;
const ull base = 131131;
char a[MAXN],b[MAXN],rb[MAXN],t[MAXN],rt[MAXN];
int nxt1[MAXN],nxt2[MAXN],f1[MAXN],f2[MAXN],tf[MAXN];
ull pw[MAXN],h1[MAXN],h2[MAXN];
ull get1(int l,int r)
{
	if(!l)return h1[r];
	return h1[r]-h1[l-1]*pw[r-l+1];
}
ull get2(int l,int r)
{
	if(!l)return h2[r];
	return h2[r]-h2[l-1]*pw[r-l+1];
}
int n,q;
void pre_z(char* x,int m,int* next)
{
	next[0]=m;
	int j=0;
	while(j+1<m&&x[j]==x[j+1])j++;
	next[1]=j;
	int k=1;
	for(int i=2;i<m;i++)
	{
		int p=next[k]+k-1;
		int L=next[i-k];
		if(i+L<p+1)next[i]=L;
		else
		{
			j=std::max(0,p-i+1);
			while(i+j<m&&x[i+j]==x[j])j++;
			next[i]=j;
			k=i;
		}
	}
}
void Z(char* x,int m,char* y,int n,int* next,int* extend)
{
	pre_z(x,m,next);
	int j=0;
	while(j<n&&j<m&& x[j]==y[j])++j;
	extend[0]=j;
	int k=0;
	for(int i=1;i<n;++i)
	{
		int p=extend[k]+k-1;
		int L=next[i-k];
		if(i+L<p+1)extend[i]=L;
		else
		{
			j=std::max(0,p-i+1);
			while(i+j<n&&j<m&&y[i+j]==x[j])++j;
			extend[i]=j;
			k=i;
		}
	}
}
ll kmp()
{
		ll ans=0;
		int j=0,m=strlen(t);
		for(int i=0;i<m;++i)rt[i]=t[m-i-1];
		Z(t,m,a,n,nxt1,f1);
		Z(rt,m,rb,n,nxt2,tf);
		for(int i=0;i<n;++i)f2[n-i-1]=tf[i];
		// printf("F1:");
		// for(int i=0;i<n;++i)printf("%d ",f1[i]);
		
		// printf("\nF2:");
		// for(int i=0;i<n;++i)printf("%d ",f2[i]);
		// puts("");
		for(int i=0;i+m-1<n;++i)
			if(f1[i]&&f2[i+m-1])
				ans+=std::max(std::min(m-1,f1[i]+f2[i+m-1]-m+1),0);
		return ans;
}

struct SAM
{
	int t[MAXN][26],pre[MAXN],len[MAXN];
	int last,tot;
	std::vector<int>g[MAXN];
	SAM(){last=tot=1;}
	int extend(int w)
	{
		int pos=last,cur=++tot;
		len[cur]=len[pos]+1,last=cur;
		while(pos&&!t[pos][w])t[pos][w]=cur,pos=pre[pos];
		if(!pos){pre[cur]=1;return cur;}
		int nxt=t[pos][w];
		if(len[nxt]==len[pos]+1)pre[cur]=nxt;
		else
		{
			int tmp=++tot;
			len[tmp]=len[pos]+1,memcpy(t[tmp],t[nxt],sizeof t[nxt]);
			pre[tmp]=pre[nxt],pre[cur]=pre[nxt]=tmp;
			while(pos&&t[pos][w]==nxt)t[pos][w]=tmp,pos=pre[pos];
		}
		return cur;
	}
	void build()
	{
		for(int i=2;i<=tot;++i)g[pre[i]].emplace_back(i);
	}
	int dfn[MAXN],ed[MAXN], cur;
	void dfs(int u)
	{
		dfn[u]=++cur;
		for(auto v:g[u])dfs(v);
		ed[u]=cur;
	}
}sam;
int last[MAXN];
std::vector<ull>fx[B+1];
std::vector<int>pos[B+1][MAXN];
int place(std::vector<ull>& seq,ull val)
{
	return std::lower_bound(seq.begin(),seq.end(),val)-seq.begin();
}
int main()
{
	scanf("%s%s",a,b);
	n=strlen(a);
	for(int i=0;i<n;++i)last[i]=sam.extend(a[i]-'a');
	sam.build(),sam.dfs(1);
	for(int i=0;i<n;++i)rb[n-i-1]=b[i];
	h1[0]=a[0],pw[0]=1;
	for(int i=1;i<=n;++i)
		h1[i]=h1[i-1]*base+b[i],pw[i]=pw[i-1]*base;
	for(int x=1;x<=B;++x)
	{
		printf("De:x=%d\n",x);
		auto& q=fx[x];
		for(int i=0;i+x-1<n;++i)
			q.emplace_back(get1(i,i+x-1));
		std::sort(q.begin(),q.end());
		q.resize(std::unique(q.begin(),q.end())-q.begin());
		for(int i=0;i+x-1<n;++i)
		{
			int v=place(q,get1(i,i+x-1));
			pos[x][v].emplace_back(sam.dfn[last[i+x-1]]);
			printf("[%d,%d]: pos[%d,%d](%llu) pb %d\n",i,i+x-1,x,v,get1(i,i+x-1),sam.dfn[last[i+x-1]]);
		}
		for(int i=0;i<int(q.size());++i)
			std::sort(pos[x][i].begin(),pos[x][i].end());
	}

	scanf("%d",&q);
	while(q--)
	{
		scanf("%s",t);
		int m=strlen(t);
		if(m>B)
		{
			printf("%lld\n",kmp());	
			continue;
		}
		h2[0]=t[0];
		for(int i=1;i<m;++i)
			h2[i]=h2[i-1]*base+t[i];
		ll ans=0;
		int u=1;
		for(int i=0;i+1<m;++i)
		{
			u=sam.t[u][t[i]-'a'];
			if(!u)break;
			int x=m-i-1;
			ull v=get2(i+1,m-1);
			int p=place(fx[x],v);
			int l=sam.dfn[u],r=sam.ed[u];
			printf("x=%d,l=%d,r=%d,v=%llu\n",x,l,r,v);
			if(p<fx[x].size()&&fx[x][p]==v)
			{
				ans+=std::lower_bound(pos[x][p].begin(),pos[x][p].end(),r+1)-std::lower_bound(pos[x][p].begin(),pos[x][p].end(),l);
				printf("set ans to %lld\n",ans);
			}
		}
		std::cout<<ans<<'\n';
	}
	return 0;
}