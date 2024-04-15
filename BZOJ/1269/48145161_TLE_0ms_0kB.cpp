#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N=3000005;

char a[N];

struct Splay
{
	int root,tot;
	int ch[N][2];
	int val[N],fa[N],cnt[N],sz[N],tag[N];
	
	Splay()
	{
		root=tot=0;
		memset(ch,0,sizeof(ch));
		memset(val,0,sizeof(val));
		memset(fa,0,sizeof(fa));
		memset(cnt,0,sizeof(cnt));
		memset(sz,0,sizeof(sz));
		memset(tag,0,sizeof(tag));
	}
	
	//\xcf\xf2\xc9ϸ\xfc\xd0\xc2sz,cnt 
	void pushup(int x)
	{
		sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+cnt[x];
	}
	
	//\xbd\xab\xb7\xadת\xb5\xc4tag\xcf\xf2\xcf\xc2ת\xd2ƣ\xa8\xb4\xcbʱsplay\xce\xde\xd0\xf2\xa3\xa9
	void pushdown(int x)
	{
		if(tag[x])
		{
			swap(ch[x][0],ch[x][1]);
			tag[ch[x][0]]^=1;
			tag[ch[x][1]]^=1;
			tag[x]=0;
		}
	}

	//\xb5\xa5\xd0\xfd 
	void rotate(int x)
	{
		int f=fa[x],ff=fa[f];
		int dir=(ch[f][1]==x);
		
		if(ff)
			ch[ff][ch[ff][1]==f]=x;
		fa[x]=ff;
		
		ch[f][dir]=ch[x][dir^1];
		fa[ch[x][dir^1]]=f;
		
		ch[x][dir^1]=f;
		fa[f]=x;
		
		pushup(f),pushup(x);
	}
	
	//\xd0\xfdתֱ\xd6\xc1fa[x]==to 
	void splay(int x,int to=0)
	{
		while(fa[x]!=to)
		{
			int f=fa[x],ff=fa[f];
			if(ff!=to)
				rotate((ch[f][1]==x)==(ch[ff][1]==f)?f:x);
			rotate(x);
		}
		if(!to)
			root=x;
	}
	
	//\xb2\xe5\xc8\xebvalΪx\xb5\xc4Ԫ\xcbأ\xa8һ\xb0\xe3\xd4\xda\xd3\xd0\xd0\xf2ʱ\xb5\xf7\xd3ã\xa9 
	void insert(int x)
	{
		int f=0,k=root;
		while(k && val[k]!=x)
			f=k,k=ch[k][x>val[k]];
		
		if(k)
			++cnt[k];
		else
		{
			k=++tot;
			if(!f)
				root=k;
			else
				ch[f][x>val[f]]=k;
			val[k]=x,cnt[k]=sz[k]=1,fa[k]=f;
		}
		splay(k);
	}
	
	//\xbd\xa8\xc1\xa2\xd0½ڵ\xe3 
	void newnode(int &x,int v,int f)
	{
		x=++tot;
		val[x]=v,cnt[x]=sz[x]=1,fa[x]=f;
	}
	
	//\xb8\xf9\xbe\xdd\xca\xfd\xd7\xe9 \xbd\xa8\xc1\xa2һ\xb8\xf6\xd7\xd3\xca\xf7\xa3\xa8һ\xb0\xe3\xd4\xda\xce\xde\xd0\xf2ʱ\xb5\xf7\xd3ã\xa9 
	void build(int &x,int l,int r,int f)
	{
		if(l>r)
			return;
		
		int mid=(l+r)>>1;
		newnode(x,a[mid],f);//a\xd0\xe8Ҫ\xb6\xa8\xd2\xe5\xd4\xdaSplayǰ
		build(ch[x][0],l,mid-1,x);
		build(ch[x][1],mid+1,r,x);
		
		pushup(x); 
	}
	
	//\xb7\xb5\xbb\xd8xǰ\xc7\xfd\xb5ı\xe0\xbaţ\xa8\xb1\xd8\xd0\xeb\xd3\xd0\xd0\xf2\xa3\xa9 
	int pre(int x)
	{
		int k=root,ans=0;
		while(k)
			if(val[k]>=x)
				k=ch[k][0];
			else
				ans=k,k=ch[k][1];
		return ans;
	}
	
	//\xb7\xb5\xbb\xd8x\xba\xf3\xbc̵ı\xe0\xbaţ\xa8\xb1\xd8\xd0\xeb\xd3\xd0\xd0\xf2\xa3\xa9 
	int suc(int x)
	{
		int k=root,ans=0;
		while(k)
			if(val[k]<=x)
				k=ch[k][1];
			else
				ans=k,k=ch[k][0];
		return ans;
	}
	
	//\xb7\xb5\xbb\xd8valΪx\xb5ı\xe0\xbaţ\xa8\xb1\xd8\xd0\xeb\xd3\xd0\xd0\xf2\xa3\xa9 
	int find(int x)
	{
		int k=root;
		while(val[k]!=x)
			k=ch[k][x>val[k]];
		return k;
	}
	
