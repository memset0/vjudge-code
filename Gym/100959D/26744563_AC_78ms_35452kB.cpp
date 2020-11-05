#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();if(f)x=-x;
}
const int N=2e3+10,mod=1e9+7;
int n,a[N],b[N],lcp[N][N];
struct z{
	int x;
	inline z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}f[N][N],g[N];
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n);
	for(int i=1;i<=n;i++)read(a[i]);
	for(int i=1;i<=n;i++)read(b[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[i]==b[j])lcp[i][j]=lcp[i-1][j-1]+1;
	g[0]=g[1]=1;
	for(int i=2;i<n;i++)
		for(int j=0;j<=i-1;j++)
			g[i]=g[i]+g[j]*g[i-j-1];
	// for(int i=1;i<=n;i++)printf("%d%c",g[i].x," \n"[i==n]);
	f[0][0]=1;
	for(int i=0;i<=n;i++)
		for(int j=i?0:1;j<=n;j++){
			if(i)f[i][j]=f[i][j]+f[i-1][j];
			if(j)f[i][j]=f[i][j]+f[i][j-1];
			// printf("%d %d : %d : %d\n",i,j,lcp[i][j],f[i][j].x);
			for(int k=1;k<=lcp[i][j];k++){
				f[i][j]=f[i][j]-f[i-k][j-k]*g[k-1];
				// printf("  %d : %d %d\n",k,g[k],f[i-k][j-k]);
			}
		}
	printf("%d\n",f[n][n].x);
}