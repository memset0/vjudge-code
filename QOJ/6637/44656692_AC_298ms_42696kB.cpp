#include<bits/stdc++.h>
// #define endl '\n'
using namespace std;
using ll=long long;
const int N=1e7+9,mod=1e9+7;
const int inv2=(mod+1)>>1;
int T,n,c,ifac[N];
inline int power(int a,int b){
	int s=1;
	for(;b;b>>=1,a=(ll)a*a%mod)
		if(b&1)s=(ll)s*a%mod;
	return s;
}
#define f ifac
int main(){
#ifdef memset0
	freopen("G.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	ifac[0]=ifac[1]=1;
	for(int i=2;i<N;i++)ifac[i]=(ll)(mod-mod/i)*ifac[mod%i]%mod;
	for(int i=1;i<N;i++)ifac[i]=(ll)ifac[i-1]*ifac[i]%mod;
	f[0]=1;
	for(int i=1,x=(mod+1)>>1,y=1;i<N;i++){
		f[i]=(ll)x*ifac[i]%mod*y%mod;
		x=x&1?(x+mod)>>1:x>>1;
		x=x?mod-x:x;
		y=(ll)y*((i<<1)-1)%mod;
	}
	// for(int i=0;i<=10;i++)cerr<<f[i]<<" \n"[i==10];
	cin>>T;
	while(T--){
		cin>>n>>c;
		if(c==1){
			cout<<1<<endl;
			continue;
		}
		int cc=(ll)c*c%mod;
		int ans=0;
		int x=4ll*(mod+1-c)%mod,tx=1;
		int y=power(cc,mod-2),ty=power(cc,n);
		for(int i=0;i<=n;i++){
			int F=(ll)f[i]*(mod-c)%mod*tx%mod;
			if(i==0)F=((ll)F+c-2+mod)%mod;
			// fprintf(stderr,"i=%d f=%d g=%d\n",i,F,g[n-i]);
			ans=(ans+(ll)F*ty)%mod;
			tx=(ll)tx*x%mod;
			ty=(ll)ty*y%mod;
		}
		cout<<(ll)ans*(mod-inv2)%mod<<endl;
	}
}