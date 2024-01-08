#include "bits/stdc++.h"
typedef unsigned un;
typedef long long ll;
const int MAXN = 200011;
int n,m;
struct Segment_Tree
{
	#define rt t[num]
	#define tl t[num<<1]
	#define tr t[num<<1|1]
	int t[MAXN<<2|1];
	void set(un pos,int val,un l=1,un r=n,un num=1)
	{
		if(l==r){rt=val;return;}
		un mid=(l+r)>>1;
		if(pos<=mid)set(pos,val,l,mid,num<<1);
		else set(pos,val,mid+1,r,num<<1|1);
		rt=tl+tr;
	}
	void modify(un pos,int val,un l=1,un r=n,un num=1)
	{
		if(l==r){rt+=val;return;}
		un mid=(l+r)>>1;
		if(pos<=mid)modify(pos,val,l,mid,num<<1);
		else modify(pos,val,mid+1,r,num<<1|1);
		rt=tl+tr;
	}
	int query(un l=1,un r=n,un num=1)
	{
		if(l==r)return l;
		un mid=(l+r)>>1;
		if(tl)return query(l,mid,num<<1);
		else return query(mid+1,r,num<<1|1);
	}
}sgt;
std::vector<int>ins[MAXN],del[MAXN];
std::multiset<int>S;
int a[MAXN];
int main()
{
	std::ios::sync_with_stdio(0),std::cin.tie(0);
	int task;std::cin>>task;
	while(task--)
	{
		//puts("New:");
		std::cin>>n>>m;
		while(m--)
		{
			int l,r;std::cin>>l>>r;
			ins[l].emplace_back(l),del[r+1].emplace_back(l);
		}
		for(int i=1;i<=n;++i)sgt.set(i,1);
		int it=0;
		for(int i=1;i<=n;++i)
		{
			// printf("i=%d:",i);
			for(auto p:ins[i])S.insert(p);//,printf("ins %d\n",p);
			for(auto p:del[i])S.erase(S.find(p));//,printf("del %d\n",p);
			if(S.empty())
			{
				while(it+1<i)sgt.modify(a[++it],1);
				//printf("fir,it=%d\n",it);
			}
			else 
			{
				//printf("it=%d,*s=%d\n",it,*S.begin());
				while(it+1<*S.begin())sgt.modify(a[++it],1);
				//printf("sec,it=%d\n",it);
			}
			a[i]=sgt.query();
			//printf("A[%d]=%d\n",i,a[i]);
			sgt.modify(a[i],-1);
		}
		for(auto p:del[n+1])S.erase(S.find(p));
		for(int i=1;i<=n;++i)printf("%d ",a[i]);
		puts("");
		for(int i=0;i<=n+1;++i)ins[i].clear(),del[i].clear();
	}
	return 0;
}