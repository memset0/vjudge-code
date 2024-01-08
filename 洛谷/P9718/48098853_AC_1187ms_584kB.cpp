#include<bits/stdc++.h>
#ifndef memset0
#define endl '\n'
#endif
#define all(x) begin(x),end(x)
using namespace std;
using ll=long long;
using lll=__int128;
const int L=37,X=20;
int T,n,a[L+2];
lll dp[L+2][2][X+2],bit[L+2];
void write(lll x){
	if(x<0){cout<<'-';return write(-x);}
	if(x==0){cout<<0;return;}
	if(x>9)write(x/10);
	cout<<(int)(x%10);
}
inline void upd(lll &x,lll y){
	if(x==-1||y<x)x=y;
}
lll bruteforce(ll v,int x){
	if(x==0){
		if((v%10)<9){
			return 1;
		}else{
			return -1;
		}
	}
	static int a[L],b[L];
	for(ll u=1;;u++){
		int n=0;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		for(ll tu=u,tv=v;tu||tv;tu/=10,tv/=10){
			a[n]=tu%10;
			b[n]=tv%10;
			n++;
		}
		n+=2;
		int c=0;
		for(int i=0;i<n;i++){
			int v=a[i]+b[i];
			if(v>9){
				++c;
				++a[i+1];
			}
		}
		if(c==x)return u;
	}
}
lll solve(ll v,int x){
	memset(a,0,sizeof(a));
	memset(dp,-1,sizeof(dp));
	n=0;
	while(v){
		a[n++]=v%10;
		v/=10;
	}
	if(x==0){
		for(int i=0;i<L;i++)
			if(a[i]<9){
				return bit[i];
			}
		return -1;
	}
	for(int u=0;u<=9;u++){
		int v=u+a[0];
		upd(dp[0][v>9][v>9],u);
	}
	for(int i=0;i+1<L;i++)
		for(int j=0;j<2;j++)
			for(int k=0;k<=x;k++)
				if(dp[i][j][k]!=-1){
					// cout<<i<<","<<j<<","<<k<<"::",write(dp[i][j][k]),cout<<endl;
					for(int u=0;u<=9;u++){
						int v=u+j+a[i+1];
						upd(dp[i+1][v>9][k+(v>9)],u*bit[i+1]+dp[i][j][k]);
					}
				}
	lll ans=-1;
	for(int i=0;i<L;i++)
		if(dp[i][0][x]!=-1){
			upd(ans,dp[i][0][x]);
		}
	// for(int j=0;j<2;j++)
	// 	if(dp[L-1][j][x]!=-1){
	// 		upd(ans,dp[L-1][j][x]);
	// 	}
	return ans;
}
bool check(lll u,lll v,int x){
	if(v==-1)return true;
	int n=0;
	static int a[L],b[L];
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	while(u||v){
		a[n]=u%10,u/=10;
		b[n]=v%10,v/=10;
		n++;
	}
	for(int i=0;i<=n+1;i++){
		int v=a[i]+b[i];
		if(v>9){
			--x;
			++a[i+1];
		}
	}
	return x==0;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("C.in","r",stdin);
#endif
	cin.tie(0)->sync_with_stdio(0);
	bit[0]=1;
	for(int i=1;i<L;i++)bit[i]=bit[i-1]*10;
	// write(bit[L-1]),cout<<endl;
	cin>>T;
	ll v;
	int x;
	// for(int v=1;v<=10000;v++)
	// 	for(int x=1;x<=6;x++){
	// 		lll a=solve(v,x);
	// 		lll b=bruteforce(v,x);
	// 		cout<<v<<" "<<x<<" => ",write(a),cout<<" ",write(b),cout<<endl;
	// 		assert(a==b);
	// 	}
	while(T--){
		cin>>v>>x;
		lll ans=solve(v,x);
		assert(check(v,ans,x));
		write(ans),cout<<endl;
	}
}