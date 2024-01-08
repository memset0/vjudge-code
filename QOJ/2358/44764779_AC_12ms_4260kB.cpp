#include<bits/stdc++.h>
using namespace std;
const int N=1e5,M=5;
int n,m,K,c,f,vis[N+10],ss[(1<<M)+10],ans;
int main(){
	scanf("%d%d%d",&n,&m,&K);
	for(int i=1;i<=K;++i){
		scanf("%d%d",&c,&f);
		vis[c]|=(1<<f-1);
	}
	for(int i=1;i<=n;++i)for(int j=0;j<(1<<M);++j)if(j&vis[i])++ss[j];
	ans=-1;
	for(int i=0;i<(1<<M);++i)if(n-ss[i]<=m)ans=max(ans,n-ss[i]);
	if(ans<0)puts("Round will be unrated");
	else printf("%d\n",ans);
	return 0;
}