#include<bits/stdc++.h>
#define pi pair<int,int>
#define f first
#define s second
#define Chk(ax,ay) (1<=(ax)&&(ax)<=n&&1<=(ay)&&(ay)<=m&&c[ax][ay]=='1')
using namespace std;
const int N=30,L=1e6;
int w[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
char ch[4]={'R','L','D','U'};
int TT,n,m,fl,vis[N+5][N+5];
pi S,T,O;
int t[N+5][N+5],d[N+5][N+5];
pi u,v;
char c[N+5][N+5];
int prt[L+10],sz,p2[L+10],s2;
queue<pi>q;
void dfs(int x,int y){
	vis[x][y]=1;
	for(int i=0;i<4;++i)if(Chk(x+w[i][0],y+w[i][1])&&!vis[x+w[i][0]][y+w[i][1]])dfs(x+w[i][0],y+w[i][1]);
}
void bfs(pi x){
	for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)d[i][j]=-1;
	d[x.f][x.s]=0,q.push(x);
	while(!q.empty()){
		u=q.front(),q.pop();
		//cerr<<"BFS "<<u.f<<" "<<u.s<<"\n";
		for(int i=0;i<4;++i){
			v.f=u.f+w[i][0],v.s=u.s+w[i][1];
			if(Chk(v.f,v.s)&&d[v.f][v.s]==-1){
				d[v.f][v.s]=d[u.f][u.s]+1,t[v.f][v.s]=i^1;
				//cerr<<"T "<<v.f<<" "<<v.s<<"="<<(i^1)<<"\n";
				q.push((pi){v.f,v.s});
			}
		}
	}
}
pi Go(pi a,int wy){
	return Chk(a.f+w[wy][0],a.s+w[wy][1])?(pi){a.f+w[wy][0],a.s+w[wy][1]}:a;
}
void Path(pi a,pi b){
	//cerr<<"PATH ("<<a.f<<","<<a.s<<") ("<<b.f<<","<<b.s<<")\n";
	int tw;
	while(a!=O||b!=O){
		if(b==O)swap(a,b);
		tw=t[b.f][b.s],prt[++sz]=tw;
		//cerr<<"TW="<<tw<<"\n";
		a=Go(a,tw),b=Go(b,tw);
	}
}
void Walk(int x,int y){
	//cerr<<"WLK "<<x<<" "<<y<<"\n";
	vis[x][y]=1;
	for(int i=0;i<4;++i)if(Chk(x+w[i][0],y+w[i][1])&&!vis[x+w[i][0]][y+w[i][1]]){
		p2[++s2]=i;
		Walk(x+w[i][0],y+w[i][1]);
		p2[++s2]=i^1;
	}
}
int main(){
	cin.sync_with_stdio(0),cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i)cin>>c[i]+1;
	for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)vis[i][j]=0;
	cin>>S.f>>S.s>>T.f>>T.s;
	sz=0;
	fl=0;
	for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)if(c[i][j]=='1'&&!vis[i][j]){
		if(!fl)fl=1,dfs(i,j),O=(pi){i,j};
		else return cout<<"-1",0;
	}
	//cerr<<"?\n";
	bfs(O);
	for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)if(c[i][j]=='1'&&(i!=O.f||j!=O.s))Path(O,(pi){i,j});
	//cerr<<"?\n";
	bfs(T);
	int tw;
	while(O!=T){
		tw=t[O.f][O.s];
		prt[++sz]=tw;
		O=Go(O,tw);
	}
	for(int i=sz;i>0;--i)S=Go(S,prt[i]);
	for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)vis[i][j]=0;
	s2=0;
	//cerr<<"S="<<S.f<<","<<S.s<<"\n";
	Walk(S.f,S.s);
	for(int i=sz;i>=1;--i)cout<<ch[prt[i]];
	//cerr<<"\n";
	for(int i=1;i<=s2;++i)cout<<ch[p2[i]];
	//cerr<<"\n";
	for(int i=s2;i>=1;--i)cout<<ch[p2[i]];
	//cerr<<"\n";
	for(int i=1;i<=sz;++i)cout<<ch[prt[i]];
	return 0;
}
/*
5 5
11111
10101
11111
10101
11111
1 4 5 5

2 3
111
111
1 2 2 3

2 2
10
01
1 1 2 2
*/