#include<bits/stdc++.h>
const int N=3e3+10;
int n,m;
char s[N][N];
bool ans,f[N][N],g[N][N];
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
	}
	for(int i=2;i<=n;i++)
		for(int j=2;j<=m;j++)
			f[i][j]=f[i-1][j]||f[i][j-1]||(s[i][j-1]==s[i-1][j]);
	for(int i=n-1;i>=1;i--)
		for(int j=m-1;j>=1;j--)
			g[i][j]=g[i+1][j]||g[i][j+1]||(s[i][j+1]==s[i+1][j]);
	for(int i=1;i<n;i++)
		for(int j=1;j<m-1;j++)	
			ans|=(s[i][j+1]==s[i+1][j])&&(s[i][j+2]==s[i+1][j+1]);
	for(int i=1;i<n-1;i++)
		for(int j=1;j<m;j++)	
			ans|=(s[i][j+1]==s[i+1][j])&&(s[i+1][j+1]==s[i+2][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			ans|=f[i][j]&&g[i][j];
	puts(ans?"YES":"NO");
}

// are there corner cases (N=1?)
// are array sizes proper (scaled by proper constant)
// any integer overflow?
// memset properly between test cases