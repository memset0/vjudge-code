#include<bits/stdc++.h>
int n,m,mod;
struct z{int x;inline z(int x=0):x(x){}};
inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
inline z fpow(z a,int b){z s=1;for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}
inline z c(int n,int m){
	if(m<0||m>n)return 0;
	z s=1;
	for(int i=1;i<=m;i++)s=s*i;
	s=fpow(s,mod-2);
	for(int i=1;i<=m;i++)s=s*(n-i+1);
	return s;
}
inline z f(int n,int m,int k){
	if(k>=m){
		// printf("%d %d %d : %d : %d %d\n",n,m,k,f(n+1,m,k-m),f(n,m,k-m+1),f(n,m,k-m));
		return f(n,m,k-m)+f(n,m,k-m+1);
	}
	z s=0;
	for(int i=0;m*i-k<=n+i;i++){
		s=s+c(n+i,m*i-k);
		// printf("%d : %d %d : %d\n",i,n+i,m*i-k,c(n+i,m*i-k));
	}
	// printf("f(%d,%d,%d)=%d\n",n,m,k,s.x);
	return s;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	std::cin>>n>>m>>mod;
	// std::cout<<f(n,m,0).x;
	z s=0;
	for(int i=0;i<=n;i++)s=s+c(n,i)*f(0,m,i);
	std::cout<<s.x<<std::endl;
	for(int i=0;i<=m;i++)printf("%d%c",f(0,m,i)," \n"[i==m]);
}