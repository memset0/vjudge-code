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
const int N=1e5+10,mod=998244353;
int n,k;
struct z{int x;inline z(int x=0):x(x){}};
inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
inline z fpow(z a,int b){z s=1;for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}
std::vector<z> mul(const std::vector<z> &a,const std::vector<z> &b){
	std::vector<z> s(a.size());
	for(int i=1;i<=n;i++)
		for(int j=1;i*j<=n;j++)
			s[i*j]=s[i*j]+a[i]*b[j];
	return s;
}
std::vector<z> fpow(std::vector<z> a,int b){
	auto s=a; b--;
	for(;b;b>>=1,a=mul(a,a))if(b&1)s=mul(s,a);
	return s;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(k);
	std::vector<z> a(n+1);
	for(int i=1;i<=n;i++)read((int&)a[i]);
	a=fpow(a,fpow(k,mod-2).x);
	for(int i=1;i<=n;i++)print(a[i].x),putchar(" \n"[i==n]);
}