#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=1e5+10;
int n,m,top,id[N],con[N],col[N],f3[N],tmp[N],dfn[N],low[N],stk[N],cnt[N];
long long out,ans[5];
std::vector<int> G[N],C[N];
void sol(int ban,int *col){
	// printf("sol => %d\n",ban);
	int cnt=0,tim=0;
	std::function<void(int,int)> tarjan=[&](int u,int fa){
		dfn[u]=low[u]=++tim,stk[++top]=u;
		for(int v:G[u])if(v!=fa&&v!=ban){
			if(!dfn[v]){
				// printf("%d -> %d\n",u,v);
				tarjan(v,u);
				low[u]=std::min(low[u],low[v]);
			}else{
				low[u]=std::min(low[u],dfn[v]);
			}
		}
		if(dfn[u]==low[u]){
			++cnt;
			do col[stk[top]]=cnt; while(stk[top--]!=u);
		}
		// printf("tarjan %d %d %d\n",u,dfn[u],low[u]);
	};
	for(int i=1;i<=n;i++)dfn[i]=0;
	for(int i=1;i<=n;i++)if(i!=ban&&!dfn[i])tarjan(i,-1);
}
long long calc(int *f){
	long long res=0;
	for(int i=1;i<=n;i++)cnt[i]=0;
	for(int i=1;i<=n;i++)cnt[f[i]]++;
	for(int i=1;i<=n;i++)res+=(long long)cnt[i]*(cnt[i]-1)/2;
	return res;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(m);
	for(int u,v,i=1;i<=m;i++){
		read(u),read(v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=1,cnt=0;i<=n;i++)if(!con[i]){
		++cnt;
		std::function<void(int)> dfs=[&](int u){
			con[u]=cnt;
			for(int v:G[u])if(!con[v])dfs(v);
		};
		dfs(i);
	}
	ans[1]=calc(con);
	sol(-1,col);
	ans[2]=calc(col);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)if(i!=j)
			C[i].push_back(j);
	for(int i=1;i<=n;i++){
		sol(i,tmp);
		// for(int j=1;j<=n;j++)if(i!=j){
		// 	std::vector<int> p;
		// 	for(int k:C[j])if(tmp[j]==tmp[k]||i==k){
		// 		p.push_back(k);
		// 	}
		// 	C[j].swap(p);
		// }
	}
	for(int i=1;i<=n;i++)ans[3]+=C[i].size();
	ans[3]>>=1;
	for(int i=1;i<=3;i++)ans[i]-=ans[i+1],out+=i*ans[i];
	printf("%lld\n",out);
}