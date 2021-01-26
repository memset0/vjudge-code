#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=100;
int T,n,m,s,e,ans,lst,cnt,sum,nosol;
int c[N],q[N],k[N],d[N],fa[N],inq[N],dis[N],val[N],cnq[N],pre[N],l[N][N],r[N][N],w[N][N];
std::vector<int> G[N];
struct edge{int u,v,w,c,i,fl;}; std::vector<edge> E;
bool spfa(int s,int e){
	memset(dis,-1,(e+1)<<2),memset(cnq,0,(e+1)<<2);
	int l=1,r=1; q[1]=s,dis[s]=val[s];
	while(l<=r){
		int u=q[(l++)%N]; inq[u]=1;
		for(int v:G[u])if(!~dis[v]||dis[v]<dis[u]+val[v]){
			dis[v]=dis[u]+val[v],pre[v]=u;
			if(!inq[v]){
				inq[v]=1,q[(++r)%N]=v;
				if(++cnq[v]>=n)return false;
			}
		}
	}
	return true;
}
inline int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
bool checkout1(){
	printf("> check out 1\n");
	for(int i=1;i<=n+1;i++)fa[i]=i;
	for(const auto &it:E)if(!it.fl)fa[find(it.u)]=it.v;
	for(int i=2;i<=n+1;i++)if(find(i)!=find(1))return false;
	return true;
}
bool checkout2(){
	printf("> check out 2\n");
	int cnt=0;
	for(int i=1;i<=m;i++)d[i]=0;
	for(const auto &it:E)++d[it.c];
	for(int i=1;i<=m;i++)if(d[i]>c[i]-k[i])return false;
	return true;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	for(read(T);T--;sum=ans=nosol=0){
		read(n),read(m),s=cnt=1;
		for(int i=1;i<=m;i++){
			read(c[i]),read(k[i]),lst+=c[i]-k[i];
			for(int j=1;j<=c[i];j++){
				read(l[i][j]),read(r[i][j]),read(w[i][j]),sum+=w[i][j];
				E.push_back((edge){l[i][j],r[i][j]+1,w[i][j],i,++cnt});
			}
		}
		e=++cnt;
		std::cout<<s<<" "<<e<<std::endl;
		for(int i=1;i<=lst;i++){
			for(int i=1;i<=cnt;i++)G[i].clear();
			for(auto &it:E)if(!it.fl){
				val[it.i]=it.w,it.fl^=1;
				if(checkout1())G[s].push_back(it.i);
				if(checkout2())G[it.i].push_back(e);
				it.fl^=1;
			}else val[it.i]=-it.w;
			std::cerr<<">>> "<<i<<std::endl;
			for(auto &x:E)if(x.fl)
				for(auto &y:E)if(!y.fl){
					x.fl^=1,y.fl^=1;
					if(checkout1())G[x.i].push_back(y.i);
					if(checkout2())G[y.i].push_back(x.i);
					x.fl^=1,y.fl^=1;
				}
			if(!spfa(s,e)){nosol=true,puts("-1");break;}
			for(int u=pre[e];u!=e;u=pre[u]){
				E[u-1].fl^=1,ans+=val[u];
			}
		}
		if(!nosol)print(ans,'\n');
	}
}