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
const int N=21,mod=998244353;
int n,m,lim,ifac[N],G[N][N],F[1<<20][20];
std::bitset<20> A[20];
int fpow(int a,int b){int s=1;for(;b;b>>=1,a=(ll)a*a%mod)if(b&1)s=(ll)s*a%mod;return s;}
int rank(std::bitset<20> *a,int n){
	for(int i=0,j;i<n;i++){
		for(j=i;j<n;j++)if(a[j][i])break;
		if(j==n)return n-i; if(i!=j)std::swap(a[i],a[j]);
		for(int j=i+1;j<n;j++)if(a[j][i])a[j]^=a[i];
	}
	return 0;
}
int euler(int s){
	std::vector<int> id;
	for(int i=1;i<=n;i++)if((s>>(i-1))&1)id.push_back(i);
	for(int i=0;i<id.size();i++)
		for(int j=0;j<id.size();j++)
			A[i][j]=G[id[i]][id[j]];
	printf("euler %d : ",s); print(id,0,id.size());
	for(int i=0;i<id.size();i++)print(A[i],0,id.size());
	int res=fpow(2,rank(A,id.size()));
	for(int i=0;i<id.size();i++)print(A[i],0,id.size());
	printf(">> %d\n",res);
	return res;
}
void array_dec(int *a,int *b,int n){for(int i=0;i<n;i++)if((a[i]-=b[i])<0)a[i]+=mod;}
void array_add(int *a,int *b,int n){for(int i=0;i<n;i++)if((a[i]+=b[i])>=mod)a[i]-=mod;}
void fwt(int a[1<<20][20],int n,int lim){
	for(int len=1;len<lim;len<<=1)
		for(int i=0;i<lim;i+=len<<1){
			for(int j=0;j<len;j++)array_add(a[i+j+len],a[i+j],n);
		}
}
void ifwt(int a[1<<20][20],int n,int lim){
	for(int len=1;len<lim;len<<=1)
		for(int i=0;i<lim;i+=len<<1){
			for(int j=0;j<len;j++)array_dec(a[i+j+len],a[i+j],n);
		}
}
void ln(int *f,int n){
	int g[20],s[20],t[20];memset(g,0,n<<2),memset(s,0,n<<2),s[0]=1;
	for(int k=1;k<n;k++){
		memset(t,0,n<<2);
		for(int i=k-1;i<n;i++)for(int j=1;i+j<n;j++)t[i+j]=(t[i+j]+(ll)s[i]*f[j])%mod;
		for(int i=0;i<n;i++)s[i]=t[i],g[i]=(g[i]+(ll)ifac[k]*s[i])%mod;
	}
	for(int i=0;i<n;i++)f[i]=g[i];
}
int main(){
	freopen("1.in","r",stdin);
	read(n),read(m),ifac[0]=ifac[1]=1;
	for(int i=2;i<n;i++)ifac[i]=(ll)(mod-mod/i)*ifac[mod%i]%mod;
	for(int i=2;i<n;i++)ifac[i]=(ll)ifac[i-1]*ifac[i]%mod;
	for(int u,v,i=1;i<=m;i++)read(u),read(v),E[i]=std::make_pair(u,v),G[u][v]=G[v][u]=1;
	for(int i=0;i<(1<<n);i++)F[i][__builtin_popcount(i)]=euler(i);
	for(int i=0;i<(1<<n);i++)printf("%d : %d\n",i,F[i][__builtin_popcount(i)]);
	fwt(F,n,1<<n);
	for(int i=0;i<(1<<n);i++)ln(F[i],n);
	ifwt(F,n,1<<n);
	printf("%d\n",F[(1<<n)-1][n]);
}