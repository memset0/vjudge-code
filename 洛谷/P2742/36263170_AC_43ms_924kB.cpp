#include<bits/stdc++.h>
const int N=1e4+10;
int n,top;
double res;
struct node{
	double x,y;
	inline double operator*(const node &other)const{return x*other.y-y*other.x;}
	inline node operator-(const node &other)const{return {x-other.x,y-other.y};}
	inline bool operator<(const node &other)const{return atan2(y,x)<atan2(other.y,other.x);}
	friend double dis(const node &a,const node &b){return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}
}d,a[N],stk[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lf%lf",&a[i].x,&a[i].y);
	d=*std::min_element(a+1,a+n+1,[](node a,node b){return a.y==b.y?a.x<b.x:a.y<b.y;});
	for(int i=1;i<=n;i++)a[i]=a[i]-d;
	std::sort(a+1,a+n+1);
	// for(int i=1;i<=n;i++)printf("[%.2lf %.2lf]%c",a[i].x,a[i].y," \n"[i==n]);
	for(int i=1;i<=n;i++){
		while(top>1&&(a[i]-stk[top-1])*(stk[top]-stk[top-1])>=0)top--;
		stk[++top]=a[i];
	}
	for(int i=1;i<=top;i++)res+=dis(stk[i],stk[i==top?1:i+1]);
	printf("%.2lf\n",res);
}