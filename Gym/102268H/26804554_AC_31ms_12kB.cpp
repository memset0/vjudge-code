#include<bits/stdc++.h>
int n,m,p[25],c[25][25];
int main(){
	std::cin>>n>>m,m=(1<<n)-m-1;
	for(int i=0;i<=n;i++)c[i][0]=1;
	for(int i=0;i<=n;i++)for(int j=1;j<=i;j++)c[i][j]=c[i-1][j]+c[i-1][j-1];
	for(int i=n-1;i>=0;i--)for(int j=0;j<n;j++)if(m>=c[i][j])m-=c[i][j],p[i+1]=j+1; else break;
	printf("%d\n",std::accumulate(p+1,p+n+1,0));
	for(int i=1;i<=n;i++)for(int j=1;j<=p[i];j++)printf("%d %d\n",i,j);
}