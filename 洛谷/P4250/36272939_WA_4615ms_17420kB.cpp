// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+7; const double eps=1e-9;
int n,q,k; double ans,sum,x[N],y[N]; bool fl;
struct seg{
	double xa,xb,ya,yb,a,b,c; bool fl;
}e[N],f[N];
inline int read(){
	int num=0; char t='+',g=getchar(); while(g<48||57<g) t=g,g=getchar();
	while(47<g&&g<58) num=(num<<1)+(num<<3)+g-48,g=getchar(); if(t=='-') return 0-num; return num;
}
inline bool check(double u){
	if(u<-eps||eps<u) return false; return true;
}
inline void addfunc(double xa,double ya,double xb,double yb){
	q++,e[q].a=-y[1]+y[0]-ya+yb,e[q].b=-x[0]+x[1]-xb+xa,e[q].c=-x[1]*y[0]+x[0]*y[1]+xb*ya-xa*yb;
	e[q].a=0-e[q].a,e[q].b=0-e[q].b,e[q].c=0-e[q].c;
	if(check(e[q].a)&&check(e[q].b)){
		e[q].fl=1; if(e[q].c<=eps) fl=1; return;
	}
	if(check(e[q].b)){
		e[q].xa=-e[q].c/e[q].a,e[q].xb=-e[q].c/e[q].a;
		if(e[q].a<=eps) e[q].ya=1,e[q].yb=2; else e[q].ya=2,e[q].yb=1; return;
	}
	if(check(e[q].a)){
		e[q].ya=-e[q].c/e[q].b,e[q].yb=-e[q].c/e[q].b;
		if(e[q].b<=eps) e[q].xa=2,e[q].xb=1; else e[q].xa=1,e[q].xb=2; return;
	}
	
	if(e[q].b>0){
		e[q].xa=1,e[q].xb=2,e[q].ya=(-e[q].a-e[q].c)/e[q].b,e[q].yb=(-e[q].a*2-e[q].c)/e[q].b;
	}
	else{
		e[q].xa=2,e[q].xb=1,e[q].ya=(-e[q].a*2-e[q].c)/e[q].b,e[q].yb=(-e[q].a-e[q].c)/e[q].b;
	}
}
inline void funcadd(double x,double y,double a,double b){
	q++,e[q].xa=x,e[q].ya=y,e[q].xb=a,e[q].yb=b;
	e[q].a=b-y,e[q].b=x-a,e[q].c=-e[q].a*e[q].xa-e[q].b*e[q].ya;
}
inline double getres(double a,double b,double x,double y){
	return a*y-b*x;
}
inline bool checkit(seg a,double x,double y){
	if(getres(x-a.xa,y-a.ya,a.xb-a.xa,a.yb-a.ya)<=eps) return true; return false;
}
inline bool cmp(seg a,seg b){
	if(check(atan2(a.yb-a.ya,a.xb-a.xa)-atan2(b.yb-b.ya,b.xb-b.xa))) return checkit(a,b.xa,b.ya);
	return atan2(a.yb-a.ya,a.xb-a.xa)<atan2(b.yb-b.ya,b.xb-b.xa);
}
inline double segx(seg a,seg b){
	if(check(a.b)) return -a.c/a.a; if(check(b.b)) return -b.c/b.a;
	a.a/=a.b,a.c/=a.b,b.a/=b.b,b.c/=b.b; return (b.c-a.c)/(a.a-b.a);
}
inline double segy(seg a,seg b){
	if(!check(a.b)){
		a.a/=a.b,a.c/=a.b,a.b=1; return -a.a*segx(a,b)-a.c;
	}
	if(!check(b.b)){
		b.a/=b.b,b.c/=b.b,b.b=1; return -b.a*segx(a,b)-b.c;
	}
}

int main(){
	n=read(); for(int i=0;i<n;i++) x[i]=read(),y[i]=read();
	for(int i=1;i<n-1;i++) addfunc(x[i],y[i],x[i+1],y[i+1]); addfunc(x[n-1],y[n-1],x[0],y[0]);
	for(int i=0;i<n-1;i++) funcadd(x[i],y[i],x[i+1],y[i+1]); funcadd(x[n-1],y[n-1],x[0],y[0]);
	for(int i=0;i<n-1;i++) ans=ans+getres(x[i],y[i],x[i+1],y[i+1]); ans=ans+getres(x[n-1],y[n-1],x[0],y[0]);
	sort(e+1,e+q+1,cmp); int ta=1,tb=0;
	for(int i=1;i<q;i++) if(check(atan2(e[i+1].yb-e[i+1].ya,e[i+1].xb-e[i+1].xa)-atan2(e[i].yb-e[i].ya,e[i].xb-e[i].xa))) e[i].fl=1;
	for(int i=1;i<=q;i++){
		if(e[i].fl) continue;
		if(!tb){
			tb++,f[tb]=e[i]; continue;
		}
		while(!checkit(e[i],segx(f[tb],f[tb-1]),segy(f[tb],f[tb-1]))&&tb>ta) tb--;
		while(!checkit(e[i],segx(f[ta],f[ta+1]),segy(f[ta],f[ta+1]))&&tb>ta) ta++;
		tb++,f[tb]=e[i];
	}
	while(!checkit(f[ta],segx(f[tb],f[tb-1]),segy(f[tb],f[tb-1]))&&tb>ta) tb--; f[tb+1]=f[ta];
	
	for(int i=ta;i<=tb;i++) k++,x[k]=segx(f[i],f[i+1]),y[k]=segy(f[i],f[i+1]); x[k+1]=x[1],y[k+1]=y[1];
	for(int i=1;i<=k;i++) sum=sum+getres(x[i],y[i],x[i+1],y[i+1]); printf("%.4lf\n", sum/ans);
}