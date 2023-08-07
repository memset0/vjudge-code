#include<bits/stdc++.h>
using namespace std;
const int N=1e6,MK=5000;
const long long INF=1e18;
int Q,n,K,m,len[N+10],c[N+10][26],vis[N+10][26],cnt,TIM,tmp;
long long mn[MK+10],g[MK+10],cst[N+10],dp[MK+10];
string s[N+10],T;
void Ins(int x,int id,int nw){
	//cout<<"INS "<<x<<" "<<id<<","<<nw<<"\n";
	cst[x]=min(cst[x],g[K-(len[id]-nw)%K]+1+1+(len[id]-nw)/K);
	//cout<<"CST="<<cst[x]<<"\n";
	if(nw==len[id])return;
	int t=s[id][nw]-'a';
	if(vis[x][t]!=TIM)vis[x][t]=TIM,c[x][t]=++cnt,cst[cnt]=INF;
	Ins(c[x][t],id,nw+1);
}
int main(){
#ifdef memset0
	freopen("E-big.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>Q;
	while(Q--){
		cin>>n>>K;
		for(int i=1;i<K;++i)mn[i]=g[i]=INF;
		//cin>>s[0];
		for(int i=1;i<=n;++i){
			cin>>s[i];
			//s[i]=s[0];
			len[i]=s[i].size();
			mn[len[i]%K]=min(mn[len[i]%K],1ll+len[i]/K);
		}
		fill(g,g+K,INF);
		g[K]=-1;
		g[0]=0;
		vector<pair<int,long long>> e;
		for(int i=1;i<K;i++){
			if(mn[i]!=INF){
				e.emplace_back(i,mn[i]);
			}
		}
		priority_queue<pair<long long,int>> q;
		q.push({0,0});
		while(q.size()){
			auto [d,u]=q.top();
			q.pop();
			if(g[u]+d)continue;
			for(const auto &[t,w]:e){
				int v=(u+t)%K;
				// fprintf(stderr,"%d -> %d %lld\n : %lld %lld\n",u,v,w,g[u],g[v]);
				if(g[u]+w<g[v]){
					g[v]=g[u]+w+(u+t>=K);
					q.push({-g[v],v});
				}
			}
		}
		//for(int i=0;i<K;++i)cout<<"G "<<i<<"="<<g[i]<<"\n";
		cnt=1,++TIM;
		for(int i=1;i<=n;++i)Ins(1,i,0);
		cin>>T,m=T.size();
		for(int i=1;i<=m;++i)dp[i]=INF;
		for(int i=0;i<m;++i)if(dp[i]!=INF){
			tmp=1;
			//cout<<"DP "<<i<<"="<<dp[i]<<"\n";
			for(int j=i+1;j<=m;++j){
				if(vis[tmp][T[j-1]-'a']!=TIM)break;
				tmp=c[tmp][T[j-1]-'a'];
				dp[j]=min(dp[j],dp[i]+cst[tmp]);
			}
		}
		cout<<(dp[m]==INF?-1ll:dp[m])<<endl;
	}
	return 0;
}
/*
2
2 3
defgh
abc
abcde
1 1
a
b
*/