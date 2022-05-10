#include<bits/stdc++.h>
using namespace std;
const int N=5e3+10,mod=998244353;
int T,n,m,spe,A,B,E,x[N],y[N],fac[N],ifac[N];
inline int dec(int a,int b){return (a-=b)<0&&(a+=mod),a;}
inline int inc(int a,int b){return (a+=b)>=mod&&(a-=mod),a;}
inline int fpow(int a,int b){int s=1;for(;b;b>>=1,a=(long long)a*a%mod)if(b&1)s=(long long)s*a%mod;return s;}
inline int C(int n,int m){return n<m||n<0||m<0?0:(long long)fac[n]*ifac[m]%mod*ifac[n-m]%mod;}
inline int F(const pair<int,int> &a,const pair<int,int> &b){return C(b.first-a.first,b.second-a.second);}
int calc(const vector<pair<int,int>> &lim){
	int ans=1;
	for(int i=0;i+1<lim.size();i++){
		ans=(long long)ans*F(lim[i],lim[i+1])%mod;
	}
	return ans;
}
int solve(int all){
	vector<pair<int,int>> lim;
	for(int i=1;i<=m;i++)
		if(x[i]>y[i]){
			lim.emplace_back(x[i],y[i]);
		}else if(x[i]<y[i]){
			lim.emplace_back(n-y[i],all-x[i]);
		}
	lim.emplace_back(0,0);
	lim.emplace_back(n,all);
	sort(lim.begin(),lim.end());
	lim.erase(unique(lim.begin(),lim.end()),lim.end());
	for(int i=0;i<lim.size();i++){
		if(lim[i].second<0)return 0;
		if(i&&(lim[i].first==lim[i-1].first||lim[i].second<lim[i-1].second))return 0;
	}
	if(!spe)return calc(lim);
	pair<int,int> L={spe,spe},R={n-spe,all-spe};
	int i=upper_bound(lim.begin(),lim.end(),L)-lim.begin()-1;
	int j=upper_bound(lim.begin(),lim.end(),R)-lim.begin()-1;
	A=(long long)fpow(F(lim[i],lim[i+1]),mod-2)*F(lim[i],L)%mod*F(L,lim[i+1])%mod;
	B=(long long)fpow(F(lim[j],lim[j+1]),mod-2)*F(lim[j],R)%mod*F(R,lim[j+1])%mod;
	if(i==j){
		if(L.first>R.first)swap(L,R);
		E=(long long)fpow(F(lim[i],lim[i+1]),mod-2)*F(lim[i],L)%mod*F(L,R)%mod*F(R,lim[i+1])%mod;
	}else{
		E=(long long)A*B%mod;
	}
//	fprintf(stderr,"(%d %d) (%d %d) (%d %d)\n",L.first,L.second,lim[i].first,lim[i].second,lim[i+1].first,lim[i+1].second);
//	fprintf(stderr,"(%d %d) (%d %d) (%d %d)\n",R.first,R.second,lim[j].first,lim[j].second,lim[j+1].first,lim[j+1].second);
//	fprintf(stderr,"all=%d ans=%d calc=%d A=%d B=%d E=%d\n",all,(((long long)A+B-E)*calc(lim)%mod+mod)%mod,calc(lim),A,B,E);
	return ((long long)A+B-E)*calc(lim)%mod;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	fac[0]=ifac[0]=ifac[1]=1;
	for(int i=2;i<N;i++)ifac[i]=(long long)(mod-mod/i)*ifac[mod%i]%mod;
	for(int i=1;i<N;i++)fac[i]=(long long)fac[i-1]*i%mod,ifac[i]=(long long)ifac[i-1]*ifac[i]%mod;
	cin>>T;
	while(T-->0){
		spe=0;
		cin>>n>>m;
		for(int i=1;i<=m;i++){
			cin>>x[i]>>y[i];
			if(x[i]==y[i])spe=max(spe,x[i]);
		}
		long long ans=0;
		for(int i=0;i<=n;i++)ans+=solve(i);
		cout<<(ans%mod+mod)%mod<<endl;
	}
}