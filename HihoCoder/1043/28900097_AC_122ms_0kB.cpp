#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m,dp[N];
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int a,b,i=1;i<=n;i++){
		cin>>a>>b;
		for(int j=a;j<=m;j++)dp[j]=max(dp[j],dp[j-a]+b);
	}
	cout<<dp[m]<<endl;
}