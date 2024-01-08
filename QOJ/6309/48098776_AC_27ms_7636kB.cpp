#include<bits/stdc++.h>
#define all(x) begin(x),end(x)
using namespace std;
const int N=1e3+9;
const int b[4][4]={
	{0,1,1,1},
	{1,1,0,1},
	{1,1,1,0},
	{1,0,1,1},
};
const int c[2][4]={
	{1,0,1,1},
	{1,1,1,0},
};
int T,n,m,fl,ans,sx,px,py,a[N][N];
void dfs(int i,int j){
	if(i<0||i>=n||j<0||j>=m)return;
	if(a[i][j]!=1)return;
	a[i][j]=2;
	dfs(i-1,j),dfs(i+1,j),dfs(i,j-1),dfs(i,j+1);
}
void solve(){
	fl=0;
	if(n>m)swap(n,m),fl^=1;
	if(n==2){
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				a[i][j]=c[i%2][j%4];
	}else if(n==3){
		for(int i=0;i<n;++i)for(int j=0;j<m;++j){
			if(((i==0||i==2)&&(j&3)==3)||(i==1&&(j&3)==1))a[i][j]=0;
			else a[i][j]=1;
		}
	}else{
		if((n%4)>(m%4))swap(n,m),fl^=1;
		int ox=0,oy=0;
		if(n%4==1)ox=2;
		if(n%4==2)ox=1;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				a[i][j]=b[(i+ox)%4][(j+oy)%4];
	}
	ans=0;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			ans+=!!a[i][j];
		}
	// cerr<<"!<<<"<<endl;
	// if(fl)for(int i=0;i<m;++i,cout<<"\n")for(int j=0;j<n;++j)cout<<a[j][i];
	// else for(int i=0;i<n;++i,cout<<"\n")for(int j=0;j<m;++j)cout<<a[i][j];
	// cerr<<"!>>>"<<endl;
	// for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(a[i][j]==1){dfs(i,j);break;}
	// for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(a[i][j]==1){assert(0);}
	// int cnt=0;
	// for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(a[i][j])++cnt;
	// assert(cnt==ans);
}
int main(){
#ifndef ONLINE_JUDGE
	//freopen(".in","r",stdin);
#endif
	cin.tie(0)->sync_with_stdio(0);
	// for(int i=3;i<=40;i++)
	// 	for(int j=3;j<=40;j++){
	// 		n=i,m=j;
	// 		fprintf(stderr,"n=%d m=%d\n",n,m);
	// 		solve();
	// 	}
	cin>>T;
	while(T--){
#ifdef memset0
		cout<<flush;
#endif
		cin>>n>>m;
		if(n<=3&&m<=3){
			cout<<n*m<<"\n";
			for(int i=1;i<=n;++i){
				for(int j=1;j<=m;++j)cout<<1;
				cout<<"\n";
			}
		 	continue;
		}
		solve();
		for(int i=0;i<n;i++)for(int j=0;j<m;j++)a[i][j]=!!a[i][j];
		cout<<ans<<"\n";
		if(fl)for(int i=0;i<m;++i,cout<<"\n")for(int j=0;j<n;++j)cout<<a[j][i];
		else for(int i=0;i<n;++i,cout<<"\n")for(int j=0;j<m;++j)cout<<a[i][j];
	}
}