#include<bits/stdc++.h>
#ifdef memset0
	#define endl '\n'
#endif
#define x first
#define y second
using namespace std;
using pii=pair<int,int>;
using pff=pair<double,double>;
double sqr(double x){return x*x;}
double dis(const pff &a,const pff &b){return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));}
const int N=109;
int T,n,k;
pff s,t,ax,ay,bx,by,a[4],b[4],f[N],g[N];
pff operator*(const pff &a,double b){return {a.x*b,a.y*b};}
pff operator+(const pff &a,const pff &b){return {a.x+b.x,a.y+b.y};}
pff operator-(const pff &a,const pff &b){return {a.x-b.x,a.y-b.y};}
double dot(const pff &a,const pff &b){return a.x*b.x+a.y*b.y;}
pff trans(pff p){
	p=p-a[0];
	return bx*(dot(p,ax)/dot(ax,ax))+by*(dot(p,ay)/dot(ay,ay))+b[0];
}
pff itrans(pff p){
	p=p-b[0];
	return ax*(dot(p,bx)/dot(bx,bx))+ay*(dot(p,by)/dot(by,by))+a[0];
}
int main(){
#ifdef memset0
	freopen("E.in","r",stdin);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin>>T;
	cout<<fixed<<setprecision(20);
	while(T--){
		for(int i=0;i<4;i++)cin>>a[i].x>>a[i].y;
		for(int i=0;i<4;i++)cin>>b[i].x>>b[i].y;
		ax=a[1]-a[0],ay=a[3]-a[0];
		bx=b[1]-b[0],by=b[3]-b[0];
		cin>>s.x>>s.y;
		cin>>t.x>>t.y;
		cin>>k>>n;
		f[0]=s,g[0]=t;
		for(int i=1;i<=n;i++)f[i]=trans(f[i-1]);
		for(int i=1;i<=n;i++)g[i]=trans(g[i-1]);
		// for(int i=0;i<=n;i++)cout<<"f["<<i<<"] = "<<f[i].x<<" "<<f[i].y<<endl;
		// for(int i=0;i<=n;i++)cout<<"g["<<i<<"] = "<<g[i].x<<" "<<g[i].y<<endl;
		double ans=numeric_limits<double>::max();
		for(int i=0;i<=n;i++)
			for(int j=0;i+j<=n;j++){
				ans=min(ans,k*(i+j)+dis(f[i],g[j]));
			}
		cout<<ans<<endl;
		// pff t=pff{6,3};
		// cout<<">> "<<t.x<<" "<<t.y<<" :: "<<itrans(trans(t)).x<<" "<<itrans(trans(t)).y<<endl;
	}
}