#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int MOD=1234567891;
const int facs[5]={2,9,5,3607,3803};
const int M=10;
int m,K,r,mod,ar[15],ans[5],nw;
ll N,mn;
struct matrix:array<array<int,M>,M>{
	friend matrix operator*(const matrix &a,const matrix &b){
		static matrix c;
		for(int i=0;i<M;i++)
			for(int j=0;j<M;j++){
				c[i][j]=0;
			}
		for(int i=0;i<M;i++)
			for(int k=0;k<M;k++)
				for(int j=0;j<M;j++){
					c[i][j]=(c[i][j]+(ll)a[i][k]*b[k][j])%mod;
				}
		return c;
	}
};
matrix POW(matrix x,ll y){
	matrix ret;
	for(int i=0;i<M;++i)for(int j=0;j<M;++j)ret[i][j]=(i==j);
	while(y)y&1?ret=ret*x,0:0,x=x*x,y>>=1;
	return ret;
}
void prt(matrix MT){
	for(int i=0;i<M;++i){
		for(int j=0;j<M;++j)cout<<MT[i][j]<<" ";
		puts("");
	}
}
void Solve(int P){
	// cout<<"----------------------------\nSolve "<<P<<"\n";
	r=N%P,mn=N/P;
	mod=P;
	matrix R,al,a1;
	if(!r){
		for(int i=0;i<M;++i)for(int j=0;j<M;++j)R[i][j]=(i==j);
	}
	for(int i=0;i<M;++i)for(int j=0;j<M;++j)al[i][j]=(i==j);
	for(int i=1;i<=P;++i){
		for(int j=0;j<M;++j)for(int k=0;k<M;++k)a1[j][k]=0;
		for(int j=1;j<=K;++j)a1[0][ar[j]-1]=(i-ar[j]+1)%P;
		for(int j=1;j<M;++j)a1[j][j-1]=1;
		// if(P<=9){cout<<"I="<<i<<" MT=\n";prt(a1);puts("");}
		al=a1*al;
		if(r==i)R=al;
	}
	// cout<<"REMAIN=\n";prt(R);puts("");
	matrix ret=R*POW(al,mn);
	ans[nw++]=ret[0][0];
	// cout<<"ANS "<<nw-1<<"="<<ans[nw-1]<<":"<<facs[nw-1]<<"\n";
}
inline ll exgcd(ll a,ll b,ll &x,ll &y){
	if(a==0&&b==0)return -1;
	if(b==0){x=1,y=0; return a;}
	ll d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}
void MLES_solve(int &m0,int &a0,int m,int a){
	ll x,y;
	int g=exgcd(m0,m,x,y);
	x*=(a-a0)/g;
	x%=m/g;
	a0=x*m0+a0;
	m0*=m/g;
	a0%=m0;
	if(a0<0)a0+=m0;
}
int MLES(){
	int m0=1,a0=0;
	for(int i=0;i<5;i++){
		MLES_solve(m0,a0,facs[i],ans[i]);
	}
	return a0;
}
int PW(int x,int y){
	int ret=1;
	while(y)y&1?ret=1ll*ret*x%MOD:0,x=1ll*x*x%MOD,y>>=1;
	return ret;
}
int main(){
#ifdef memset0
	freopen("J.in","r",stdin);
#else
	freopen("stairs.in","r",stdin);
	freopen("stairs.out","w",stdout);
#endif
	scanf("%lld%d%d",&N,&m,&K);
	for(int i=1;i<=K;++i)scanf("%d",&ar[i]);
	for(int i=0;i<5;++i)Solve(facs[i]);
	int fa=MLES();
	// cout<<"FS="<<fa<<"\n";
	printf("%d",PW(m,fa));
	return 0;
}
/*
3 2 1
1
*/