	//\xb5\xa5\xb5\xe3ɾ\xb3\xfdx\xa3\xa8\xb1\xd8\xd0\xeb\xd3\xd0\xd0\xf2\xa3\xa9 
	void erase(int x)
	{
		int prex=pre(x),sucx=suc(x);
		if(!prex || !sucx)
		{
			int k=find(x);
			cnt[k]--;
			splay(k);
			
			if(!cnt[k])
			{
				int dir=ch[k][1]>0;
				root=ch[k][dir];
				fa[root]=0;
			}
		}
		else
		{
			splay(prex);
			splay(sucx,prex);
			
			int k=ch[sucx][0];
			cnt[k]--;
			if(!cnt[k])
				ch[sucx][0]=0;
			
			pushup(sucx),pushup(prex);
		}
	}
	
	//\xb2\xe9\xd5\xd2valΪx\xb5\xc4Ԫ\xcbص\xc4rank\xa3\xa8\xb1\xd8\xd0\xeb\xd3\xd0\xd0\xf2\xa3\xa9 
	int rank(int x)
	{
		int k=root,ans=0;
		while(k && val[k]!=x)
			if(val[k]>x)
				k=ch[k][0];
			else
				ans+=sz[ch[k][0]]+cnt[k],k=ch[k][1];
		ans+=sz[ch[k][0]]+1;
		return ans;
	}
	
	//\xb7\xb5\xbbص\xdak\xb4\xf3Ԫ\xcbص\xc4\xcf±\xea
	int kth(int x)
	{
		int k=root;
		pushdown(k);
		
		while(sz[ch[k][0]]>=x || sz[ch[k][0]]+cnt[k]<x)
		{
			if(sz[ch[k][0]]>=x)
				k=ch[k][0];
			else
				x-=(sz[ch[k][0]]+cnt[k]),k=ch[k][1];
			pushdown(k);
		}
		return k;
	}
	
	//\xbd\xab[l,r]\xc7\xf8\xbc䷭ת\xa3\xa8\xb4\xcbʱsplay\xce\xde\xd0\xf2\xa3\xa9 
	//\xb4\xd30\xb2\xe5\xc8뵽n+1 
	void flip(int l,int r)
	{
		l=kth(l),r=kth(r+2);
		splay(l);
		splay(r,l);
		
		if(ch[r][0])
			tag[ch[r][0]]^=1;
	}
	
	//\xb1\xe9\xc0\xfa\xb5õ\xbd\xb7\xadת\xba\xf3\xb5\xc4\xd0\xf2\xc1У\xa8\xb4\xcbʱsplay\xce\xde\xd0\xf2\xa3\xa9 
	void trav(int x)
	{
		if(!x)
			return;
		pushdown(x);
		
		trav(ch[x][0]);
		if(val[x]>0)//n\xd0\xe8Ҫ\xb6\xa8\xd2\xe5\xd4\xdaSplayǰ 
			printf("%c",val[x]);
		trav(ch[x][1]);
	}
}t;

int n,m,cursor=1;
char opt[N];

void Insert()
{
	int u=t.kth(cursor);
	t.splay(u);
	int v=t.kth(cursor+1);
	t.splay(v,u);
	
	int tmp;
	t.build(tmp,1,m,0);
	
	t.ch[v][0]=tmp;
	t.fa[tmp]=v;
	t.pushup(v),t.pushup(u);
}

void Move()
{
	cursor=m+1;
}

void Delete()
{
	int u=t.kth(cursor);
	t.splay(u);
	int v=t.kth(cursor+m+1);
//	printf("%d %d\n",u,v);
	t.splay(v,u);
	
	t.ch[v][0]=0;
	t.pushup(v),t.pushup(u);
}

void Rotate()
{
	int u=t.kth(cursor);
	t.splay(u);
	int v=t.kth(cursor+m+1);
	t.splay(v,u);
	t.tag[t.ch[v][0]]^=1;
}

void Get()
{
	int u=t.kth(cursor+1);
	t.splay(u);
	if(t.val[u]!='\n')
		putchar(t.val[u]);
/*	else
		printf("enter\n");*/
	putchar('\n');
}

void Prev()
{
	cursor--;
}

void Next()
{
	cursor++;
}

int main()
{
//	freopen("9.in","r",stdin);
	scanf("%d",&n);
/*	if(n==86000)
		n+=2;*/
	t.build(t.root,1,4,0);
	
	while(~scanf("%s",opt+1))
	{
/*		if(n<100)
		printf("%s\n",opt+1);*/
		
		if(opt[1]=='I')
		{
			scanf("%d",&m),getchar();
			for(int i=1;i<=m;i++)
				a[i]=getchar();
			Insert();
		}
		if(opt[1]=='M')
			scanf("%d",&m),Move();
		if(opt[1]=='D')
			scanf("%d",&m),Delete();
		if(opt[1]=='R')
			scanf("%d",&m),Rotate();
		if(opt[1]=='G')
			Get();
		if(opt[1]=='P')
			Prev();
		if(opt[1]=='N')
			Next();
		
/*		if(n<100)
			printf("cursor=%d sz=%d\n",cursor,t.sz[t.root]);*/
	}
	return 0;
}
