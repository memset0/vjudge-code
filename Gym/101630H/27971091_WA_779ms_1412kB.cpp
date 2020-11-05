#include<bits/stdc++.h>
#define i64 long long
#define ic8 __int128
using namespace std;
const int lim=3e4,N=lim+5,M=65;
i64 n,s,tem,ans,a[N],b[N],r[N],d[N],p[N],q[N];
mt19937_64 rng(20040726);
inline int bits(i64 x){return ceil(log(x+1));}
inline int mul(i64 a,i64 b){return (bits(a)+1)*(bits(b)+1);}
inline i64 query(i64 a){i64 b;cout<<"? "<<a<<endl<<flush,cin>>b;return b;}
// inline int query(i64 a){
// 	i64 r=1;int rsp=0;
// 	for(int i=0;i<60;i++){
// 		if((s>>i)&1)rsp+=mul(r,a),r=(ic8)r*a%n;
// 		rsp+=mul(a,a),a=(ic8)a*a%n;
// 	}
// 	return rsp;
// }
inline double cov(i64 *a,i64 *b){
	double sab=0,sa=0,sb=0;
	for(int i=1;i<=lim;i++){
		sab+=(double)a[i]*b[i];
		sa+=a[i],sb+=b[i];
	}
	return sab/lim-(sa/lim)*(sb/lim);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	// cin>>s;
	uniform_int_distribution<i64> ranger(0,n-1);
	for(int i=1;i<=lim;i++){
		a[i]=ranger(rng),r[i]=1,tem=a[i];
		q[i]=b[i]=query(a[i]);
		for(int i=0;i<60;i++)q[i]-=mul(tem,tem),tem=(ic8)tem*tem%n;
	}
	for(int i=0;i<60;i++){
		// printf("=== %d ===\n",i);
		for(int i=1;i<=lim;i++)p[i]=mul(r[i],a[i]),d[i]=mul(r[i],(ic8)a[i]*a[i]%n);
		// const int tem=20;
		// for(int i=1;i<=tem;i++)cout<<p[i]<<" ";cout<<endl;
		// for(int i=1;i<=tem;i++)cout<<q[i]<<" ";cout<<endl;
		// for(int i=1;i<=tem;i++)cout<<d[i]<<" ";cout<<endl;
		double x=cov(p,q),y=cov(p,p),z=cov(p,d);
		// printf("%.2lf %.2lf %.2lf\n",x,y,z);
		if(abs(x-y)<abs(x-z)){
			ans^=1ll<<i;
			for(int i=1;i<=lim;i++)q[i]-=p[i],r[i]=(ic8)r[i]*a[i]%n;
		}
		for(int i=1;i<=lim;i++)a[i]=(ic8)a[i]*a[i]%n;
	}
	cout<<"! "<<ans<<endl;
}