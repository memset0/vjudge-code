#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+9;
int n;
struct pt{
	ll x,y;
	friend constexpr pt operator-(const pt &u,const pt &v){return {u.x-v.x,u.y-v.y};}
}a[N];
inline ll myabs(ll x){return x<0?-x:x;}
inline ll cross(const pt &u,const pt &v){return u.x*v.y-u.y*v.x;}
inline ll get_line(const pt &u,const pt &v){
	pt z=u-v;
	ll x=myabs(z.x);
	ll y=myabs(z.y);
	ll gcd=__gcd(x,y);
	return gcd;
}
ll solve(int xd,int yd){
	for(int i=1;i<=n;i++)a[i].x*=xd,a[i].y*=yd;
	long long s=0;
	long long m=0;
	a[n+1]=a[1];
	for(int i=2;i<n;i++)s+=myabs(cross(a[i]-a[1],a[i+1]-a[1]));
	for(int i=1;i<=n;i++)m+=get_line(a[i],a[i+1]);
	for(int i=1;i<=n;i++)a[i].x/=xd,a[i].y/=yd;
	assert((s+m)%2==0);
	ll ans=(s+m+2)>>1;
	// fprintf(stderr,"solve(%d,%d) = %lld\n",xd,yd,ans);
	return ans;
}
int main(){
#ifdef memset0
	freopen("I.in","r",stdin);
#else
	freopen("semi-cool.in","r",stdin);
	freopen("semi-cool.out","w",stdout);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
	}
	long long ans=0;
	ans+=solve(1,1);
	ans-=solve(1,2);
	ans-=solve(2,1);
	ans+=solve(2,2);
	cout<<ans<<endl;
}