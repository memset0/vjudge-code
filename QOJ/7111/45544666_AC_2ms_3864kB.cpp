#include<bits/stdc++.h>
using namespace std;
int T,a,b,c,d,rm,tt;
long long v,t,l,ans;
int gcd(int x,int y){
	return y?gcd(y,x%y):x;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d%d%lld%lld",&a,&b,&c,&d,&v,&t);
		if(a<c)swap(a,c),swap(b,d);
		l=1ll*a*c/gcd(a,c);
		if(v>=c){
			printf("%lld\n",1ll*(t/a+1)*b+1ll*(t/c+1)*d-1);
			continue;
		}
		ans=1ll*(t/a+1)*(b-1)+1ll*(t/c+1)*(d-1);
		tt=0;
		rm=0;
		for(long long i=0;i<l;i+=a){
			tt+=(rm<=v)+(c-rm<=v);
			rm=c-(a-rm)%c;
			if(rm==c)rm=0;
		}
		ans+=(t/l)*tt,t%=l;
		rm=0;
		for(long long i=0;i<=t;i+=a){
			ans+=(c-rm<=v);
			if(i+rm<=t&&rm<=v)++ans;
			rm=c-(a-rm)%c;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
/*
2
8 2 5 1 2 18
10 2 5 1 2 10
*/