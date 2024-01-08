#include<bits/stdc++.h>
// #define endl '\n'
using namespace std;
const int N=1e5+9;
int T,n,m,a[N],b[N];
bool _dp[7][4][N];
auto dp=_dp+3;
string sa,sb;
int main(){
#ifdef memset0
	freopen("A.in","r",stdin);
	// freopen("A.out","w",stdout);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>T;
	getline(cin,sa);
	while(T--){
		getline(cin,sa);
		getline(cin,sb);
		n=sa.length();
		m=sb.length();
		for(int i=1;i<=n;i++)a[i]=sa[i-1];
		for(int i=1;i<=m;i++)b[i]=sb[i-1];
		for(int i=0;i<=n;i++)
			for(int j=0;j<=3;j++)
				for(int k=-j;k<=j;k++)
					dp[k][j][i]=false;
		dp[0][0][0]=true;
		for(int i=0;i<=n;i++)
			for(int j=0;j<=3;j++)
				for(int k=-j;k<=j;k++)
					if(dp[k][j][i]){
						// fprintf(stderr,"i=%d j=%d k=%d(%d)\n",i,j,k,i+k);
						if(i+1<=n&&i+k+1<=m){
							if(a[i+1]==b[i+k+1]){
								dp[k][j][i+1]=true;
							}else{
								if(j<3){
									dp[k][j+1][i+1]=true;
								}
							}
						}
						if(j<3){
							if(i+1<=n){
								dp[k-1][j+1][i+1]=true;
							}
							if(i+k+1<=m){
								dp[k+1][j+1][i]=true;
							}
						}
					}
		int ans=-1;
		int t=m-n;
		// cerr<<"! t="<<t<<endl;
		if(-3<=t&&t<=3){
			for(int i=0;i<=3;i++)
				if(dp[t][i][n]){
					ans=i;
					break;
				}
		}
		if(ans==0){
			cout<<"You're logged in!"<<endl;
		}else if(ans==1){
			cout<<"You almost got it. You're wrong in just one spot."<<endl;
		}else if(ans==2){
			cout<<"You almost got it, but you're wrong in two spots."<<endl;
		}else if(ans==3){
			cout<<"You're wrong in three spots."<<endl;
		}else{
			cout<<"What you entered is too different from the real password."<<endl;
		}
	}
}