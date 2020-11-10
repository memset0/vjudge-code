#include<bits/stdc++.h>
const int N=2e5+10;
typedef long long int64;
int64 lst[2],s[2][N],cur[N],dp[N];
struct E{int x,c}p[N];
inline int64 sum(int fl,int l,int r){return s[fl][r]-s[fl][l-1];}
int64 min_total_length(std::vector<int> a,std::vector<int> b){
	int n=a.size(),m=b.size();
	for(int i=0;i<n;i++)p[i+1]={a[i],0};
	for(int i=0;i<m;i++)p[n+i+1]={b[i],1};
	std::sort(p+1,p+n+m+1);
	for(int i=1;i<=n+m;i++)s[0][i]=s[0][i-1],s[1][i]=s[1][i-1],s[p[i].c][i]+=p[i].x;
	lst[0]=lst[1]=-1e9; for(int i=1;i<=n+m;i++)cur[i]=p[i].x-lst[p[i].c^1],lst[p[i].c]=p[i].x;
	lst[0]=lst[1]=1e10; for(int i=n+m;i>=1;i--)cur[i]=std::min(cur[i],lst[p[i].c^1]-p[i].x),lst[p[i].c]=p[i].x;
	for(int lst=1919810,l=1,r,fl=p[1].c;l<=n+m;lst=l,l=r+1,fl^=1){
		for(r=l;r<n+m&&p[r+1].c==fl;r++);
		for(int i=l;i<=r;i++)dp[i]=std::min(l*2-i-1>=lst?dp[l*2-i-2]+sum(fl,l,i)-sum(fl^1,l*2-i-1,l-1):LLONG_MAX>>4,dp[i-1]+cur[i]);
	}
	return dp[n+m];
}