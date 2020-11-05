#include<bits/stdc++.h>
using namespace std;
int n,C;
const int N=1000005;
namespace sub1
{
int ans;
struct seg_tr{
	struct node{
		int ls,rs;
		int minn;
	}f[N<<1];
	int node_cnt;
	inline void pushup(int x)
	{
		f[x].minn=min(f[f[x].ls].minn,f[f[x].rs].minn);
	}
	int build(int l,int r)
	{
		int cur=++node_cnt;
		f[cur]={0,0,0};
		if(l==r) return cur;
		int mid=(l+r)>>1;
		f[cur].ls=build(l,mid);
		f[cur].rs=build(mid+1,r);
		return cur;
	}
	void Update(int pos,int val,int l,int r,int cur)
	{
		if(l==r)
		{
			f[cur].minn+=val;
			return;
		}
		int mid=(l+r)>>1;
		if(pos<=mid) Update(pos,val,l,mid,f[cur].ls);
		else Update(pos,val,mid+1,r,f[cur].rs);
		pushup(cur);
	}
	int Query(int C,int l,int r,int cur)
	{
		if(l==r) return l;
		int mid=(l+r)>>1;
		if(f[f[cur].ls].minn<=C) return Query(C,l,mid,f[cur].ls);
		return Query(C,mid+1,r,f[cur].rs);
	}
}tr;
void init()
{
	ans=0;
	tr.node_cnt=0;
	tr.build(1,n);
}
void Update(int x)
{
	int pos=tr.Query(C-x,1,n,1);
	if(pos>ans) ++ans;
	tr.Update(pos,x,1,n,1);
}
}
namespace sub2
{
int ans;
std::multiset<int> S;
void init()
{
	ans=0;
	S.clear();
}
void Update(int x)
{
	auto it=S.upper_bound(C-x);
	if(it==S.begin())
	{
		++ans;
		S.insert(x);
	}
	else
	{
		--it;
		int val=*it;
		S.erase(it);
		S.insert(val+x);
	}
}
}
void MAIN()
{
	scanf("%d %d",&n,&C);
	sub1::init();
	sub2::init();
	int x;
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&x);
		sub1::Update(x);
		sub2::Update(x);
	}
	printf("%d %d\n",sub1::ans,sub2::ans);
}
int main()
{
	int _;scanf("%d",&_);
	while(_--) MAIN();
	return 0;
}
