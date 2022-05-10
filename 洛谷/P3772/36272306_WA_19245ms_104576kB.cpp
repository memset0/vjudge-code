#include<bits/stdc++.h>
const int N=2e5+10;
int n,m,op;
double p[N],q[N];
struct matrix{
	double a[4][4];
	double e(){return a[0][0]+a[1][0];}
	void out(){printf("> %.2lf %.2lf %.2lf %.2lf\n");}
	void init(double p,double q){
		a[0][0]=a[1][1]=1;
		a[0][2]=a[2][2]=p,a[3][2]=1-p;
		a[0][3]=a[2][3]=q,a[3][3]=1-q;
	}
}base,res,win,lose,org[N];
inline matrix operator*(const matrix &a,const matrix &b){
	static matrix c; memset(c.a,0,sizeof(c.a));
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			for(int k=0;k<4;k++)
				c.a[i][j]+=a.a[i][k]*b.a[k][j];
	return c;
}
struct node{
	int l,r,mid;
	matrix x;
}e[N<<2];
void build(int u,int l,int r){
	e[u].l=l,e[u].r=r,e[u].mid=(l+r)>>1;
	if(l==r){e[u].x=org[l];return;}
	build(u<<1,l,e[u].mid),build(u<<1|1,e[u].mid+1,r);
	e[u].x=e[u<<1|1].x*e[u<<1].x;
}
void modify(int u,int k,const matrix &x){
	if(e[u].l==e[u].r){e[u].x=x;return;}
	modify(k<=e[u].mid?u<<1:u<<1|1,k,x);
	e[u].x=e[u<<1|1].x*e[u<<1].x;
}
matrix query(int u,int l,int r){
	if(e[u].l==l&&e[u].r==r)return e[u].x;
	if(r<=e[u].mid)return query(u<<1,l,r);
	if(l>e[u].mid)return query(u<<1|1,l,r);
	return query(u<<1|1,e[u].mid+1,r)*query(u<<1,l,e[u].mid);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	scanf("%d%d %c%lf",&n,&m,&op,&p[1]);
	for(int i=2;i<=n;i++)scanf("%lf%lf",&p[i],&q[i]);
	for(int i=1;i<=n;i++)printf("%.2lf %.2lf\n",p[i],q[i]);
	base.a[2][0]=1,win.init(1,1),lose.init(0,0);
	for(int i=1;i<=n;i++)org[i].init(p[i],q[i]);
	build(1,1,n);
	// for(int i=1;i<=n;i++)printf("%.2lf%c",(query(1,1,i)*base).e()," \n"[i==n]);
	for(int i=1,c,k,fl;i<=m;i++){
		while(c=getchar(),!isalpha(c));
		getchar(),getchar(),scanf("%d",&k);
		if(c=='a')scanf("%d",&fl),modify(1,k,fl?win:lose);
		else modify(1,k,org[k]);
		printf(c=='a'?"a %d %d\n":"d %d\n",k,fl);
		res=e[1].x*base;
		printf("%.4lf\n",res.a[0][0]+res.a[1][0]);
		for(int i=1;i<=n;i++)printf("%.2lf%c",(query(1,1,i)*base).e()," \n"[i==n]);
		for(int i=1;i<=n;i++)(query(1,1,i)*base).out();
	}
}