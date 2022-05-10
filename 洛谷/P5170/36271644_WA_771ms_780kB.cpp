#include<bits/stdc++.h>
#define ll long long
const int mod=998244353;
inline int s1(int n){return n+1;}
inline int s2(int n){return (ll)n*(n+1)/2%mod;}
void simGcd(int n,int a,int b,int c,int &f,int &g,int &h){
	// printf("F %d %d %d %d\n",n,a,b,c);
	int ff,gg,hh,m=((ll)a*n+b)/c;
	if(a==0){
		f=(ll)s1(n)*(b/c)%mod;
	}else if(a>=c||b>=c){
		simGcd(n,a%c,b%c,c,ff,gg,hh);
		f=(ff+(ll)s2(n)*(a/c)+(ll)s1(n)*(b/c))%mod;
	}else{
		simGcd(m-1,c,c-b-1,a,ff,gg,hh);
		f=((ll)n*m-ff+mod)%mod;
	}
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	int T,n,a,b,c,f=-1,g=-1,h=-1;
	for(scanf("%d",&T);T--;){
		scanf("%d%d%d%d",&n,&a,&b,&c);
		simGcd(n,a,b,c,f,g,h);
		printf("%d %d %d\n",f,g,h);
	}
}