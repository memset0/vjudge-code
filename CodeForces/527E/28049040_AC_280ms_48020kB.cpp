#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=1e5+10,M=5e5+10;
int n,m,cnt,lst[N],vis[M];
std::vector<int> q;
std::vector<std::pair<int,int>> r,G[N];
void connect(int u,int v){
	++cnt;
	G[u].push_back(std::make_pair(v,cnt));
	G[v].push_back(std::make_pair(u,cnt));
}
void dfs(int u){
	for(int &i=++lst[u];i<G[u].size();i++){
		int v=G[u][i].first,w=G[u][i].second;
		if(!vis[w])vis[w]=1,dfs(v),r.push_back(std::make_pair(u,v));
	}
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(m),memset(lst+1,-1,n<<2);
	for(int u,v,i=1;i<=m;i++)read(u),read(v),connect(u,v);
	for(int i=1;i<=n;i++)if(G[i].size()&1)q.push_back(i);
	for(int i=0;i<q.size();i+=2)connect(q[i],q[i|1]);
	dfs(1);
	if(r.size()&1)r.push_back(std::make_pair(1,1));
	for(int i=0;i<r.size();i+=2)std::swap(r[i].first,r[i].second);
	print(r.size(),'\n');
	for(auto it:r)print(it.first,' '),print(it.second,'\n');
}