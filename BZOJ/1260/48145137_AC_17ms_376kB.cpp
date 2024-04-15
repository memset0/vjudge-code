#include <cstdio>
#include <cstring>
#include <algorithm>
char s[55];
int n,dp[55][55];
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	memset(dp,0x3f,sizeof dp);
	for(int l=1;l<=n;++l)
		for(int i=1,j=i+l-1;j<=n;++i,++j)
		{
			dp[i][j]=l;
			if(j>i)
			{
				if(s[j]==s[j-1])dp[i][j]=std::min(dp[i][j],dp[i][j-1]);
				if(s[i]==s[i+1])dp[i][j]=std::min(dp[i][j],dp[i+1][j]);
				if(s[i]==s[j])dp[i][j]=std::min(std::min(dp[i][j],dp[i+1][j]),dp[i][j-1]);
				for(int k=i;k<j;++k)
					dp[i][j]=std::min(dp[i][j],dp[i][k]+dp[k+1][j]);
			}

		}
	printf("%d\n",dp[1][n]);
}
