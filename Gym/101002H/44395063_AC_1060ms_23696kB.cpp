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
const ll M=1e5+10;
vector<ll>val[305];
ll pre[M*10],t1[M],t2[M],n,k,dp[M],S;
void fenzhi(ll l,ll r,ll sl,ll sr){
	if(l>r)return ;
	ll mid=(l+r)>>1;
	ll op=0,res=-1;
	rep(i,sl,sr){
		if(mid-i<0)continue;
		if(mid-i>S)continue;
		if(res<t1[i]+pre[mid-i]){
			res=t1[i]+pre[mid-i];
			op=i;
		}
	}
	t2[mid]=res;
	fenzhi(l,mid-1,sl,op);
	fenzhi(mid+1,r,op,sr);
}
void solve(ll x){
	if(val[x].size()==0)return ;
	sort(val[x].begin(),val[x].end(),greater<ll>());
	rep(i,1,val[x].size())pre[i]=pre[i-1]+val[x][i-1];
	S=val[x].size();
	rep(i,0,x-1){
		ll cnt=0;
		for(ll j=i;j<=k;j+=x)
			t1[++cnt]=dp[j];	
		fenzhi(1,cnt,1,cnt);
		cnt=0;
		for(ll j=i;j<=k;j+=x)
			dp[j]=t2[++cnt];
	}
}

int main(){
	n=rd(),k=rd();
	rep(i,1,n){
		ll s=rd(),v=rd();
		val[s].push_back(v);
	}
	rep(i,1,300)solve(i);
	rep(i,1,k)printf("%lld ",dp[i]);
	puts("");
	return 0;
}
