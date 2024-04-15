#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
const int maxn=1E6+5;
const int limit=1000000;
int f,m,n,ans[maxn];
int totF;
struct line
{
	int l,r,x,id,type;
	bool operator<(const line&A)const
	{
		return x>A.x;
	}
}bar[maxn*2],flo[maxn],cow[maxn];
namespace SEG
{
	int t[maxn*4];
	bool tag[maxn*4];
	inline void put(int num)
	{
		t[num]=0;
		tag[num]=1;
	}
	inline void pushdown(int num)
	{
		if(tag[num])
		{
			tag[num]=0;
			put(num<<1),put(num<<1|1);
		}
	}
	inline void pushup(int num)
	{
		t[num]=t[num<<1]+t[num<<1|1];
	}
	void fill(int L,int R,int l,int r,int num)
	{
		if(L<=l&&r<=R)
		{
			put(num);
			return;
		}
		int mid=(l+r)>>1;
		pushdown(num);
		if(R<=mid)
			fill(L,R,l,mid,num<<1);
		else if(mid<L)
			fill(L,R,mid+1,r,num<<1|1);
		else
			fill(L,R,l,mid,num<<1),fill(L,R,mid+1,r,num<<1|1);
		pushup(num);
	}
	inline void change(int l,int r,int pos,int x,int num)
	{
		if(l==r)
		{
			t[num]+=x;
			return;
		}
		int mid=(l+r)>>1;
		pushdown(num);
		if(pos<=mid)
			change(l,mid,pos,x,num<<1);
		else
			change(mid+1,r,pos,x,num<<1|1);
		pushup(num);
	}
	int ask(int L,int R,int l,int r,int num)
	{
		if(L<=l&&r<=R)
			return t[num];
		int mid=(l+r)>>1;
		pushdown(num);
		if(R<=mid)
			return ask(L,R,l,mid,num<<1);
		else if(mid<L)
			return ask(L,R,mid+1,r,num<<1|1);
		return ask(L,R,l,mid,num<<1)+ask(L,R,mid+1,r,num<<1|1);
	}
}
multiset<int>ban;// !!!!!!!
inline pii getR(int pos)
{
	set<int>::iterator pt=ban.lower_bound(pos);
	int r=*pt;
	--pt;
	return pii(*pt,r);
}
inline int getA(int pos)
{
	if(pos<1||pos>limit)
		return 0;
	pii R=getR(pos);
	return SEG::ask(pos,R.second,1,limit,1);
}
int tmp[maxn];
inline void solve()
{
	ban.insert(0),ban.insert(limit+1);
	sort(bar+1,bar+totF+1);
	sort(flo+1,flo+m+1);
	sort(cow+1,cow+n+1);
	int pB=1,pF=1,pC=1;
	for(int pos=limit+1;pos>=1;--pos)// PLUS 1 !!!!!!!
	{
		while(flo[pF].x==pos)
		{
			SEG::change(1,limit,flo[pF].l,1,1);
			++pF;
		}
		while(cow[pC].x==pos)
		{
			ans[cow[pC].id]=getA(cow[pC].l);
			++pC;
		}
		vector<pii>tmp1;// delta
		vector<pii>tmp2;// clear
		vector<int>B1,B2;
		while(bar[pB].x==pos)
		{
			int l=bar[pB].l,r=bar[pB].r;
//			cout<<"FUCK "<<pB<<" "<<bar[pB].type<<" "<<pos<<endl;
			if(bar[pB].type==1)
			{
//				cerr<<"WHY "<<l<<" "<<r<<" "<<getA(l)<<endl;
				if(l-1)
					tmp1.push_back(pii(l-1,getA(l)));
				tmp2.push_back(pii(l,r));
				tmp[bar[pB].id]=getA(r+1);
				B1.push_back(l-1),B1.push_back(r);
			}
			else
			{
//				cout<<"?!?! "<<tmp[bar[pB].id]<<endl;
				if(l-1)
					tmp1.push_back(pii(l-1,-tmp[bar[pB].id]));
				tmp2.push_back(pii(l,r));
				B2.push_back(l-1),B2.push_back(r);
			}
			++pB;
		}
		for(int i=0;i<tmp1.size();++i)
			SEG::change(1,limit,tmp1[i].first,tmp1[i].second,1);
		for(int i=0;i<tmp2.size();++i)
			SEG::fill(tmp2[i].first,tmp2[i].second,1,limit,1);
		for(int i=0;i<B1.size();++i)
		{
			int x=B1[i];
			if(1<=x&&x<=limit)
				ban.insert(x);
		}
		for(int i=0;i<B2.size();++i)
		{
			int x=B2[i];
			if(1<=x&&x<=limit)
				ban.erase(ban.find(x));
		}
	}
}
int main()
{
//	freopen("6.in","r",stdin);
//	freopen("a.out","w",stdout);
	ios::sync_with_stdio(false);
	cin>>f;
	for(int i=1;i<=f;++i)
	{
		int r1,c1,r2,c2;
		cin>>r1>>c1>>r2>>c2;
		bar[++totF]=(line){r1,r2,c1,i,-1};
		bar[++totF]=(line){r1,r2,c2+1,i,1};
	}
	cin>>m;
	for(int i=1;i<=m;++i)
		cin>>flo[i].l>>flo[i].x;
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		cin>>cow[i].l>>cow[i].x;
		cow[i].id=i;
	}
	solve();
	for(int i=1;i<=n;++i)
		cout<<ans[i]<<'\n';
	return 0;
}
