#include<bits/stdc++.h>
using namespace std;
const int N=1e5+9,mod=235813,lim=100000;
int n,a[N],b[N],fac[N],ifac[N],inv[N];
inline int rev(int x){return x?mod-x:x;}
inline int sub(int x,int y){return x-=y,x<0?x+mod:x;}
inline int add(int x,int y){return x+=y,x>=mod?x-mod:x;}
inline int C(int n,int m){return (long long)fac[n]*ifac[m]%mod*ifac[n-m]%mod;}
inline int getinv(int x){
	return x<N?inv[x]:(int)((long long)(mod-mod/x)*getinv(mod%x)%mod);
}
int main(){
#ifdef memset0
	freopen("B.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	fac[0]=ifac[0]=inv[0]=inv[1]=1;
	for(int i=2;i<N;i++)inv[i]=(long long)(mod-mod/i)*inv[mod%i]%mod;
	for(int i=1;i<N;i++)fac[i]=(long long)fac[i-1]*i%mod,ifac[i]=(long long)ifac[i-1]*inv[i]%mod;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]=(a[i]+mod)%mod;
	}
	for(int i=1;i<=n;i++){
		b[i]=C(n-1,i-1);
		if((n-i)&1)b[i]=rev(b[i]);
	}
	int sum=0;
	for(int i=1;i<=n;i++){
		sum=add(sum,(long long)a[i]*b[i]%mod);
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		int cur=rev(sub(sum,(long long)a[i]*b[i]%mod));
		cur=(long long)cur*getinv(b[i])%mod;
		if(cur<=lim||cur>=mod-lim){
			// cerr<<i<<" "<<(cur<=lim?cur:-(mod-cur))<<endl;
			if(cur==a[i])continue;
			ans++;
		}
	}
	cout<<ans<<endl;
}