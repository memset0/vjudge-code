#include<bits/stdc++.h>
#define ll long long
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
template<class T> inline void print(T a,int l,int r){for(int i=l;i<r;i++)print(a[i]," \n"[i==r-1]);}
const int N=25,mod=998244353;
int n,m,lim,inv[N],G[N][N],F[1<<20][21];
std::bitset<190> A[20];
inline int dec(int a,int b){return (a-=b)<0?a+mod:a;}
inline int inc(int a,int b){return (a+=b)>=mod?a-mod:a;}
int fpow(int a,int b){int s=1;for(;b;b>>=1,a=(ll)a*a%mod)if(b&1)s=(ll)s*a%mod;return s;}
int rank(std::bitset<190> *a,int n,int m){
	int i=0,j,u=0; for(;i<m&&u<n;i++,u++){
		for(j=u;j<n;j++)if(a[j][i])break;
		if(j==n){u--;continue;} if(u!=j)std::swap(a[u],a[j]);
		for(int j=u+1;j<n;j++)if(a[j][i])a[j]^=a[u];
	}
	return std::max(0,m-u);
}
int euler(int s){
	std::vector<int> id; int m=0;
	for(int i=1;i<=n;i++)if((s>>(i-1))&1)id.push_back(i);
	for(int i=0;i<id.size();i++)A[i].reset();
	for(int i=0;i<id.size();i++)
		for(int j=i+1;j<id.size();j++){
			if(G[id[i]][id[j]])A[i][m]=A[j][m]=1,++m;
		}
	// if(s==31){
	// 	printf("euler %d : ",s); print(id,0,id.size());
	// 	for(int i=0;i<id.size();i++)print(A[i],0,m);
	// }
	int res=rank(A,id.size(),m);
	// if(s==31){
	// 	for(int i=0;i<id.size();i++)print(A[i],0,m);
	// 	printf(">> %d\n",res);
	// }
	return fpow(2,res);
}
void array_dec(int *a,int *b,int n){for(int i=0;i<=n;i++)a[i]=dec(a[i],b[i]);}
void array_add(int *a,int *b,int n){for(int i=0;i<=n;i++)a[i]=inc(a[i],b[i]);}
void fwt(int a[1<<20][21],int n,int lim){
	for(int len=1;len<lim;len<<=1)
		for(int i=0;i<lim;i+=len<<1){
			for(int j=0;j<len;j++)array_add(a[i+j+len],a[i+j],n);
		}
}
void ifwt(int a[1<<20][21],int n,int lim){
	for(int len=1;len<lim;len<<=1)
		for(int i=0;i<lim;i+=len<<1){
			for(int j=0;j<len;j++)array_dec(a[i+j+len],a[i+j],n);
		}
}
void ln(int *f,int n){
	static int g[N]; g[n]=0;
	for(int i=0;i<n;i++)g[i]=(ll)(i+1)*f[i+1]%mod;
	for(int i=0;i<=n;i++){
		for(int j=1;j<=i;j++)g[i]=dec(g[i],(ll)g[i-j]*f[j]%mod);
	}
	for(int i=1;i<=n;i++)f[i]=(ll)g[i-1]*inv[i]%mod;
	// print(f,0,n+1);
}
int main(){
	// freopen("1.in","r",stdin);
	// freopen("1.out","w",stdout);
	read(n),read(m),inv[0]=inv[1]=1;
	for(int i=2;i<N;i++)inv[i]=(ll)(mod-mod/i)*inv[mod%i]%mod;
	for(int u,v,i=1;i<=m;i++)read(u),read(v),G[u][v]=G[v][u]=1;
	for(int i=0;i<(1<<n);i++)F[i][__builtin_popcount(i)]=euler(i);
	// for(int i=0;i<(1<<n);i++)printf("%d : %d\n",i,F[i][__builtin_popcount(i)]);
	fwt(F,n,1<<n);
	for(int i=0;i<(1<<n);i++)ln(F[i],n);
	ifwt(F,n,1<<n);
	printf("%d\n",F[(1<<n)-1][n]);
}
