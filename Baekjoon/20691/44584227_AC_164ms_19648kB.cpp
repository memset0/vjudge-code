#include "bits/stdc++.h"
#include <algorithm>
typedef long long ll;
const int MAXN = 400011;
int fx[MAXN], diff;
int place(int val){return std::lower_bound(fx+1,fx+diff+1,val)-fx;}
struct BIT
{
	int t[MAXN];
	#define lowb (i&-i)
	void modify(int i,int k)
	{
		while(i<=diff)t[i]+=k,i+=lowb;
	}
	int Qsum(int i)
	{
		int res=0;
		while(i)res+=t[i],i-=lowb;
		return res;
	}
}bt,st;
std::vector<int>a,b[MAXN];
int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int n,m;
	std::cin>>n>>m;
	a.resize(n);
	for(int i=0;i<n;++i)std::cin>>a[i],fx[++diff]=a[i];
	for(int w=0;w<m;++w)
	{
		int sz;
		std::cin>>sz;
		b[w].resize(sz);
		for(int i=0;i<sz;++i)std::cin>>b[w][i],fx[++diff]=b[w][i];
	}
	std::sort(fx+1,fx+diff+1),diff=std::unique(fx+1,fx+diff+1)-fx-1;
	ll ex=0;
	for(int i=0;i<n;++i)
	{
		a[i]=place(a[i]);
		ex+=i-bt.Qsum(a[i]);
		bt.modify(a[i],1);
	}
	for(int w=0;w<m;++w)
		for(auto& p:b[w])p=place(p);
	for(int w=0;w<m;++w)
	{
		ll ans=1e18,cur=0,self=0;
		int sz=b[w].size();
		for(int i=0;i<sz;++i)
		{
			cur+=n-bt.Qsum(b[w][i]);
			self+=i-st.Qsum(b[w][i]);
			st.modify(b[w][i], 1);
		}
		ans=cur;
		for(int i=0;i<sz;++i)
		{
			cur-=n-bt.Qsum(b[w][i]);
			cur+=bt.Qsum(b[w][i]-1);
			ans=std::min(ans,cur);
			st.modify(b[w][i], -1);
		}
		printf("%lld\n",ans+ex+self);
	}
	return 0;
}