#include<bits/stdc++.h> 
using namespace std;
const int N=505;
int n,m,ans,a[N],cnt[7],dp[N][N][N];
inline int calc(int x){
	vector<int> vec={x%10,x/10%10,x/100%10,x/1000%10,x/10000%10,x/100000%10,x/1000000};
	if(*min_element(vec.begin(),vec.end())==*max_element(vec.begin(),vec.end()))return -1;
	vector<int> tem(7,0);
	for(int i=0;i<7;i++){
		for(int j=6;j>=0;j--)tem[i]=tem[i]*10+vec[(i+j)%7];
		// printf("%d%c",tem[i],",\n"[i==6]);
	}
	return max_element(tem.begin(),tem.end())-tem.begin();
}
int solve(int a,int b,int c,int x,int y,int z){
	// printf("solve(%d,%d,%d,%d,%d,%d)\n",a,b,c,x,y,z);
	memset(dp,0x3f,sizeof(dp));
	dp[0][0][0]=0;
	for(int i=0;i<=7;i++)
		for(int j=0;j<=7;j++)
			for(int k=0;k<=7;k++)if((i||j||k)&&(i*x+j*y+k*z)%7==0){
				// printf("i=%d j=%d k=%d\n",i,j,k);
				int w=i+j+k-1;
				for(int p=i;p<=a;p++)
					for(int q=j;q<=b;q++)
						for(int r=k;r<=c;r++)
							dp[p][q][r]=min(dp[p][q][r],dp[p-i][q-j][r-k]+w);
			}
	int ans=0x3f3f3f3f;
	for(int p=0;p<=a;p++)
		for(int q=0;q<=b;q++)
			for(int r=0;r<=c;r++)
				ans=min(ans,dp[p][q][r]+a-p+b-q+c-r);
	return ans;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>m;
	for(int x,y,i=1;i<=m;i++){
		cin>>x,y=calc(x);
		// printf("> %d %d\n",x,y);
		if(~y)a[++n]=y;
	}
	// for(int i=1;i<=n;i++)printf("%d%c",a[i]," \n"[i==n]);
	for(int i=1;i<=n;i++)a[i]=((a[i+1]-a[i])%7+7)%7,cnt[a[i]]++;
	// for(int i=1;i<=n;i++)printf("%d%c",a[i]," \n"[i==n]);
	for(int i=1,tmp;i<=3;i++)tmp=min(cnt[i],cnt[7-i]),ans+=tmp,cnt[i]-=tmp,cnt[7-i]-=tmp;
	vector<pair<int,int>> tar;
	for(int i=1;i<=6;i++)if(cnt[i])tar.push_back({cnt[i],i});
	while(tar.size()<3)tar.push_back({0,-1});
	ans+=solve(tar[0].first,tar[1].first,tar[2].first,tar[0].second,tar[1].second,tar[2].second);
	cout<<ans<<endl;
}