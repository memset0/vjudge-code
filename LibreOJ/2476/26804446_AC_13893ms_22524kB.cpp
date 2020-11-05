//author: zx2003
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
char ibuf[1<<24],*ih=ibuf;
inline void read(ull&x){
	for(;!isdigit(*ih);++ih);
	for(x=0;isdigit(*ih);x=x*10+*ih++-48);
}
const int N=1e5+5;
int n,lm,i,j,k,x,pr[N],pcnt;
bool bb[N];
vector<int>cop[330];
ull A[N],B[N],C[N],D[N],E[N],F[N],ans;
inline void PS(ull*a,int n){for(int i=1;i<=pcnt && pr[i]<=n;++i)for(int j=1;pr[i]*j<=n;++j)a[pr[i]*j]+=a[j];}
inline void SS(ull*a,int n){for(int i=1;i<=pcnt && pr[i]<=n;++i)for(int j=n/pr[i];j;--j)a[j]+=a[pr[i]*j];}
inline void MI(ull*a,int n){for(int i=1;i<=pcnt && pr[i]<=n;++i)for(int j=n/pr[i];j;--j)a[pr[i]*j]-=a[j];}
inline ull calc(ull*A,ull*B,ull*E,ull*F,int m,int nn,int tp){
	static ull a[N],b[N],c[N],d[N],f[N];ull ret=0;
	for(j=1;j<=nn;++j)b[j]=B[i*j],c[j]=C[i*j],d[j]=D[i*j],f[j]=F[i*j];SS(c,nn);MI(d,nn);
	for(k=1;k<=m;++k){
		memset(a+1,0,nn<<3);for(j=1;j*k<=nn;++j)a[j*k]=A[i*j*k];SS(a,nn);
		for(j=1;j<=nn;++j)a[j]*=d[j];PS(a,nn);
		for(j=1;j<=nn;++j)a[j]*=b[j];SS(a,nn);
		ull all=0;for(j=tp?m+1:1;j*k<=nn;++j)all+=cop[k][j]?f[j]*a[j]*c[j*k]:0;ret+=E[i*k]*all;
	}
	return ret;
}
int main(){
	scanf("%d",&n);fread(ibuf,1,1<<24,stdin);
	for(i=2;i<=n;++i)if(!bb[i])for(pr[++pcnt]=i,j=i*2;j<=n;j+=i)bb[j]=1;
	for(i=1;i<=n;++i)read(A[i]);for(i=1;i<=n;++i)read(B[i]);
	for(i=1;i<=n;++i)read(C[i]);for(i=1;i<=n;++i)read(D[i]);
	for(i=1;i<=n;++i)read(E[i]);MI(E,n);
	for(i=1;i<=n;++i)read(F[i]);MI(F,n);
	for(i=1;i*i<=n;++i)for(j=1,cop[i].resize(n/i+1);i*j<=n;++j)cop[i][j]=__gcd(i,j)==1;
	for(i=1;i<=n;++i)lm=sqrt(n/i),ans+=calc(A,B,E,F,lm,n/i,0)+calc(B,A,F,E,lm,n/i,1);
	cout<<ans<<endl;
}