#include<bits/stdc++.h>
#ifndef memset0
	#define endl '\n'
#endif
using namespace std;
const int N=1e2+9,M=N*N;
int n,tot,a[N][N],fa[M];
char op;
string str;
vector<int> G[M];
pair<int,int> pos[M];
vector<pair<int,int>> edg;
int find(int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
void dfs(int u,int fa=-1){
	for(int v:G[u])
		if(v!=fa){
			dfs(v,u);
		}
	if(fa!=-1){
		// cerr<<u<<" "<<fa<<endl;
		cout<<pos[u].first<<" "<<pos[u].second<<" "<<pos[fa].first<<" "<<pos[fa].second<<endl;
	}
}
int main(){
#ifdef memset0
	freopen("D.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	getline(cin,str);
	op=str[1];
	for(int i=1;i<=n;i++){
		getline(cin,str);
		for(int j=1;j<=n;j++){
			if(str[j-1]==op){
				a[i][j]=++tot;
				pos[tot]={i,j};
			}
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[i][j]){
				auto find=[&](int x,int y){
					if(x<1||y<1||x>n||y>n)return true;
					if(!a[x][y])return false;
					edg.emplace_back(a[i][j],a[x][y]);
					return true;
				};
				if(op=='R'||op=='Q'){
					for(int k=1;k<=n;k++)if(find(i-k,j))break;
					for(int k=1;k<=n;k++)if(find(i+k,j))break;
					for(int k=1;k<=n;k++)if(find(i,j-k))break;
					for(int k=1;k<=n;k++)if(find(i,j+k))break;
				}
				if(op=='B'||op=='Q'){
					for(int k=1;k<=n;k++)if(find(i-k,j-k))break;
					for(int k=1;k<=n;k++)if(find(i+k,j-k))break;
					for(int k=1;k<=n;k++)if(find(i-k,j+k))break;
					for(int k=1;k<=n;k++)if(find(i+k,j+k))break;
				}
				if(op=='N'){
					for(int x=-1;x<=1;x+=2)
						for(int y=-1;y<=1;y+=2){
							find(i+x,j+y*2);
							find(i+x*2,j+y);
						}
				}
				if(op=='K'){
					for(int x=-1;x<=1;x++)
						for(int y=-1;y<=1;y++)
							if(x||y){
								find(i+x,j+y);
							}
				}
			}
	for(int i=1;i<=tot;i++)fa[i]=i;
	for(const auto &[u,v]:edg)
		if(find(u)!=find(v)){
			G[u].push_back(v);
			G[v].push_back(u);
			// cerr<<"find "<<u<<" "<<v<<endl;
			fa[find(u)]=find(v);
		}
	bool fl=true;
	for(int i=1;i<=tot;i++)
		if(find(i)!=find(1)){
			fl=false;
			break;
		}
	if(!fl){
		cout<<"NO"<<endl;
		return 0;
	}
	cout<<"YES"<<endl;
	dfs(1);
}