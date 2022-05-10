#include<bits/stdc++.h>
#define in(i,x) (((x)>>((i)-1))&1)
const int N=17,M=1<<16;
int n,m,k,S,fa[N],dis[N],f[M][N],g[M],h[N][M];
struct edge{
	int u,v,w;
	inline bool operator<(const edge &other)const{
		return w>other.w;
	}
};
std::vector<edge> G[N],E;
inline int popcount(int x){return __builtin_popcount(x);}
inline int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
inline int locate(int x,int y){
	int res=1000000000;
	for(int i=1;i<=n;i++)if(in(i,y))res=std::min(res,h[i][x]);
	return res;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#else
	// freopen("c.in","r",stdin),freopen("c.out","w",stdout);
#endif
	memset(f,-1,sizeof(f)),memset(g,-1,sizeof(g));
	std::cin>>n>>m>>k,S=(1<<n)-1;
	for(int u,v,w,i=1;i<=m;i++){
		std::cin>>u>>v>>w;
		E.push_back((edge){u,v,w});
		G[u].push_back((edge){u,v,w});
		G[v].push_back((edge){v,u,w});
	}
	std::sort(E.begin(),E.end());
	for(int x=0;x<(1<<n);x++){
		for(int i=1;i<=n;i++)h[i][x]=1000000000;
		for(int i=1;i<=n;i++)if(in(i,x)){
			for(auto it:G[i])h[it.v][x]=std::min(it.w,h[it.v][x]);
		}
	}
	for(int x=1,fl,sum;x<(1<<n);x++)if(popcount(x)){
		for(int i=1;i<=n;i++)if(in(i,x))fa[i]=i;
		fl=sum=0;
		for(auto it:E)if(in(it.u,x)&&in(it.v,x)&&find(it.u)!=find(it.v)){
			sum+=it.w;
			fa[find(it.u)]=find(it.v);
		}
		for(int i=1;i<=n;i++)if(in(i,x)){
			if(fl){if((~fl)&&fl!=find(i))fl=-1;}else fl=find(i);
		}
		// printf("x=%d fl=%d sum=%d\n",x,fl,sum);
		if(~fl)f[x][popcount(x)-1]=g[x]=sum;
	}
	for(int i=0;i<=k;i++){
		for(int x=S;~x;x--)if(~f[x][i]){
			// for(int i=1;i<=n;i++)dis[i]=1000000000;
			// for(int i=1;i<=n;i++)if(in(i,x)){
			// 	for(auto it:G[i])dis[it.v]=std::min(dis[it.v],it.w);
			// }
			for(int j,sum,y=x^S;y;y=(y-1)&(x^S))if(~g[y]){
				j=popcount(y)-1;
				if(i+j<=k){
					sum=locate(x,y)+f[x][i]+g[y];
					// printf("%d,%d,%d -> %d,%d,%d : %d\n",x,i,f[x][i],y,j,g[y],locate(x,y));
					if(sum<1000000000&&(sum>f[x|y][i+j]||!f[x|y][i+j]))f[x|y][i+j]=sum;
				}
			}
			// printf("%d > ",x);
			// for(int i=1;i<=n;i++)printf("%d%c",h[i][x]," \n"[i==n]);
		}
		// for(int j=0;j<(1<<n);j++)std::cout<<f[j][i]<<" \n"[j==S];
	}
	std::cout<<f[S][k]<<std::endl;
	std::cerr<<clock()/(double)CLOCKS_PER_SEC<<std::endl;
}