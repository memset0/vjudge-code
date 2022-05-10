#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=1e6+10;
int n,k,a[N];
long long max,s[N];
int main(){
#ifdef memset0
	freopen("A.in","r",stdin);
#endif
	read(n),read(k),++k;
	for(int i=1;i<=n;i++)read(a[i]),s[i]=s[i-1]+a[i];
	for(int i=k;i<=n;i++)max=std::max(max,s[i]-s[i-k]);
	printf("%lld\n",max);
}