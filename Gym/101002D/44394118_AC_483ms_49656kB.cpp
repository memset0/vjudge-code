#include<bits/stdc++.h>
using namespace std;

#define Mod(x) (x>=P)&&(x-=P)
#define rep(i,a,b) for(ll i=a,i##end=b;i<=i##end;++i)
#define drep(i,a,b) for(ll i=a,i##end=b;i>=i##end;--i)

typedef long long ll;
void Max(ll &a,ll b){(a<b)&&(a=b);}
char IO;
ll rd(ll res=0){
	bool f=0;
	while(IO=getchar(),IO<48||IO>57)
		f|=IO=='-';
	do res=(res<<1)+(res<<3)+(IO^48);
	while(IO=getchar(),isdigit(IO));
	return f?-res:res;
}
const ll M=2505;
ll sz[M],dp[M][M],A[M],B[M],C[M],k,n;
vector<int>G[M];
void dfs(ll x,ll f){
	sz[x]=1;
	dp[x][1]=C[x];
	dp[x][0]=0;
	for(ll y:G[x])if(y!=f){
		dfs(y,x);
		drep(j,sz[x],1)
			rep(i,1,sz[y])
				Max(dp[x][i+j],dp[x][j]+dp[y][i]);
		sz[x]+=sz[y];
	}
}
bool check(ll op){
	rep(i,0,n)rep(j,0,n+1)dp[i][j]=-2e18;
	rep(i,1,n)C[i]=B[i]*10000ll-1ll*A[i]*op;
	dfs(0,-1);
	return dp[0][k]>=0;
}
char s[M];
int main(){
	k=rd(),n=rd();
	++k;
	rep(i,1,n){
		A[i]=rd(),B[i]=rd();
		G[rd()].push_back(i);
	}
	ll L=0,R=100000000,ans;
	while(L<=R){
		ll mid=(L+R)>>1;
		if(check(mid)){
			ans=mid,L=mid+1;
		}else R=mid-1;
	}
	ans=(ans+5)/10;
	printf("%lld.%03lld\n",ans/1000,ans%1000);

	return 0;
}
