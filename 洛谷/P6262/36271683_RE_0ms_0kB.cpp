#include<bits/stdc++.h>

const int N=1010,mod=998244353;
int n,m,p,q;

struct z {
	int x;
	z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}ans,f[N][N],P[N][N],C[N][N];

inline void upd(z &a,z b){a=a+b;}

int main(){
#ifdef local
	freopen("1.in","r",stdin);
#endif
	scanf("%d%d%d%d",&n,&m,&p,&q);

	P[0][0]=1;
	for(int i=1;i<=m;i++)P[0][i]=P[0][i-1]*q;
	for(int i=1;i<=m;i++)
		for(int j=0;j<=m;j++){
			P[i][j]=P[i-1][j]*p;
		}

	for(int i=0;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=n;j++)C[i][j]=C[i-1][j]+C[i-1][j-1];
	}

	f[1][m]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=0;k<=j;k++){
				upd(f[i+1][k+m-j],f[i][j]*P[k][j-k]*C[j][k]);
			}

	for(int i=0;i<=m;i++){
		upd(ans,f[n+1][i]);
	}
	printf("%d\n",ans.x);
}