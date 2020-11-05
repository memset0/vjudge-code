#include<bits/stdc++.h>
using namespace std;
const int N=310,V=N<<1,E=V*V;
int n,s,t,cnt,tot,m[N],ans[N],need[N],hed[V],val[E],to[E],nxt[E],dep[V],q[V],cur[V];
string d[N],l[N];
vector<int> vec[N][N],goal[N][N],fd[N],fl[N],f;
void runtime_assert(bool x){
	if(!x)throw true;
}
void move(vector<int> &vec,vector<int> &b){
	runtime_assert(vec.size());
	b.push_back(vec.back()),vec.pop_back();
}
void add(int u,int v){
	// cerr<<"add edge "<<u<<" "<<v<<endl;
	nxt[tot]=hed[u],to[tot]=v,val[tot]=1,hed[u]=tot++;
	nxt[tot]=hed[v],to[tot]=u,val[tot]=0,hed[v]=tot++;
}
int connect(int x){
	for(int i=hed[x];~i;i=nxt[i])
		if((x<=n?val[i^1]:val[i])&&to[i]!=s&&to[i]!=t)
			return to[i];
	return false;
}
void newgoal(int i,int j){
	++cnt;
	runtime_assert(cnt<=(n<<1));
	for(int x:f)add(x,cnt);
	for(int x:fd[i])add(x,cnt);
	for(int x:fl[j])add(x,cnt);
	goal[i][j].push_back(cnt);
}
bool bfs(){
	int u,l,r; memset(dep+1,0,t<<2),l=r=dep[s]=1,q[1]=s;
	while(l<=r&&(u=q[l++]))for(int i=hed[u];~i;i=nxt[i])
		if(val[i]&&!dep[to[i]])dep[to[i]]=dep[u]+1,q[++r]=to[i];
	return dep[t];
}
int dfs(int u,int d){
	if(u==t)return d; int s=0;
	for(int &i=cur[u];~i;i=nxt[i])if(val[i]&&dep[to[i]]==dep[u]+1)
		if(int e=dfs(to[i],std::min(d-s,val[i]))){s+=e,val[i]-=e,val[i^1]+=e;if(s==d)return s;}
	return s?s:dep[s]=0;
}
int dinic(){
	int r=0;
	while(bfs())memcpy(cur+1,hed+1,t<<2),r+=dfs(s,1e9);
	return r;
}
void solve(int top){
	tot=0,s=(n<<1)+1,t=(n<<1)+2,cnt=n,f.clear();
	memset(ans,0,sizeof(ans));
	memset(hed,-1,sizeof(hed));
	memset(need,-1,sizeof(need));
	for(int i=0;i<=n;i++)fl[i].clear(),fd[i].clear();
	for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)vec[i][j].clear(),goal[i][j].clear();
	for(int i=1;i<=n;i++){
		if(d[i]=="?"&&l[i]=="?")f.push_back(i);
		else if(d[i]=="?")fd[atoi(l[i].c_str())].push_back(i);
		else if(l[i]=="?")fl[atoi(d[i].c_str())].push_back(i);
		else vec[atoi(l[i].c_str())][atoi(d[i].c_str())].push_back(i);
	}
	for(int i=1;i<=n;i++){
		if(fd[i].size())need[i]=0;
		for(int j=0;j<=n;j++)if(vec[i][j].size())need[i]=0;
	}
	need[top]=0;
	for(int i=1;i<=n;i++)
		if(~need[i]){
			need[i]=vec[i][0].size();
			if(need[i]<i)need[i]=i-need[i];
			else need[i]=need[i]%i==0?0:i-need[i]%i;
		}
	// cerr<<m[6]<<" "<<need[6]<<endl;
	for(int i=1;i<=n;i++){
		m[i]=~need[i]?0:-1;
		for(int j=0;j<=n;j++)if(vec[i][j].size())m[i]=j;
	}
	int maxt=0;
	for(int i=1;i<=n;i++)if(fl[i].size())maxt=i;
	m[top]=std::max(m[top],maxt);
	for(int i=1;i<=n;i++)if(~need[i]){
		while(need[i]--)newgoal(i,0);
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m[i];j++){
			if(!vec[i][j].size())newgoal(i,j);
		}
	for(int i=1;i<=n;i++)add(s,i);
	for(int i=n+1;i<=cnt;i++)add(i,t);
	cerr<<"dinic="<<dinic()<<endl;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=m[i];j++)
			for(int x:goal[i][j]){
				runtime_assert(connect(x));
				vec[i][j].push_back(connect(x));
			}
	auto clear=[&](vector<int> &x){
		vector<int> t;
		for(int u:x)if(!connect(u))t.push_back(u);
		x.swap(t);
	};
	clear(f);
	for(int i=0;i<=n;i++)clear(fd[i]),clear(fl[i]);
	while(fl[0].size())move(fl[0],vec[1][0]);
	while(f.size())move(f,vec[1][0]);
	for(int j=1;j<=n;j++)while(fl[j].size())move(fl[j],vec[top][j]);
	for(int i=1;i<=n;i++)while(fd[i].size())move(fd[i],vec[i][1]);
	for(int i=1;i<=n;i++){
		runtime_assert((int)vec[i][0].size()%i==0);
		for(int j=0;j<vec[i][0].size();j+=i)
			for(int k=0;k<i;k++)
				ans[vec[i][0][j+k]]=vec[i][0][j+(k+1)%i];
		for(int j=1;j<=n;j++){
			runtime_assert(!vec[i][j].size()||vec[i][j-1].size());
			for(int k=0;k<vec[i][j].size();k++)
				ans[vec[i][j][k]]=vec[i][j-1][0];
		}
	}
	for(int i=1;i<=n;i++)runtime_assert(ans[i]);
	for(int i=1;i<=n;i++)cout<<ans[i]<<" \n"[i==n];
	exit(0);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	cin>>n;
	for(int i=1;i<=n;i++)cin>>d[i]>>l[i];
	for(int i=1;i<=n;i++)try{solve(i);}catch(bool e){cerr<<"fail:"<<i<<endl;}
	puts("-1");
}