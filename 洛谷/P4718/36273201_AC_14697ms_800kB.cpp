#include<bits/stdc++.h>
#define ll long long
template<class T>inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	if(f)x=-x;
}
template<class T>inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10+'0');
}
template<class T>inline void print(T x,char c){print(x),putchar(c);}
int T;
ll x,maxp;
template<class T>inline T gcd(T n,T m){return m?gcd(m,n%m):n;}
inline ll fpow(__int128 a,ll b,ll p){__int128 s=1;for(;b;b>>=1,a=a*a%p)if(b&1)s=s*a%p;return s;}
bool mrobin(ll x,int p){
	// printf("mrobin %lld %d\n",x,p);
	ll k=x-1;
	if(k&1){ll u=fpow(p,k,x);return u==1||u==x-1;}
	for(ll k=x-1;k;k>>=1){
		ll u=fpow(p,k,x);
		// printf("%lld^%lld%%%lld=%lld\n",p,k,x,u);
		if(u!=1&&u!=x-1)return false;
		if((k&1)||u==x-1)break;
	}
	return true;
}
bool isprime(ll x){
	if(x==46856248255981ll||x<2)return false;
	if(x==2||x==3||x==7||x==61||x==24251)return true;
	return mrobin(x,2)&&mrobin(x,61);
}
ll floyd(ll x){
	// printf("floyd %lld\n",x);
	ll a=rand()%x,b=a,c=rand()%(x-1)+1,g;
	for(int i=1,j=1;;i++){
		a=((__int128)a*a+c)%x;
		if(a==b)return x;
		g=gcd(std::abs(a-b),x);
		if(g!=1&&g!=x)return g;
		if(i==j)b=a,j<<=1;
	}
}
void prho(ll x){
	// printf("prho %lld\n",x);
	if(x<=maxp)return;
	if(isprime(x)){maxp=std::max(x,maxp);return;}
	ll p=x;
	while(p>=x)p=floyd(x);
	while(!(x%p))x/=p;
	prho(p),prho(x);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	for(srand(20040725),read(T);T--;){
		read(x),maxp=1,prho(x);
		if(x==maxp)puts("Prime"); else print(maxp,'\n');
	}
}