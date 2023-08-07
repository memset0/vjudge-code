#include<bits/stdc++.h>
using namespace std;
const int N=5e5;
struct node{
	int c,id;
	bool operator<(const node&y)const{
		return c>y.c;
	}
}a[N+10];
string str;
int n,m,Q,pos[N+10],sz,u,v,lm,to[20][N+10],ans;
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>m>>Q;
	for(int i=1;i<=n;++i)cin>>a[i].c,a[i].id=i;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i){
		if(a[i].c!=a[i-1].c)++sz;
		pos[a[i].id]=sz;
	}
	for(int i=1;i<=sz;++i)to[0][i]=i;
	for(int i=1;i<=m;++i){
		cin>>u>>v;
		if(pos[u]>pos[v])swap(u,v);
		to[0][pos[v]]=min(to[0][pos[v]],pos[u]);
	}
	for(int i=sz-1;i>=1;--i)to[0][i]=min(to[0][i],to[0][i+1]);
	for(lm=1;(1<<lm)<=sz;++lm)for(int j=1;j<=sz;++j)to[lm][j]=to[lm-1][to[lm-1][j]];
	--lm;
	while(Q--){
		cin>>str>>u>>v;
		u=pos[u],v=pos[v];
		//cout<<u<<"->"<<v<<"\n";
		if(u<=v)cout<<"0\n";
		else{
			ans=0;
			for(int i=lm;i>=0;--i)if(to[i][u]>v)ans+=(1<<i),u=to[i][u];
			if(to[0][u]<=v)cout<<ans+1<<"\n";
			else cout<<"-1\n";
		}
	}
	return 0;
}