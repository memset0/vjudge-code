#include<bits/stdc++.h>
const int N=510;
const long double eps=1e-7;
int n,m,s,a[N],g[N][N];
long double f[N][N],res[N];
struct atom{
	long double v,k; int i;
	inline bool operator<(const atom &other)const{
		return v<other.v;
	}
}x[N];
void gauss(long double a[N][N],long double res[N],int n,int m){
	// for(int i=1;i<=n;i++)for(int j=1;j<=m+1;j++)printf("%.2lf%c",f[i][j]," \n"[j==m+1]); puts("");
	for(int i=1,j,k,u=1;i<=m;i++){
		for(j=u;j<=n;j++)if(std::abs(a[j][i])>eps)break;
		if(j>n)continue; if(j!=u)std::swap(a[u],a[j]);
		for(j=m+1;j>=i;j--)a[u][j]/=a[u][i];
		for(j=u+1;j<=n;j++)for(k=m+1;k>=i;k--)a[j][k]-=a[u][k]*a[j][i];
		++u;
	}
	// for(int i=1;i<=n;i++)for(int j=1;j<=m+1;j++)printf("%.2lf%c",f[i][j]," \n"[j==m+1]); puts("");
	for(int i=n;i>=1;i--)for(int j=1;j<=m;j++)if(std::abs(a[i][j])>eps){
		res[j]=f[i][m+1];
		for(int k=1;k<i;k++)f[k][m+1]-=res[j]*f[k][j],f[k][j]=0;
		break;
	}
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),x[i].v=a[i],x[i].i=i,s+=a[i];
	if(s!=n*(n+1)/2)return puts("-1"),0; std::sort(x+1,x+n+1);
	for(int i=1;i<=n;i++)x[i].k=i; ++m;
	for(int i=1;i<=n;i++)g[m][x[i].i]=i;
	// for(int i=1;i<=n;i++)printf("%d%c",x[i].i," \n"[i==n]);
	// for(int i=1;i<=n;i++)printf("%.2lf%c",x[i].k," \n"[i==n]);
	// for(int i=1;i<=n;i++)printf("%.2lf%c",x[i].v," \n"[i==n]);
	for(int i=1;i<=n;i++){
		long double lim=DBL_MAX;
		for(int i=1;i<n;i++)if(std::abs(x[i].k-x[i+1].k)>eps)lim=std::min(lim,(x[i+1].v-x[i].v)/(x[i+1].k-x[i].k));
		if(lim==DBL_MAX)break;
		for(int i=1;i<=n;i++)x[i].v-=x[i].k*lim; ++m;
		for(int i=1,j;i<=n;){
			for(j=i;j<=n&&std::abs(x[i].v-x[j].v)<eps;j++); --j;
			for(int k=i;k<=j;k++)x[k].k=(i+j)/2.0,g[m][x[k].i]=i+j-k; i=j+1;
		}
		// for(int i=1;i<=n;i++)printf("%.2lf%c",x[i].v," \n"[i==n]);
		// for(int i=1;i<=n;i++)printf("%.2lf%c",x[i].k," \n"[i==n]); puts("");
	}
	for(int i=1;i<=m;i++)for(int j=1;j<=n;j++)f[j][i]=g[i][j];
	for(int i=1;i<=n;i++)f[i][m+1]=a[i];
	gauss(f,res,n,m);
	for(int i=1;i<=m;i++)if(res[i]<-eps)return puts("-1"),0;
	printf("%d\n",m);
	for(int i=1;i<=m;i++){
		printf("%.9Lf ",res[i]);
		for(int j=1;j<=n;j++)printf("%d%c",g[i][j]," \n"[j==n]);
	}
}