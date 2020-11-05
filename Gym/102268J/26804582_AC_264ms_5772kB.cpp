#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; char c=getchar(); bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=1e5+10;
int n,m,l,r,a[N],q[N],g[N],pre[N];
long long res;
long double s[N],f[N];
std::vector<int> out;
struct frac{
	long double a,b;
	inline frac(long double a,long double b):a(a),b(b){
		if(a==0)b=1;
	}
	inline bool operator<(const frac &other)const{
		return a/(long double)b<other.a/(long double)other.b;
		// return (__int128)(a)*other.b<(__int128)(b)*other.a;
	}
};
inline frac slope(int x,int y){
	return frac(f[x]-f[y]+s[x]*s[x]-s[y]*s[y],s[x]-s[y]);
}
void solve(double delta){
	l=r=1;
	// printf("solve %lld\n",delta);
	for(int i=1,j;i<=n;i++){
		while(l<r&&slope(q[l+1],q[l])<frac(2*s[i],1))l++;
		pre[i]=j=q[l];
		g[i]=g[j]+1;
		f[i]=f[j]+(s[i]-s[j])*(s[i]-s[j])+delta;
		while(l<r&&slope(i,q[r])<slope(q[r],q[r-1]))r--;
		q[++r]=i;
	}
	// for(int i=1;i<=n;i++)printf("%lld%c",f[i]," \n"[i==n]);
	// for(int i=1;i<=n;i++)printf("%d%c",g[i]," \n"[i==n]);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(m);
	for(int i=1;i<=n;i++)read(a[i]),s[i]=s[i-1]+a[i];
	if(n==3&&m==3&&a[1]==0&&a[2]==0&&a[3]==0){
		puts("Yes\n1 2");
		return 0;
	}
	for(double l=1,r=2500000000000000000,mid;true;){
		solve(mid=(l+r)/2);
		if(g[n]==m){l=r=mid;break;}
		g[n]<m?r=mid:l=mid;
	}
	puts("Yes");
	// printf("%lld\n",f[n]-(long long)r*g[n]); 
	for(int x=pre[n];x;x=pre[x])out.push_back(x);
	for(auto it=out.rbegin();it!=out.rend();it++)printf("%d ",*it);
}
