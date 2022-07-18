#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=22;
int n,m,dp[N][1<<20];
std::vector<std::pair<int,int>> G[N];
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(m);
	for(int u,v,w,i=1;i<=m;i++){
		read(u),read(v),read(w);
		G[u].push_back({v,w});
		G[v].push_back({u,w});
	}
	int max=0;
	for(int i=0;i<n;i++)std::fill(dp[i],dp[i]+(1<<n),-1);
	for(int i=0;i<n;i++)dp[i][1<<i]=0;
	for(int x=0;x<(1<<n);x++){
		for(int i=0;i<n;i++)if(~dp[i][x]){
			max=std::max(max,dp[i][x]);
			for(const auto &it:G[i]){
				const int &j=it.first,&w=it.second;
				if(!((x>>j)&1)){
					dp[j][x|(1<<j)]=std::max(dp[j][x|(1<<j)],dp[i][x]+(w==1?1:2-w));
				}
			}
		}
	}
	printf("%d\n",(n-1<<1)-max);
}