#include<bits/stdc++.h>
const int N=5e4+10;
int Q,k; double v,c; char opt[20];
struct line{
	double k,b;
	inline double operator[](double x)const{
		return k*x+b;
	}
}p[N<<2];
void modify(int u,line x,int l,int r){
	if(p[u].k==0&&p[u].b==0){p[u]=x;return;}
	if(x[l]<=p[u][l]&&x[r]<=p[u][r])return;
	if(x[l]>=p[u][l]&&x[r]>=p[u][r]){p[u]=x;return;}
	int mid=(l+r)>>1;
	if(x[mid]>p[u][mid])std::swap(p[u],x);
	if(l!=r)x[l]>p[u][l]?modify(u<<1,x,l,mid):modify(u<<1|1,x,mid+1,r);
}
double query(int u,int k,int l,int r){
	if(l==r)return p[u][k]; int mid=(l+r)>>1;
	return std::max(p[u][k],k<=mid?query(u<<1,k,l,mid):query(u<<1|1,k,mid+1,r));
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	for(scanf("%d\n",&Q);Q--;){
		scanf("%s",opt);
		if(opt[0]=='P'){
			scanf("%lf%lf",&v,&c);
			modify(1,(line){c,v-c},1,50000);
		}else{
			scanf("%d",&k);
			printf("%d\n",(int)(query(1,k,1,50000)/100));
		}
	}
}