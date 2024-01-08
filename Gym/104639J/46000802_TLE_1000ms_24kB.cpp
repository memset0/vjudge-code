#include<bits/stdc++.h>
//#define all(x) (x).begin(),(x).end()
#define debug(x) cerr<<#x<<": "<<x<<endl
using namespace std;
using ll=long long;
using lf=long double;
int T;
lf px,py,qx,qy,cx,cy,dx,dy,R,dlt;
lf MH(lf x,lf y){
	return abs(x-cx)+abs(y-cy);
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>T;
	while(T--){
		cin>>px>>py>>qx>>qy;
		cx=(px+qx)/2.0,cy=(py+qy)/2.0;
		cin>>px>>py>>qx>>qy;
		dx=(px+qx)/2.0,dy=(py+qy)/2.0,R=sqrt((px-qx)*(px-qx)+(py-qy)*(py-qy))/2.0;
		dlt=sqrt(2.0)*R/2.0;
		cout<<fixed<<setprecision(12)<<min(min(MH(dx-dlt,dy-dlt),MH(dx+dlt,dy-dlt)),min(MH(dx-dlt,dy+dlt),MH(dx+dlt,dy+dlt)))<<"\n";
	}
}