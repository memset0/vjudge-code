#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=36,C=25;
const ll INF=1e18;
struct node{
	ll a,b;
	int id;
	bool operator<(const node&y)const{
		if((b-a>0)!=(y.b-y.a>0))return y.b-y.a>0;
		return b-a>0?(a!=y.a?a>y.a:(b!=y.b?b>y.b:id>y.id)):(b!=y.b?b<y.b:(a!=y.a?a<y.a:id<y.id));
	}
	bool operator==(const node&y)const{
		return a==y.a&&b==y.b&&id==y.id;
	}
}t;
struct PQ{
	priority_queue<node>pq,del;
	void push(node x){pq.push(x);}
	void erase(node x){del.push(x);}
	void pop(){
		while(!del.empty()&&pq.top()==del.top())pq.pop(),del.pop();
		pq.pop();
	}
	node top(){
		while(!del.empty()&&pq.top()==del.top())pq.pop(),del.pop();
		return pq.top();
	}
	void clr(){
		while(!pq.empty())pq.pop();
		while(!del.empty())del.pop();
	}
	int size(){return pq.size()-del.size();}
}p;
int n,m,u,v,nf[N+10],fa[N+10],tp;
ll a[N+10],b[N+10],na[N+10],nb[N+10],mx,dt,ans=INF;
ll lb[(1<<C)+10],ss[(1<<C)+10],dp[(1<<C)+10],to;
vector<int>f[N+10];
int getf(int x){
	return fa[x]==x?x:fa[x]=getf(fa[x]);
}
void dfs(int x){
	if(x>n){
		p.clr();
		na[1]=nb[1]=0,fa[1]=1;
		for(int i=2;i<=n;++i)fa[i]=i,p.push((node){a[i],b[i],i}),na[i]=a[i],nb[i]=b[i];
		while(p.size()){
			t=p.top(),p.pop();
			tp=getf(nf[t.id]);
			if(tp!=1)p.erase((node){na[tp],nb[tp],tp});
			mx=max(na[tp],na[tp]-nb[tp]+t.a);
			nb[tp]=nb[tp]+t.b-na[tp]-t.a+mx,na[tp]=mx;
			fa[t.id]=tp;
			if(tp!=1)p.push((node){na[tp],nb[tp],tp});
		}
		ans=min(ans,na[1]);
		return;
	}
	for(int i:f[x])nf[x]=i,dfs(x+1);
}
int main(){
	cin.sync_with_stdio(0),cin.tie(0);
	cin>>n>>m;
	for(int i=2;i<=n;++i)cin>>a[i]>>b[i];
	if(n>C){
		for(int i=1;i<=m;++i){
			cin>>u>>v,f[v].push_back(u);
		}
		dfs(2);
		cout<<ans<<"\n";
	}else{
		for(int i=1;i<=m;++i)cin>>u>>v,fa[v]|=(1<<u-1);
		for(int i=1;i<(1<<n);++i)lb[i]=((i&1)?0:lb[i>>1]+1),ss[i]=ss[i-(1<<lb[i])]-a[lb[i]+1]+b[lb[i]+1];
		for(int i=2;i<(1<<n);++i)dp[i]=INF;
		for(int i=1;i<(1<<n);i+=2){
			for(int j=2;j<=n;++j)if(!((i>>j-1)&1)&&(i&fa[j])){
				to=i+(1<<j-1);
				dp[to]=min(dp[to],max(dp[i],a[j]-ss[i]));
			}
		}
		cout<<dp[(1<<n)-1]<<"\n";
	}
	return 0;
}