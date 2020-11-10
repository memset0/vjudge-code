#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;
const int inf=0x3f3f3f3f;
#define N 155
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    return x*f;
}
namespace Maxflow{
	int cnt,S,T,dep[N],head[N],pre[N];
	struct Edge{
		int to,nxt,val;
	}edge[N*N<<1];
	void Clear(){
		memset(head,0,sizeof(head));
		cnt=1;
	}
	void add(int a,int b,int c){
		edge[++cnt]={b,head[a],c};
		head[a]=cnt;
	}
	void adde(int a,int b,int c){
		add(a,b,c),add(b,a,0);
	}
	queue<int> q;
	bool bfs(){
		memset(dep,0,sizeof(dep));
		dep[S]=1;
		q.push(S);
		while(!q.empty()){
			int u=q.front();
			q.pop();
			for(int i=head[u];i;i=edge[i].nxt){
				int v=edge[i].to;
				if(edge[i].val&&!dep[v]){
					dep[v]=dep[u]+1;
					q.push(v);
				}
			}
		}
		return dep[T]>0;
	}
	int dfs(int u,int limit){
		if(u==T)return limit;
		int flow=0;
		for(int &i=head[u];i;i=edge[i].nxt){
			int v=edge[i].to;
			if(dep[v]==dep[u]+1&&edge[i].val){
				int k=dfs(v,min(limit,edge[i].val));
				edge[i].val-=k;
				edge[i^1].val+=k;
				flow+=k;
				limit-=k;
			}
			if(!limit)break;
		}
		if(!flow)dep[u]=inf;
		return flow;
	}
	int Dinic(){
		memcpy(pre,head,sizeof(head));
		int maxflow=0;
		while(bfs()){
			maxflow+=dfs(S,inf);
			memcpy(head,pre,sizeof(head));
		}
		return maxflow;
	}
	bool vis[N];
	void dfs(int u){
		vis[u]=true;
		for(int i=head[u];i;i=edge[i].nxt){
			int v=edge[i].to;
			if(edge[i].val&&!vis[v])dfs(v);
		}
	}
	void Plan(){
		memset(vis,false,sizeof(vis));
		dfs(S);
	}
}
int n,D;
vector<int> ans;
struct Point{
	int x,y;
	Point(int _x=0,int _y=0){x=_x,y=_y;}
	Point operator -(const Point b){
		return Point(x-b.x,y-b.y);
	}
	int operator %(const Point b){
		return x*b.y-y*b.x;
	}
}p[N];
inline int Dis(Point &a,Point &b){
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
inline bool Left(Point a,Point b){
	return a%b<0;
}
inline bool Para(Point a,Point b){
	return a%b==0;
}
void Solve(int a,int b){
	static int type[N];
	static vector<int> res;
	res.clear();
	int tot=0,lim=Dis(p[a],p[b]);
	Maxflow::Clear();
	Maxflow::S=a,Maxflow::T=b;
	res.push_back(a),res.push_back(b);
	for(int i=1;i<=n;++i){
		type[i]=-1;
		if(i==a||i==b)continue;
		if(Dis(p[a],p[i])>lim||Dis(p[b],p[i])>lim)continue;
		
		if(Para(p[i]-p[a],p[b]-p[a])){
			res.push_back(i);continue;
		}
		
		type[i]=Left(p[i]-p[a],p[b]-p[a]);
	}
	for(int i=1;i<=n;++i){
		if(!~type[i])continue;
		type[i]==0?Maxflow::adde(a,i,1):Maxflow::adde(i,b,1);
	}
	for(int i=1;i<=n;++i){
		if(!~type[i])continue;
		for(int j=i+1;j<=n;++j){
			if(!~type[j])continue;
			if(type[i]^type[j]){
				if(Dis(p[i],p[j])>lim){
					type[i]==0?Maxflow::adde(i,j,1):Maxflow::adde(j,i,1);
				}
			}
		}
	}
	Maxflow::Dinic();
	Maxflow::Plan();
	for(int i=1;i<=n;++i){
		if(!~type[i])continue;
		if(type[i]^Maxflow::vis[i])res.push_back(i);
	}
	if(res.size()>ans.size()){
		ans=res;
	}
}
int main(){
	while(~scanf("%d %d",&n,&D)){
		for(int i=1;i<=n;++i){
			p[i].x=read(),p[i].y=read();
		}
		ans.clear();
		ans.push_back(1);
		for(int i=1;i<=n;++i){
			for(int j=i+1;j<=n;++j){
				if(Dis(p[i],p[j])<=D*D){
					Solve(i,j);
				}
			}
		}
		printf("%d\n",(int)ans.size());
		for(auto x:ans){
			printf("%d ",x);
		}
		printf("\n");
	}
	return 0;
}