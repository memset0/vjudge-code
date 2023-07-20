#include<bits/stdc++.h>
using namespace std;
const int N=209;
int T,n,b,a[N][N],g[N];
bool vis[N];
double bf,af[N][N];
void solve(){
	cin>>n>>bf;
	b=bf*1000000;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>af[i][j];
			a[i][j]=af[i][j]*1000000;
		}
	}
	if(n==1){
		cout<<"kono jinsei, imi ga nai!"<<endl;
		return;
	}
	for(int i=1;i<=n;i++){
		int mx=-10000000,mi;
		for(int j=1;j<=n;j++){
			if(a[i][j]>mx&&i!=j){
				mx=a[i][j];
				mi=j;
			}
		}
		if(mx<b){
			cout<<"hbxql"<<endl;
			return;
		}
		g[i]=mi;
		// cerr<<">> "<<i<<" "<<g[i]<<endl;
	}
	for(int i=1;i<=n;i++){
		vis[i]=false;
	}
	for(int i=1;i<=n;i++){
		vis[g[i]]=true;
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			cout<<"hbxql"<<endl;
			return;
		}
	}
	cout<<"wish you the best in your search"<<endl;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>T;
	while(T--){
		solve();
	}
}