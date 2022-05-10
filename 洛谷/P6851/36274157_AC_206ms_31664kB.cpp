#include<bits/stdc++.h>
#define rep(i,a,b) for (register int i=(a);i<=(b);i++)
#define drep(i,a,b) for (register int i=(a);i>=(b);i--)
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
inline ll read()
{
	ll sum=0,f=0;char c=getchar();
	while (!isdigit(c)) f|=(c=='-'),c=getchar();
	while (isdigit(c)) sum=(sum<<1)+(sum<<3)+(c^48),c=getchar();
	return f?-sum:sum;
}
const int N=100010;
ll n,m,c,v,maxx,ans[N];
struct card{ll id,col,val;bool operator < (const card &a) const {return val<a.val;}}p1[N],p2[N];
inline bool cmpval(card a,card b){return a.val<b.val;}
priority_queue<card>q1[N],q2[N];
vector<card>v1[N],v2[N];
inline ll cl(ll i,ll j)
{
	int res=0;
	if (p1[i].val>=p2[j].val) res+=c;
	else res-=c;
	res+=p1[i].val;
	return res;
}
inline ll calc()
{
	ll Ans=0;
	rep(i,1,m)
	{
		if (ans[i]==0) ans[i]=-1;
		if (ans[i]!=-1) Ans+=cl(ans[i],i);
		if (ans[i]==-1) Ans-=c;
	}
	return Ans;
}
signed main()
{
	n=read(),m=read(),c=read(),v=read(),maxx=100000;
	rep(i,1,n) p1[i].id=i,p1[i].col=read(),p1[i].val=read();
	rep(i,1,m) p2[i].id=i,p2[i].col=read(),p2[i].val=read();
	rep(i,1,n) q1[p1[i].col].push(p1[i]);
	rep(i,1,m) q2[p2[i].col].push(p2[i]);
	rep(i,1,n) v1[p1[i].col].push_back(p1[i]);
	rep(i,1,m) v2[p2[i].col].push_back(p2[i]);
	rep(i,1,maxx) if (q2[i].size())
	{
		while (q2[i].size())
		{
			if (!q1[i].size())
			{
				while (q2[i].size()) ans[q2[i].top().id]=-1,q2[i].pop();
				break;
			}
			if (q1[i].top().val>=q2[i].top().val)
			{
				ans[q2[i].top().id]=q1[i].top().id;
				q1[i].pop();
			}
			else ans[q2[i].top().id]=-1;
			q2[i].pop();
		}
		int tmp=0;
		while (q1[i].size())
		{
			if (tmp>=v2[i].size()) break;
			if (ans[v2[i][tmp].id]==-1||ans[v2[i][tmp].id]==0)
			{
				ans[v2[i][tmp].id]=q1[i].top().id;
				q1[i].pop();
			}
			tmp++;
		}
	}
	printf("%lld\n",calc()+v);
	rep(i,1,m) printf("%lld\n",ans[i]!=0?ans[i]:-1);
}