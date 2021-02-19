#include<bits/stdc++.h>
using namespace std;
const int N=2e5+9;
int T,n,m,f[N],G[N][2];
vector<int> ans;
inline void upd(int &x,const int y){if(x<y)x=y;}
void solve(){
	cin>>n>>m;
	for(int u,v,i=1;i<=m;i++){
		cin>>u>>v;
		G[u][!!*G[u]]=v;
	}
	for(int i=1;i<=n;i++)if(f[i]==2){
		ans.push_back(i);
	}else{
		if(G[i][0])upd(f[G[i][0]],f[i]+1);
		if(G[i][1])upd(f[G[i][1]],f[i]+1);
	}
	cout<<ans.size()<<endl;
	for(int i=0;i<ans.size();i++)cout<<ans[i]<<" \n"[i+1==ans.size()];
}
int main(){for(cin>>T;T--;)solve(),memset(f,0,sizeof(f)),memset(G,0,sizeof(G)),ans.clear();}