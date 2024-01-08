#include<bits/stdc++.h>
#ifndef memset0
	#define endl '\n'
#endif
using namespace std;
string frac(int p,int q){
	int g=__gcd(p,q);
	p/=g;
	q/=g;
	if(q<0)p=-p,q=-q;
	if(q==1)return to_string(p);
	return to_string(p)+"/"+to_string(q);
}
string frac(int p,int r,int q){
	int r1=1,r2=r;
	for(int i=2;i*i<=r2;i++)
		while(r2%(i*i)==0){
			r2/=i*i;
			r1*=i;
		}
	int qr=q,g=__gcd(r1,qr);
	r1/=g;
	qr/=g;
	if(r1<0)r1=-r1;
	if(qr<0)qr=-qr;
	string ans="";
	if(p){
		ans+=frac(p,q)+"+";
	}
	if(r1>1){
		ans+=to_string(r1)+"*";
	}
	ans+="sqrt(";
	ans+=to_string(r2)+")";
	if(qr>1){
		ans+="/"+to_string(qr);	
	}
	return ans;
}
string solve(int a,int b,int c){
	int delta=b*b-4*a*c;
	if(delta<0)return "NO";
	int tdelta=sqrtl(delta)+0.5;
	if(tdelta*tdelta==delta){
		int p=-b;
		int q=a*2;
		if(q<0)p=-p,q=-q;
		return frac(p+tdelta,q);
	}else{
		return frac(-b,delta,a*2);
	}
}
int main(){
#ifdef memset0
//	freopen("uqe0.in","r",stdin);
	freopen("uqe2.in","r",stdin);
	freopen("uqe2.out","w",stdout);
#endif	
	cin.tie(0)->sync_with_stdio(0);
	int T,M,a,b,c;
	cin>>T>>M;
//	cerr<<"! "<<T<<" "<<M<<endl;
	for(int t=1;t<=T;t++){
		cin>>a>>b>>c;
		cout<<solve(a,b,c)<<endl;
	}
}