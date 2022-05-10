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

const int N=2010,mod=998244352;
int n,k,s=1,f[N][N];

inline int inc(int a,int b){return (a+=b)>=mod?a-mod:a;}

int main(){
	freopen("1.in","r",stdin);
	read(n),read(k);
	for(int i=1;i<=42;i++)f[i][0]=i;
	for(int i=43;i<=n;i++){
		for(int j=1;j<=42;j++)f[i][0]=(f[i][0]+(ll)f[i-j][0]*j)%mod;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=k;j++){
			f[i][j]=inc(f[i-1][j],f[i][j-1]);
		}
	}
	for(int b=f[n][k],a=2;b;b>>=1,a=(ll)a*a%(mod+1))
		if(b&1)s=(ll)s*a%(mod+1);
	print(s,'\n');
}