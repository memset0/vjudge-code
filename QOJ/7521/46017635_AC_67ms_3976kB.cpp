#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using lf=long double;
const int N=59;
int n;
lf ans;
struct pt{
	ll x,y,z;
	lf len()const{
		return sqrtl((ll)x*x+(ll)y*y+(ll)z*z);
	}
	constexpr pt operator+(const pt &rhs)const{
		return {x+rhs.x,y+rhs.y,z+rhs.z};
	}
	constexpr pt operator-(const pt &rhs)const{
		return {x-rhs.x,y-rhs.y,z-rhs.z};
	}
	constexpr ll operator*(const pt &rhs)const{
		return (ll)x*rhs.x+(ll)y*rhs.y+(ll)z*rhs.z;
	}
	constexpr pt operator^(const pt &rhs)const{
		return {y*rhs.z-z*rhs.y,z*rhs.x-x*rhs.z,x*rhs.y-y*rhs.x};
	}
	constexpr bool iszero()const{
		return x==0&&y==0&&z==0;
	}
	// vec()const{
	// 	pt t;
	// 	ll g=__gcd(x,__gcd(y,z));
	// 	t.x=x/g;
	// 	t.y=y/g;
	// 	t.z=z/g;
	// }
}a[N];
struct plane{
	pt a,b,c,o;
	plane(pt _a,pt _b,pt _c){
		a=_a,b=_b,c=_c;
		o=(b-a)^(c-a);
	}
	ll tdis(pt x)const{
		return (x-a)*o;
	}
	void solve(){
		if(((b-a)^(c-a)).iszero())return;
		ll mx=0,mn=0;
		for(int i=1;i<=n;i++){
			ll dis=tdis(::a[i]);
			// fprintf(stderr,"%d %lld\n",i,dis);
			mx=max(mx,dis);
			mn=min(mn,dis);
		}
		// fprintf(stderr,"%d,%d,%d  %d,%d,%d  %d,%d,%d\n",a.x,a.y,a.z,b.x,b.y,b.z,c.x,c.y,b.z);
		// fprintf(stderr,"[%d %d %d] => %lld %lld %.12Lf\n",o.x,o.y,o.z,mx,mn,max(mx,-mn)/o.len());
		lf cur=(mx-mn)/o.len();
		// assert(!isnan(cur));
		ans=min(ans,cur);
	}
};
int main(){
#ifdef memset0
	freopen("J.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y>>a[i].z;
	}
	ans=1e20;
	for(int u=1;u<=n;u++)
		for(int v=u+1;v<=n;v++)
			for(int w=v+1;w<=n;w++){
				plane p(a[u],a[v],a[w]);
				p.solve();
			}
	for(int u0=1;u0<=n;u0++)
		for(int v0=u0+1;v0<=n;v0++)
			for(int u1=u0+1;u1<=n;u1++)
				for(int v1=u1+1;v1<=n;v1++){
					if(u1==v0||v1==v0)continue;
					plane p(a[u0],a[v0],a[u0]+a[v1]-a[u1]);
					// fprintf(stderr,"!! %d %d %d %d\n",u0,v0,u1,v1);
					p.solve();
				}
	if(ans>1e18){
		ans=0;
	}
	// printf("%.18Lf\n",ans);
	printf("%.18lf\n",(double)ans);
}