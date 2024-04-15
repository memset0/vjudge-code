#include "bits/stdc++.h"
typedef long long ll;
using namespace std;
typedef std::pair<int,int> pii;
const int MAXN = 200011;
std::vector<int>g[MAXN];
std::vector<pii>tong,duan,chang,ans;
int type[MAXN],fa[MAXN],dep[MAXN];
int r[MAXN];
void fail()
{
	std::cout<<"NO"<<std::endl;
	exit(0);
}
void dfs(int u,int d)
{
	dep[u]=d;
	for(auto v:g[u])dfs(v,d+1);
	tong.clear(),duan.clear(),chang.clear();
	for(auto v:g[u])
		if(type[r[v]]==1)tong.emplace_back(pii(dep[r[v]],r[v]));
		else if(type[r[v]]==2)duan.emplace_back(pii(dep[r[v]],r[v]));
		else if(type[r[v]]==3)chang.emplace_back(pii(dep[r[v]],r[v]));
	if(type[u]==1)tong.emplace_back(pii(dep[u],u));
	else if(type[u]==2)duan.emplace_back(pii(dep[u],u));
	else if(type[u]==3)chang.emplace_back(pii(dep[u],u));
	sort(tong.begin(),tong.end());
	std::sort(duan.begin(),duan.end()),std::sort(chang.begin(),chang.end());
	//printf("Enter u=%d\n",u);
    r[u]=0;
	for(int i=0;i<tong.size();++i)
    {
        if(i+1<tong.size()&&tong[i].first==tong[i+1].first)
        {
            ans.emplace_back(pii(tong[i].second,tong[i+1].second));
            ++i;continue;
        }
        if(!r[u])r[u]=tong[i].second;
        else fail();
    }
	//puts("ok!");
	int na=duan.size(),nb=chang.size(),flag=0;
	if(na>nb)flag=1;
	else flag=0;
	//printf("Na=%d,Nb=%d\n",na,nb);
	if(flag)
	{
		int it=nb-1;
		for(int i=na-1;i>=0;--i)
		{
			if(it>=0&&duan[i].first<chang[it].first)
			{
				ans.emplace_back(pii(duan[i].second,chang[it].second));
				--it;continue;
			}
			if(!r[u])r[u]=duan[i].second;
			else fail();
		}
        while(it>=0)
        {
            if(!r[u])r[u]=chang[it].second;
            else fail();
            --it;
        }
	}
	else
	{
		int it=0;
		for(int i=0;i<nb;++i)
		{
			if(it<na&&duan[it].first<chang[i].first)
			{
				ans.emplace_back(pii(duan[it].second,chang[i].second));
				++it;continue;
			}
			if(!r[u])r[u]=chang[i].second;
			else fail();
		}
        while(it<na)
        {
            if(!r[u])r[u]=duan[it].second;
            else fail();
            ++it;
        }
	}
	//printf("Quit %d,sz=%d,r=%d\n",u,int(ans.size()),r[u]);
}
int main()
{
#ifdef memset0
	freopen("C.in","r",stdin);
#endif
	cin.tie(0)->sync_with_stdio(0);
	int n;
	std::cin>>n;
	for(int i=2;i<=n;++i)
	{
		int u;
		string tp;
		cin>>u>>fa[u]>>tp;
		if(tp=="Tong")type[u]=1;
		else if(tp=="Duan")type[u]=2;
		else if(tp=="Chang")type[u]=3;
		g[fa[u]].emplace_back(u);
	}
	dfs(1,1);
	if(r[1])fail();
	cout<<"YES\n";
	for(auto P:ans)cout<<P.first<<" "<<P.second<<"\n";
	return 0;
}