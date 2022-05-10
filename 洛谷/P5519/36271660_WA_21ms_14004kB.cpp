// luogu-judger-enable-o2
#include<bits/stdc++.h>
#define ll long long

template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}

const int N=2e3+10,mod=998244352;
int n,k,res,ans=1,f[N],c[N][N];

inline int inc(int a,int b){return (a+=b)>=mod?a-mod:a;}

int main(){
// 	freopen("1.in","r",stdin);
	read(n),read(k);
	for(int i=0;i<=n+k;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++)c[i][j]=inc(c[i-1][j],c[i-1][j-1]);
	}
	for(int i=1;i<=n;i++){
		if(i<=42)f[i]=i;
		else for(int j=1;j<=42;j++)f[i]=(f[i]+(ll)f[i-j]*j)%mod;
		res=(res+(ll)f[i]*c[n-i+k-1][k-1])%mod;
	}
	// for(int i=1;i<=n;i++)print(f[i]," \n"[i==n]);
	// printf(">%d\n",res);
	for(int b=res,a=2;b;b>>=1,a=(ll)a*a%(mod+1))
		if(b&1)ans=(ll)ans*a%(mod+1);
	print(ans,'\n');
}