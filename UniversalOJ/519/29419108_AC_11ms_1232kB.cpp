#include<bits/stdc++.h>
using namespace std;
const int N=200;
int n,dp[N][6]; char s[N];
int main(){
	int t; cin>>t;
	while(t--){
		scanf("%s",s+1),n=strlen(s+1);
		for(int x=0;x<=n;x++)
			for(int z=0;z<=5;z++) dp[x][z]=n+1;
		dp[0][0]=0; 
		for(int i=1;i<=n;i++){
			if(s[i]=='x'){
				dp[i][0]=dp[i-1][0]+1;
				dp[i][1]=min(dp[i-1][1]+1,dp[i-1][0]);
				dp[i][2]=min(dp[i-1][2]+1,dp[i-1][1]);
				dp[i][3]=min(dp[i-1][3],dp[i-1][2]);
				dp[i][4]=min(dp[i-1][4],dp[i-1][3]+1);
				dp[i][5]=min(dp[i-1][5],dp[i-1][4]+1);
			}
			else{
				dp[i][0]=dp[i-1][0];
				dp[i][1]=min(dp[i-1][1],dp[i-1][0]+1);
				dp[i][2]=min(dp[i-1][2],dp[i-1][1]+1);
				dp[i][3]=min(dp[i-1][3]+1,dp[i-1][2]+1);
				dp[i][4]=min(dp[i-1][4]+1,dp[i-1][3]);
				dp[i][5]=min(dp[i-1][5]+1,dp[i-1][4]);
			}
		}
		int ans=n;
		for(int x=0;x<=4;x++) ans=min(ans,dp[n][x]);
		cout<<ans<<endl;
	}
    return 0;
}