#include<bits/stdc++.h>
using namespace std;
int lim;
bool check(long double r){
	long long cnt=0;
	for(int i=1;;i++){
		long double x=r*r-i*i;
		if(x<1)break;
		cnt+=sqrtl(x);
		if(4*cnt>lim)return false;
	}
	return true;
}
int main(){
#ifdef memset0
	freopen("C.in","r",stdin);
#endif
	cin>>lim;
	long double l=0,r=sqrt(lim)+10,mid,res;
	for(int i=0;i<60;i++){
		mid=(l+r)/2;
		if(check(mid)){
			res=mid;
			l=mid;
		}else{
			r=mid;
		}
	}
	cout<<fixed<<setprecision(10)<<res<<endl;
}