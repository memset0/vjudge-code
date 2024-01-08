#include <bits/stdc++.h>
#include <queue>
using namespace std;
typedef long long ll;
bool umin(ll& a,ll t){if(t<a)return a=t,1;return 0;}

const int MAXN = 400011;
struct edge{int v,w,nxt;}e[MAXN<<1|1];
int cnt=1,last[MAXN];
void adde(int u,int v,int w){
	e[++cnt].v=v,e[cnt].w=w;
	e[cnt].nxt=last[u],last[u]=cnt;
}

std::vector<int>a[MAXN];
int dk[MAXN],dn[MAXN];
void bfs(int* dep,int s,int n){
	static int Q[MAXN];
	int h=0,t=0;
	Q[t++]=s,dep[s]=1;
	while(h<t)
	{
		int u=Q[h++];
		for(auto v:a[u])
			if(!dep[v])dep[v]=dep[u]+1,Q[t++]=v;
	}
	for(int u=1;u<=n;++u)--dep[u];
}
struct node{
	int u;ll dis;
	node(){}
	node(int _u,ll _dis){u=_u,dis=_dis;}
	bool operator<(const node& you)const{return dis>you.dis;}
};
std::priority_queue<node>Q;
ll dis[MAXN],f[MAXN];
void Dij(int s)
{
	memset(dis,0x3f,sizeof dis);
	dis[s]=0,Q.push(node(s,0));
	while(Q.size())
	{
		node tp=Q.top();Q.pop();
		int u=tp.u;
		if(dis[u]!=tp.dis)continue;
		for(int i=last[u];i;i=e[i].nxt)
		{
			int v=e[i].v,w=e[i].w;
			if(umin(dis[v],dis[u]+w))Q.push(node(v,dis[v]));
		}
	}
}
int main(){
#ifdef memset0
	freopen("I.in","r",stdin);
#endif
	std::cin.tie(0)->sync_with_stdio(0);
	int n,m,k,d;
	cin>>n>>m>>k>>d;
	for(int i=1;i<=m;++i)
	{
		int u,v;
		cin>>u>>v;
		a[u].emplace_back(v),a[v].emplace_back(u);
	}
	bfs(dn,n,n),bfs(dk,k,n);
	for(int u=1;u<=n;++u)
		for(auto v:a[u])
			if(dk[v]<d)adde(u,v,d-dk[v]);
	Dij(1);
	f[0]=d;
	for(int i=1;i<=n;++i)
		f[i]=f[i-1]+(d-i%d);
	ll ans=dis[n];
	for(int v:a[1])
		if(dk[v]>=d){
			umin(ans,f[dn[v]]);
		}
	for(int u=1;u<=n;++u)
		for(auto v:a[u])
			if(dk[v]>=d)
				umin(ans,dis[u]+f[dn[v]]);
	cout<<ans<<endl;
	return 0;
}