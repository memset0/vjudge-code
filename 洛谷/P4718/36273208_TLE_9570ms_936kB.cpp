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
int T; ll x; std::vector<ll> v;
template<class T>inline T gcd(T n,T m){return m?gcd(m,n%m):n;}
inline ll fpow(__int128 a,ll b,ll p){__int128 s=1;for(;b;b>>=1,a=a*a%p)if(b&1)s=s*a%p;return s;}
bool mrobin(ll x,int p){
	// printf("mrobin %lld %d\n",x,p);
	ll k=x-1,c=0; while(k&1^1)k>>=1,++c;
	ll u=fpow(p,k,x);
	if(u==1||u==x-1)return true;
	while(c--){u=(__int128)u*u%x; if(u==x-1)return true;}
	return false;
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
		if(a==b)return floyd(x);
		g=gcd(std::abs(a-b),x);
		if(g!=1&&g!=x)return g;
		if(i==j)b=a,j<<=1;
	}
}
void prho(ll x,std::vector<ll>&v){
	if(x==1)return;
	if(isprime(x)){v.push_back(x);return;}
	ll p=floyd(x);
	while(!(x%p))x/=p;
	prho(p,v),prho(x,v);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	for(srand(20040725),read(T);T--;){
		read(x),v.clear(),prho(x,v);
		if(isprime(x))puts("Prime");
		else{std::sort(v.begin(),v.end());print(*--v.end(),'\n');}
	}
}