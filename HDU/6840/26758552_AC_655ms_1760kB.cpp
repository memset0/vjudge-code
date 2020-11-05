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
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=1e5+10;
int T,n,l,k,a[N];
long long solve(int *a,int l,int k){
	int cur=k;
	long long ans=0;
	for(int i=0;i<=n-l;i++){
		ans+=a[cur];
		if(i%l>=l-k)cur++;
	}
	return ans;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	for(read(T);T--;){
		read(n),read(l),read(k);
		for(int i=1;i<=n;i++)read(a[i]);
		std::sort(a+1,a+n+1);
		std::reverse(a+1,a+n+1);
		print(solve(a,l,k),' ');
		for(int i=1;i<=n;i++)a[i]=-a[i];
		std::reverse(a+1,a+n+1);
		print(-solve(a,l,l-k+1),'\n');
	}
}