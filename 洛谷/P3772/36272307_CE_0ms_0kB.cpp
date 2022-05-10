#include<bits/stdc++.h>
const int N=2e5+10;
int n,m,op,tag[N];
double ans,p[N],q[N];
std::set<int> set;
template<class T> inline int prev(const T &x){T y=x;return *--y;}
template<class T> inline int next(const T &x){T y=x;return *++y;}
struct matrix{
	double a[4][4];
	double e(){return a[0][0]+a[1][0];}
	void init(double p,double q){
		a[0][0]=a[1][1]=1;
		a[0][2]=a[2][2]=p,a[3][2]=1-p;
		a[0][3]=a[2][3]=q,a[3][3]=1-q;
	}
}B0,B1,R,org[N];
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
matrix query(int u,int l,int r){
	if(e[u].l==l&&e[u].r==r)return e[u].x;
	if(r<=e[u].mid)return query(u<<1,l,r);
	if(l>e[u].mid)return query(u<<1|1,l,r);
	return query(u<<1|1,e[u].mid+1,r)*query(u<<1,l,e[u].mid);
}
inline double calc(int l,int r){
	if(l+1==r)return 0;
	R=query(1,l+1,r-1)*((l==0||tag[l])?B1:B0);
	return r==n+1?(R.a[2][0]+R.a[3][0]):(tag[r]?R.a[2][0]:R.a[3][0]);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	scanf("%d%d %c%lf",&n,&m,&op,&p[1]);
	for(int i=2;i<=n;i++)scanf("%lf%lf",&p[i],&q[i]);
	for(int i=1;i<=n;i++)printf("%.2lf %.2lf\n",p[i],q[i]);
	B0.a[3][0]=B1.a[2][0]=1;
	for(int i=1;i<=n;i++)org[i].init(p[i],q[i]);
	build(1,1,n);
	set.insert(0),set.insert(n+1),ans=calc(0,n+1);
	for(int i=1,c,k,v;i<=m;i++){
		while(c=getchar(),!isalpha(c)); getchar(),getchar();
		if(c=='a'){
			scanf("%d%d",&k,&v),tag[k]=v;
			auto it=set.insert(k);
			ans-=calc(prev(it),next(it));
			ans+=calc(prev(it),k)+calc(k,next(it))+tag[k];
		}else{
			scanf("%d",&k);
			auto it=set.find(k);
			ans-=calc(prev(it),k)+calc(k,next(it))+tag[k];
			set.erase(it);
			ans+=calc(prev(it),next(it));
		}
		printf("%.4lf\n",ans);
	}
}