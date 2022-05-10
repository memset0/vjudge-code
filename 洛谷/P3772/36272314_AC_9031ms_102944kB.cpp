#include<bits/stdc++.h>
const int N=2e5+10;
int n,m,op,tag[N];
double S,ans,p[N],q[N];
std::set<int> set;
struct matrix{
	double a[4][4];
	inline double e(){return a[0][0]+a[1][0];}
	inline void out(){printf("> %.2lf %.2lf %.2lf %.2lf\n",a[0][0],a[1][0],a[2][0],a[3][0]);}
	inline void fullout(){
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				printf("%.2lf%c",a[i][j]," \n"[j==3]);
	}
	inline void init(double p,double q){
		a[0][0]=a[0][2]=a[2][2]=p,a[1][0]=a[3][2]=1-p;
		a[0][1]=a[0][3]=a[2][3]=q,a[1][1]=a[3][3]=1-q;
	}
}B[2],org[N];
inline matrix operator*(const matrix &a,const matrix &b){
	static matrix c; memset(c.a,0,sizeof(c.a));
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			for(int k=0;k<4;k++)
				c.a[i][j]+=a.a[i][k]*b.a[k][j];
	return c;
}
struct node{int l,r,mid; matrix x;}e[N<<2];
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
	matrix M=query(1,l+1,r)*B[tag[l]];
	return (M.a[tag[r]][0])/(r==n+1?1:M.a[2+tag[r]][0])-(tag[r]^1);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	scanf("%d%d %c%lf",&n,&m,&op,&p[1]);
	for(int i=2;i<=n;i++)scanf("%lf%lf",&p[i],&q[i]);
	tag[0]=0,tag[n+1]=1,B[0].a[2][0]=B[1].a[3][0]=1;
	org[0].init(1,1),org[n+1].init(0,0);
	for(int i=1;i<=n;i++)org[i].init(p[i],q[i]);
	build(1,1,n+1);
	set.insert(0),set.insert(n+1),ans=calc(0,n+1);
	// printf("=> %.2lf\n",ans);
	for(int i=1,c,k,v,l,r;i<=m;i++){
		static std::set<int>::iterator it;
		while(c=getchar(),!isalpha(c)); getchar(),getchar();
		if(c=='a'){
			scanf("%d%d",&k,&v),tag[k]=v^1,set.insert(k);
			it=set.find(k),l=*std::prev(it),r=*std::next(it);
			ans=ans-calc(l,r)+calc(l,k)+calc(k,r)+(tag[k]^1);
			// printf("ADD %d %d\n",k,v); for(int x:set)printf("%d ",x); puts("");
		}else{
			scanf("%d",&k);
			it=set.find(k),l=*std::prev(it),r=*std::next(it),set.erase(k);
			ans=ans+calc(l,r)-calc(l,k)-calc(k,r)-(tag[k]^1);
			// printf("DEL %d : ",k); for(int x:set)printf("%d ",x); puts("");
		}
		printf("%.6lf\n",ans);
	}
} 