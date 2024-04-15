#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
const int N=1e5;
int n,Q,lg[N+10];
int a[N+10],ql,qr,qk,sz[N+10],ar[N+10][70];
ll g[20][N+10],gp[N+10][70],ls,tmp;
ll mygcd(ll a, ll b){
  while (b != 0) {
    ll tmp = a;
    a = b;
    b = tmp % b;
  }
  return a;
}
ll _gcd(ll l,ll r){
	if(l>r)return 0;
	int k=lg[r-l+1];
	return mygcd(g[k][l],g[k][r-(1<<k)+1]);
}
ll Que(int l,int r,int k,ll tg){
	//cout<<"QUE "<<l<<" "<<r<<" "<<k<<" "<<tg<<"\n";
	if(r-l<k)return tg;
	if(k==1){
		ll ret=mygcd(tg,_gcd(l+1,r)),t;
		for(int i=2;i<=sz[l]&&ar[l][i]<=r;++i){
			t=mygcd(gp[l][i-1],_gcd(ar[l][i]+1,r));
			//cout<<"P="<<ar[l][i]<<",t="<<t<<"\n";
			ret=max(ret,mygcd(tg,t));
		}
		return ret;
	}
	ll ret=Que(l+1,r,k-1,tg);
	for(int i=2;i<=sz[l]&&ar[l][i]<=r;++i){
		ret=max(ret,Que(ar[l][i]+1,r,k-1,mygcd(tg,gp[l][i-1])));
	}
	return ret;
}
signed main(){
#ifdef memset0
	freopen("L.in","r",stdin);
#endif
	cin.sync_with_stdio(0),cin.tie(0);
	cin>>n>>Q;
	for(int i=2;i<=n;++i)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=n;++i)cin>>a[i],g[0][i]=a[i];
	for(int i=1;i<=lg[n];++i)for(int j=1;j+(1<<i)-1<=n;++j)g[i][j]=mygcd(g[i-1][j],g[i-1][j+(1<<i-1)]);
	ar[n][sz[n]=1]=n,gp[n][1]=a[n];
	for(int i=n-1;i>=1;--i){
		ar[i][sz[i]=1]=i,gp[i][1]=a[i],ls=a[i];
		for(int j=1;j<=sz[i+1];++j){
			if(ls!=(tmp=mygcd(a[i],gp[i+1][j]))){
				ar[i][++sz[i]]=ar[i+1][j],gp[i][sz[i]]=tmp,ls=tmp;
				//assert(sz[i]<=64);
			}
		}
		//cout<<"AR "<<i<<":\n";
		//for(int j=1;j<=sz[i];++j)cout<<"("<<ar[i][j]<<","<<gp[i][j]<<")\n";
	}
	while(Q--){
		cin>>ql>>qr>>qk;
		cout<<Que(ql,qr,qk,0)<<"\n";
	}
	return 0;
}
/*
4 4
3 2 6 4
1 3 1
2 4 1
1 4 2
1 4 3
*/