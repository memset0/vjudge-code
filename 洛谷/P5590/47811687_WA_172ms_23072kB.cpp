// nobfs2

#include<bits/stdc++.h>
template<class T>inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	if(f)x=-x;
}
template<class T>inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10+'0');
}
template<class T>inline void print(T x,char c){print(x),putchar(c);}
const int N=3e5+10;
bool fl[N],fl1[N],fl2[N],inq[N],ins[N];
int n,m,top,tim,cnt[N],dis[N],dfn[N],low[N],stk[N];
std::queue<int> q;
std::vector<int> G[N],Q[N];
std::vector<std::pair<int,int>> E,P[N];
void bfs(int s,bool *fl,std::vector<int> *G){
	q.push(s),fl[s]=1;
	while(q.size()){
		int u=q.front(); q.pop();
		for(int v:G[u])if(!fl[v])fl[v]=1,q.push(v);
	}
}
bool spfa(){
	q.push(1),dis[1]=0;
	while(q.size()){
		int u=q.front(); q.pop(),inq[u]=0;
		for(auto it:P[u]){
			int v=it.first,w=it.second;
			if(!~dis[v]||~dis[v]&&dis[v]<dis[u]+w){
				dis[v]=dis[u]+w;
				if(!inq[v]){
					// printf("%d -> %d [%d]\n",u,v,cnt[v]);
					q.push(v),inq[v]=1;
					if(++cnt[v]>=n)return false;
				}
			}
		}
	}
	return true;
}
bool tarjan(int u){
	dfn[u]=low[u]=++tim;
	for(int v:G[u])if(!dfn[v]){
		if(!tarjan(v)) return false;
		low[u]=std::min(low[u],low[v]);
	}else if(ins[v]){
		low[u]=std::min(low[u],dfn[v]);
	}
	return dfn[u]==low[u];
}
int main(){
// #ifdef memset0
// 	freopen("1.in","r",stdin);
// #endif
	read(n),read(m);
	for(int u,v,i=1;i<=m;i++){
		read(u),read(v);
		E.push_back(std::make_pair(u,v));
		G[u].push_back(v),Q[v].push_back(u);
	}
	bfs(1,fl1,G),bfs(n,fl2,Q);
	for(int i=1;i<=n;i++)fl[i]=true;
	for(auto it:E)if(fl[it.first]&&fl[it.second]){
		P[it.first].push_back(std::make_pair(it.second,1));
		P[it.second].push_back(std::make_pair(it.first,-9));
	}
	std::cerr<<"[std] "<<n<<" "<<m<<std::endl;
	print(n,' '),print(m,'\n');
	for(auto it:E)if(fl[it.first]&&fl[it.second]){
		print(it.first,' '),print(it.second,' '),print(dis[it.second]-dis[it.first],'\n');
	}else{
		print(it.first,' '),print(it.second,' '),print(1,'\n');
	}
}