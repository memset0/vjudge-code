#include<bits/stdc++.h>
using namespace std;
int T,len,a[20];
long long l,r,ans[20],dp[18][2][10][19][19];
void solve(long long x,int e){
	if(x==0){
		return;
	}
	if(x==1000000000000000000){
		x--;
		ans[18]+=e;
	}
	memset(dp,0,sizeof(dp));
	len=0;
	while(x)a[len++]=x%10,x/=10;
//	for(int i=0;i<len;i++)cerr<<a[i]<<" \n"[i+1==len];
	for(int c=0;c<10;c++)
		if(c<=a[len-1]){
			dp[len-1][c==a[len-1]][c][!!c][!!c]=1;
		}
	for(int ii,jj,k=len-2;k>=0;k--)
		for(int f=0;f<2;f++)
			for(int c=0;c<10;c++)
				if(!f||c<=a[k]){
					for(int x=0;x<10;x++)
						for(int i=0;i<=len-k;i++)
							for(int j=0;j<=len-k;j++){
								if(c==x){
									ii=i?i+1:0,jj=max(ii,j);
								}else{
									ii=1,jj=max(j,1);
								}
//								if(dp[k+1][f][x][i][j])fprintf(stderr,"dp[%d][%d][%d][%d][%d]=>dp[%d][%d][%d][%d][%d]\n",k+1,f,x,i,j,k,f&&c==a[i],c,ii,jj);
								dp[k][f&&c==a[k]][c][ii][jj]+=dp[k+1][f][x][i][j];
							}
				}
	static long long sum[20];
	memset(sum,0,sizeof(sum));
	for(int f=0;f<2;f++)
		for(int x=0;x<10;x++)
			for(int i=1;i<=18;i++)
				for(int j=1;j<=18;j++)
					if(dp[0][f][x][i][j]){
//						cerr<<f<<" "<<x<<" "<<i<<" "<<j<<" <= "<<dp[0][f][x][i][j]<<endl;
						sum[j]+=dp[0][f][x][i][j];
					}
	for(int i=0;i<=18;i++)ans[i]+=e*sum[i];
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>l>>r;
		memset(ans,0,sizeof(ans));
		solve(r,1);
//		for(int i=0;i<=18;i++)cerr<<ans[i]<<" \n"[i==18];
		solve(l-1,-1);
//		for(int i=0;i<=18;i++)cerr<<ans[i]<<" \n"[i==18];
		for(int i=18;i>=1;i--)
			if(ans[i]){
				cout<<i<<" "<<ans[i]<<endl;
				break;				
			}
	}
}