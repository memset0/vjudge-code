#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7,N=1e6,V=1e5;
ll Qpow(ll a,ll p)
{
	ll res=1;
	while(p)
	{
		if(p&1)res=res*a%mod;
		a=a*a%mod,p>>=1;
	}
	return res;
}
int x,k,tot,fac[N],ifac[N];
bool vis[V];
vector<int> pri,m,d;
inline int C(int n,int m){
	if(n<m)return 0;
	return (ll)fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
void dfs(int i){
	if(i==m.size()){
		int cnt=1; //d的因数个数
		int mul=1; //当前贡献次数
		int mu=1; //mu(a)*mu(m/d/a)
		for(int i=0;i<m.size();i++){
			cnt=(ll)cnt*(m[i]-d[i]+1)%mod;
			if(d[i]==1){
				mul=2ll*mul%mod;
				mu*=-1;
			}
		}
		tot=(tot+(ll)C(cnt,k)*(mod+mu)%mod*mul)%mod;
		// for(int j=0;j<m.size();j++)cerr<<d[j]<<" \n"[j==d.size()];
		// fprintf(stderr,"C(%d,k)=%d * mul=%d * mu=%d\n",cnt,C(cnt,k),mul,mu);
		return;
	}
	for(int j=0;j<=m[i]&&j<=2;j++){
		d[i]=j;
		dfs(i+1);
	}
}
void solve(int gcd){
	int lcm=x/gcd-1;
	if(lcm<1)return;
	if(lcm==1){
		if(k==1){
			++tot;
		}
		return;
	}
	// fprintf(stderr,"gcd=%d lcm=%d\n",gcd,lcm);
	m.clear();
	for(int i=0;i<pri.size()&&(long long)pri[i]*pri[i]<=lcm;i++)
		if(lcm%pri[i]==0){
			m.push_back(0);
			while(lcm%pri[i]==0){
				++m.back();
				lcm/=pri[i];
			}
		}
	if(lcm>1){
		m.push_back(1);
	}
	d.resize(m.size());
	dfs(0);
}
int main(){
#ifdef memset0
	freopen("E.in","r",stdin);
#endif
	for(int i=2;i<V;i++){
		if(!vis[i]){
			pri.push_back(i);
		}
		for(int j=i*2;j<V;j+=i){
			vis[j]=true;
		}
	}
	fac[0]=ifac[0]=ifac[1]=1;
	for(int i=2;i<N;i++){
		ifac[i]=(ll)(mod-mod/i)*ifac[mod%i]%mod;
	}
	for(int i=1;i<N;i++){
		fac[i]=(ll)fac[i-1]*i%mod;
		ifac[i]=(ll)ifac[i-1]*ifac[i]%mod;
	}
	cin>>x>>k;
	for(int i=1;i*i<=x;i++)
		if(x%i==0){
			solve(i);
			if(i*i!=x)solve(x/i);
		}
	cout<<(tot%mod+mod)%mod<<endl;
}

/*
void solve(vector<int> &m){
	printf("k=%d:\n",k);
	for(auto w:m)printf("%d ",w);
	puts("");
	printf("H:");
	for(int i=1;i<=k;++i)
	{
		h[i]=1;
		for(auto w:m)
			h[i]=ll(h[i])*((Qpow(w+1,i)-2*Qpow(w,i)+Qpow(w-1,i))%mod)%mod;
		h[i]=(h[i]+mod)%mod;
		printf("%d ",h[i]);
	}
	puts("");
	int ans=0;
	for(int i=1;i<=k;++i)
		if((k-i)&1)ans=(ans-1ll*C(k,i)*h[i]%mod)%mod;
		else ans=(ans+1ll*C(k,i)*h[i]%mod)%mod;
	tot=(tot+ans)%mod;
}
*/