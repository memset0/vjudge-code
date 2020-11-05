#include<bits/stdc++.h>
// #define int long long
#define ll long long
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=205;
int n,m,k,mod,binom[N][N],f[N][N][N][2],trans1[N][N][N],trans2[N][N][N];
inline void add(int &x,int y){x=(x+y)%mod;}
inline int fpow(int a,int b){int s=1;for(;b;b>>=1,a=(ll)a*a%mod)if(b&1)s=(ll)s*a%mod;return s;}
signed main(){
	read(n),read(m),read(k),read(mod);
	for(int i=0;i<=std::max(n,m);i++){
		binom[i][0]=1;
		for(int j=1;j<=i;j++)binom[i][j]=(binom[i-1][j]+binom[i-1][j-1])%mod;
	}
	for(int c=1;c<=k;c++)
		for(int d,i=0;i<=m;i++){
			d=(ll)(fpow(c,m-i)-fpow(c-1,m-i)+mod)%mod*fpow(k-c+1,i)%mod;
			for(int s=1,j=0;j<=n;j++,s=(ll)s*d%mod)trans1[c][i][j]=s;
		}
	for(int c=1;c<=k;c++)
		for(int d,i=0;i<=n;i++){
			d=(ll)(fpow(k-c+1,i)-fpow(k-c,i)+mod)%mod*fpow(c,n-i)%mod;
			for(int s=1,j=0;j<=m;j++,s=(ll)s*d%mod)trans2[c][i][j]=s;
		}
	f[0][0][0][0]=1;
	for(int c=0;c<k;c++){
		for(int i=0;i<=n;i++)
			for(int j=0;j<=m;j++){
				for(int k=0;i+k<=n;k++){
					// if((ll)f[c][i][j][0]*trans1[c+1][j][k]%mod*binom[n-i][k]%mod)printf("[%d %d %d %d] -> [%d %d %d %d] : %d %d %d\n",c,i,j,0,c  ,i+k,j,1,f[c][i][j][0],trans1[c+1][j][k],binom[n-i][k]);
					add(f[c  ][i+k][j][1],(ll)f[c][i][j][0]*trans1[c+1][j][k]%mod*binom[n-i][k]%mod);
				}
				for(int k=0;j+k<=m;k++){
					// if((ll)f[c][i][j][1]*trans2[c+1][i][k]%mod*binom[m-j][k]%mod)printf("[%d %d %d %d] -> [%d %d %d %d] : %d %d %d\n",c,i,j,0,c+1,i+k,j,1,f[c][i][j][1],trans2[c+1][i][k],binom[m-j][k]);
					add(f[c+1][i][j+k][0],(ll)f[c][i][j][1]*trans2[c+1][i][k]%mod*binom[m-j][k]%mod);
				}
			}
		// std::cerr<<f[c+1][n][m][0]<<std::endl;
	}
	printf("%d\n",f[k][n][m][0]);
}