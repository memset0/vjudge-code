// 写一半咕咕咕了

#include<bits/stdc++.h>
#define log(...) (void(0))
// #define log(...) fprintf(stderr,__VA_ARGS__)
#define debug log("\33[2mPassing [%s] in LINE %d\33[0m\n",__FUNCTION__,__LINE__);

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
int n,m,rt,ful,fa[N],val[N],vis[N],siz[N],mxp[N],srt[N];
std::vector<int> G[N];
std::vector<std::pair<int,int>> tmp[N],dis[N];

struct bit:std::vector<int>{
	using std::vector<int>::vector;
#ifdef memset0
	int id;
	inline const char* vname(){
		return ((std::string)"bit"+(id<=n?"A":"B")+"["+std::to_string(id<=n?id:id-n)+"]").c_str();
	}
#endif
	inline void add(int k,int v){
		log("%s add %d %d\n",vname(),k,v);
		++k;
		for(;k<=size();k+=k&-k)this->operator[](k-1)+=v;
	}
	inline int qry(int k){
		log("%s qry %d\n",vname(),k);
		int s=0; k=std::min((int)size(),++k);
		for(;k;k-=k&-k)s+=this->operator[](k-1);
		return s;
	}
}tr1[N],tr2[N];

void findroot(int u,int fa){
	siz[u]=1,mxp[u]=0;
	for(int v:G[u])if(!vis[v]&&v!=fa){
		findroot(v,u);
		siz[u]+=siz[v];
		mxp[u]=std::max(mxp[u],siz[v]);
	}
	mxp[u]=std::max(mxp[u],ful-siz[u]);
	if(mxp[u]<mxp[rt])rt=u;
}

void dfs(int u,int fa,int dis,int src){
	tmp[src].push_back(std::make_pair(u,dis));
	for(int v:G[u])if(!vis[v]&&v!=fa){
		dfs(v,u,dis+1,src);
	}
}

void buildtree(int u){
	log("\e[33mbuildtree %d\e[0m\n",u);
	int mx1=0,mx2=0;
	vis[u]=1;
	dis[u].push_back(std::make_pair(u,0));
	std::reverse(dis[u].begin(),dis[u].end());
	for(int v:G[u])if(!vis[v]){
		// 寻找点分树叶子节点
		mxp[rt=0]=ful=siz[u];
		findroot(v,u);
		srt[v]=rt;
		// 点分治
		mx2=0,tmp[v].clear();
		dfs(v,0,1,v);
		for(auto x:tmp[v]){
			mx1=std::max(mx1,x.second);
			mx2=std::max(mx2,x.second);
		}
		tr2[srt[v]].resize(mx2);
		for(auto x:tmp[v]){
			tr2[srt[v]].add(x.second,val[x.first]);
			dis[v].push_back(std::make_pair(srt[v],x.second));
		}
	}
	tr1[u].resize(mx1);
	tr1[u].add(0,val[u]);
	for(int v:G[u])
		for(auto x:tmp[v]){
			tr1[u].add(x.second,val[x.first]);
		}
	for(int v:G[u])if(!vis[v]){
		fa[srt[v]]=u;
		log("%d -> %d %d\n",u,v,srt[v]);
		buildtree(srt[v]);
	}
}

int query(int x,int y){
	int ans=0;
	for(auto it:dis[x]){
		ans+=tr1[x].qry(y);
		if(x!=it.first)ans-=tr2[it.first].qry(y);
		x=fa[x];
		if((y-=it.second)<0)break;
	}
	return ans;
}

void modify(int x,int y){
	for(auto it:dis[x]){
		tr1[x].add(it.second,y);
		if(x!=it.first)tr2[it.first].add(it.second,y);
		x=fa[x];
	}
}

void modify(int u,int w){
	for(auto it:dis[u]){
		tr1[u].add(it.second,y);
	}
}

int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(m);
	for(int i=1;i<=n;i++)read(val[i]);
	for(int i=1,u,v;i<n;i++){
		read(u),read(v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
#ifdef memset0
	for(int i=1;i<=n;i++){
		tr1[i].id=i;
		tr2[i].id=i+n;
	}
#endif
	mxp[rt=0]=ful=n;
	findroot(1,0);
	buildtree(rt);
	for(int i=1,o,x,y,ans=0;i<=m;i++){
		read(o),read(x),read(y);
		// x^=ans,y^=ans;
		log("\e[31m>> %d %d %d\e[0m\n",o,x,y);
		if(o){
			modify(x,y-val[x]),val[x]=y;
		}else{
			print(ans=query(x,y),'\n');
		}
	}
}