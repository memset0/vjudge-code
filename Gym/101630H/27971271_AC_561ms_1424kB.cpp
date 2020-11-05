#include<bits/stdc++.h>
#define i64 long long
#define ic8 __int128
using namespace std;
const int lim=3e4,N=lim+5,M=65;
i64 n,s,tem,ans,a[N],b[N],r[N],d[N],p[N],q[N];
mt19937_64 rng(20040726);
inline int bits(i64 x){return 64-__builtin_clzll(x);}
inline int mul(i64 a,i64 b){return (bits(a)+1)*(bits(b)+1);}
inline i64 query(i64 a){i64 b;cout<<"? "<<a<<endl<<flush,cin>>b;return b;}
inline long double cov(i64 *a,i64 *b){
	long double sab=0,sa=0,sb=0;
	for(int i=1;i<=lim;i++){
		sab+=(long double)a[i]*b[i];
		sa+=a[i],sb+=b[i];
	}
	return sab/lim-(sa/lim)*(sb/lim);
}
inline string transform(i64 v){
	string s;
	for(int i=59;i>=0;i--)s+=(v>>i)&1?"1":"0";
	return s;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	uniform_int_distribution<i64> ranger(0,n-1);
	for(int i=1;i<=lim;i++){
		a[i]=ranger(rng),r[i]=1,tem=a[i];
		q[i]=b[i]=query(a[i]);
		for(int j=0;j<60;j++)q[i]-=mul(tem,tem),tem=(ic8)tem*tem%n;
	}
	for(int i=0;i<=60;i++){
		for(int i=1;i<=lim;i++)p[i]=mul(r[i],a[i]),d[i]=mul(r[i],(ic8)a[i]*a[i]%n);
		double x=cov(p,q),y=cov(p,p),z=cov(p,d);
		if(abs(x-y)<abs(x-z)){
			ans^=1ll<<i;
			for(int i=1;i<=lim;i++)q[i]-=p[i],r[i]=(ic8)r[i]*a[i]%n;
		}
		for(int i=1;i<=lim;i++)a[i]=(ic8)a[i]*a[i]%n;
	}
	cout<<"! "<<ans<<endl;
}