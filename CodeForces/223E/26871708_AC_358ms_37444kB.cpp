#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=1e5+10;
int n,m,vis[N];
std::vector<int> G[N],f[N],s[N];
std::map<int,int> F[N];
struct node{
	int x,y;
	inline node operator-(const node &rhs)const{return node{x-rhs.x,y-rhs.y};}
	inline bool operator<(const node &rhs)const{return atan2(y,x)<atan2(rhs.y,rhs.x);}
	inline long long operator*(const node &rhs)const{return (long long)x*rhs.y-(long long)y*rhs.x;}
}a[N];
inline int calc(int u,int l,int r){
	l=F[u][l],r=F[u][r];
	// printf("calc %d %d %d [%d] => %d\n",u,l,r,G[u].size(),s[u][r]-(l?s[u][l-1]:0)+(l<=r?0:s[u].back()));
	return s[u][r]-(l?s[u][l-1]:0)+(l<=r?0:s[u].back());
}
void dfs(int u){
	int i,j,v;
	vis[u]=1,f[u].resize(G[u].size());
	for(i=0;i<G[u].size();i++)if(!vis[v=G[u][i]]){
		dfs(v),f[u][i]=1;
		for(j=0;j<G[v].size();j++)f[u][i]+=f[v][j];
		for(j=0;j<G[v].size();j++)if(G[v][j]==u)f[v][j]=-f[u][i];
	}
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	int i,j,t,k,p=1,u,v,q,ans; std::vector<int> vec;
	read(n),read(m);
	for(i=1;i<=m;i++)read(u),read(v),G[u].push_back(v),G[v].push_back(u);
	for(i=1;i<=n;i++)read(a[i].x),read(a[i].y);
	for(i=1;i<=n;i++)if(a[i].x<a[p].x||(a[i].x==a[p].x&&a[i].y<a[p].y))p=i;
	G[0].push_back(p),G[p].push_back(0),a[0].x=a[0].y=-1e9-10;
	for(i=0;i<=n;i++){
		std::vector<std::pair<node,int>> e(G[i].size());
		for(j=0;j<e.size();j++)e[j]=std::make_pair(a[G[i][j]]-a[i],G[i][j]);
		for(std::sort(e.begin(),e.end()),j=0;j<e.size();j++)G[i][j]=e[j].second,F[i][G[i][j]]=j;
	}
	dfs(0);
	for(i=0;i<=n;i++)for(s[i].resize(G[i].size()),s[i][0]=f[i][0],j=1;j<G[i].size();j++)s[i][j]=s[i][j-1]+f[i][j];
	// for(i=1;i<=n;i++)for(j=0;j<G[i].size();j++)printf("%d->%d:%d\n",i,G[i][j],f[i][j]);
	for(read(q),t=1;t<=q;t++){
		for(read(k),vec.resize(k),i=0;i<k;i++)read(vec[i]);
		for(p=0,i=0;i<k;i++)if(a[vec[i]].x<a[vec[p]].x||(a[vec[i]].x==a[vec[p]].x&&a[vec[i]].y<a[vec[p]].y))p=i;
		if((a[vec[(p+1)%k]]-a[vec[p]])*(a[vec[p]]-a[vec[(p+k-1)%k]])>0)std::reverse(vec.begin(),vec.end());
		ans=calc(vec[0],vec[k-1],vec[1])+calc(vec[k-1],vec[k-2],vec[0]);
		for(j=1;j+1<vec.size();j++)ans+=calc(vec[j],vec[j-1],vec[j+1]);
		printf("%d\n",-ans);
	}
}