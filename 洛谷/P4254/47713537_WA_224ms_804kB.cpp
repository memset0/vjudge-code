#include<bits/stdc++.h>
const int N=1e5+10;
int q,k;
double c,v;
char str[20];
struct line{
	double k,b;
	inline double operator()(double x){return k*x+b;}
};
struct node{
	int l,r,mid;
	line x;
}p[N<<2];
void modify(int u,line x){
	if(p[u].x.k==0&&p[u].x.b==0){p[u].x=x;return;}
	if(x(p[u].l)<=p[u].x(p[u].l)&&x(p[u].r)<=p[u].x(p[u].r))return;
	if(x(p[u].l)>=p[u].x(p[u].l)&&x(p[u].r)>=p[u].x(p[u].r)){p[u].x=x;return;}
	if(x(p[u].mid)>p[u].x(p[u].mid))std::swap(x,p[u].x);
	if(p[u].l!=p[u].r){
		if(x(p[u].l)>=p[u].x(p[u].l))modify(u<<1,x);
		else modify(u<<1|1,x);
	}
}
double query(int u,int k){
	if(p[u].l==p[u].r)return p[u].x(k);
	return std::max(p[u].x(k),query(k<=p[u].mid?u<<1:u<<1|1,k));
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	scanf("%d",&q);
	while(q--){
		scanf("%s",str);
		if(str[0]=='P'){
			scanf("%.2lf%.2lf",&v,&c);
			modify(1,(line){c,v});
		}else{
			scanf("%d",&k),v=query(1,k);
			std::abs(v)<=1e-9?puts("0"):printf("%.2lf\n",v);
		}
	}
}