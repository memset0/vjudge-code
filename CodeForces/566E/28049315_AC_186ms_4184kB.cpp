#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();if(f)x=-x;
}
const int N=1e3+10;
int n,m,vis[N],dis[N][N];
std::bitset<N> it,tag,a[N];
std::vector<int> tree,leaf,G[N];
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n);
	for(int t,x,i=1;i<=n;i++){
		read(t);
		for(int j=1;j<=t;j++)read(x),a[i].set(x);
	}
	for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)if((it=a[i]&a[j]).count()==2){
		int u=it._Find_first(),v=it._Find_next(u);
		if(find(G[u].begin(),G[u].end(),v)==G[u].end()){
			G[u].push_back(v),G[v].push_back(u),tag[u]=tag[v]=1;
		}
	}
	for(int u=1;u<=n;u++)for(int v:G[u])dis[u][v]=1;
	for(int i=1;i<=n;i++)for(int u:G[i])for(int v:G[i])if(u!=v)dis[u][v]=2;
	for(int i=1;i<=n;i++)(tag[i]?tree:leaf).push_back(i);
	if(leaf.size()==n){
		std::cerr<<"[1]"<<std::endl;
		for(int i=2;i<=n;i++)printf("1 %d\n",i);
	}else if(leaf.size()==n-2){
		std::cerr<<"[2]"<<std::endl;
		printf("%d %d\n",tree[0],tree[1]);
		for(int i=1;i<=n;i++)if(a[i].count()!=n){it=a[i];break;}
		for(int u:leaf)printf("%d %d\n",tree[it[u]],u);
	}else{
		std::cerr<<"[3]"<<std::endl;
		for(int u=1;u<=n;u++)for(int v:G[u])if(u<v)printf("%d %d\n",u,v);
		for(int i=1;i<=n;i++)if(!vis[i])for(int j=i+1;j<=n;j++){
			if(a[i]==a[j])vis[j]=1;
			else{
				if((a[i]&a[j])==a[i])vis[j]=1;
				if((a[i]&a[j])==a[j])vis[i]=1;
			}
		}
		for(int i=1;i<=n;i++)if(!vis[i]){
			std::vector<int> v; int rt;
			it=a[i]&tag;
			for(int i=it._Find_first();i!=N;i=it._Find_next(i))v.push_back(i);
			if(v.size()==2)rt=v[G[v[1]].size()==1];
			else for(int i=0;i<v.size();i++){
				if(dis[v[i]][v[(i+1)%v.size()]]!=1||dis[v[i]][v[(i+2)%v.size()]]!=1)continue;
				rt=v[i];break;
			}
			it=a[i]^(a[i]&tag);
			for(int i=it._Find_first();i!=N;i=it._Find_next(i))printf("%d %d\n",i,rt);
		}
	}
}