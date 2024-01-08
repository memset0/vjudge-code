#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
const int N=2e5+10;
int n,m,a[N];
long long ans[N];
int gcd(int n,int m){return m?gcd(m,n%m):n;}
inline long long solve(int *a,int n){
	if(n==2){
		return 2ll*a[1]*a[2];
	}
	long long res=(long long)a[1]*(a[2]+a[3]);
	int l=2,r=3;
	for(int i=4;i<=n;i++)if(i&1){
		res+=(long long)a[i]*a[r];
		r=i;
	}else{
		res+=(long long)a[i]*a[l];
		l=i;
	}
	return res+=(long long)a[l]*a[r];
}
int main(){
#ifdef memset0
	freopen("ring.in","r",stdin);
#else
	// freopen("ring.in","r",stdin),freopen("ring.out","w",stdout);
#endif
	read(n),read(m);
	for(int i=1;i<=n;i++){
		read(a[i]);
		ans[0]+=(long long)a[i]*a[i];
	}
	std::sort(a+1,a+n+1);
	for(int i=1;i<=n/2;i++)if(n%i==0){
		for(int l=1,r=n/i;r<=n;l+=n/i,r+=n/i){
			ans[i]+=solve(&a[l-1],r-l+1);
		}
	}else{
		ans[i]=ans[gcd(i,n)];
	}
	// if(n%2==0)ans[n>>1]>>=1;
	for(int x,i=1;i<=m;i++){
		read(x);
		print(ans[x]),putchar('\n');
	}
}