#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=1e5+10;
int n,x[N],y[N];
double S,T,f[N];
inline double calc(int x){
	if(n>100)return (double)1/f[x];
	return (double)(f[n-x]-1)/(f[n]-1-n-n*(n-1)/2);
}
inline double calc(int i,int j){
	return std::__gcd(std::abs(x[i]-x[j]),std::abs(y[i]-y[j]));
}
inline double calc(int s,int a,int b){
	int x1=x[a]-x[s],y1=y[a]-y[s];
	int x2=x[b]-x[s],y2=y[b]-y[s];
	return ((long long)x1*y2-(long long)x2*y1)/2.0;
}
inline double pick(double x,double y){
	// printf("pick %.2lf %.2lf\n",x,y);
	return x-y/2;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),f[0]=1;
	for(int i=0;i<n;i++)read(x[i]),read(y[i]);
	for(int i=1;i<=100;i++)f[i]=f[i-1]*2;
	S=pick(0,calc(0,1)+calc(n-1,0));
	for(int i=2;i<n;i++)S+=pick(calc(0,i-1,i),calc(i-1,i));
	for(int i=0;i<n;i++,T=0)
		for(int t=1;t<60;t++){
			int j=(i+t)%n; if(i==j)break;
			// printf("%d %d\n",i,j);
			T+=pick(calc(i,(j+n-1)%n,j),calc((j+n-1)%n,j));
			if(t>1)S+=(pick(0,calc(i,j))-T)*calc(t+1);
			// printf("> %.4lf %.4lf*%.4lf\n",T,(T+pick(0,calc(i,j))),calc(t+1));
		}
	printf("%.12lf\n",S+1);
}