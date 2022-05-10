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
const int N=2e4+10,M=200,mod=998244353;
int n,m,sqn,w[N<<2],rev[N<<2];
int F[N],G[N],S[N],P[N],T[N],R[N],Q[M][N];
inline int dec(int a,int b){return (a-=b)<0?a+mod:a;}
inline int inc(int a,int b){return (a+=b)>=mod?a-mod:a;}
inline int fpow(int a,int b){int s=1;for(;b;b>>=1,a=(ll)a*a%mod)if(b&1)s=(ll)s*a%mod;return s;}
void ntt(int *a,int lim){
	for(int i=0;i<lim;i++)if(i<rev[i])std::swap(a[i],a[rev[i]]);
	for(int len=1;len<lim;len<<=1)
		for(int i=0;i<lim;i+=(len<<1))
			for(int j=0;j<len;j++){
				int x=a[i+j],y=(ll)w[j+len]*a[i+j+len]%mod;
				a[i+j]=inc(x,y),a[i+j+len]=dec(x,y);
			}
}
void mul(int *f,int *g,int *h,int n,int m){
	static int a[N<<2],b[N<<2];
	int lim=1,k=0; while(lim<(n+m))lim<<=1,++k;
	for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
	int ilim=fpow(lim,mod-2);
	memcpy(a,f,n<<2),memset(a+n,0,(lim-n)<<2),ntt(a,lim);
	memcpy(b,g,m<<2),memset(b+m,0,(lim-m)<<2),ntt(b,lim);
	for(int i=0;i<lim;i++)a[i]=(ll)a[i]*b[i]%mod;
	std::reverse(a+1,a+lim),ntt(a,lim);
	for(int i=0;i<lim;i++)h[i]=(ll)a[i]*ilim%mod;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(m),++n,++m,sqn=sqrt(n);
	for(int wn,len=1;len<(n<<1)+3;len<<=1){
		wn=fpow(3,(mod-1)/(len<<1)),w[len]=1;
		for(int i=1;i<len;i++)w[i+len]=(ll)w[i+len-1]*wn%mod;
	}
	for(int i=0;i<n;i++)read(F[i]);
	for(int i=0;i<m;i++)read(G[i]);
	S[0]=P[0]=Q[0][0]=1;
	for(int i=0;i<sqn;i++)mul(S,G,S,n,n);
	for(int i=1;i<sqn;i	++)mul(Q[i-1],G,Q[i],n,n);
	for(int i=0;i*sqn<n;i++){
		memset(T,0,n<<2);
		for(int j=0;j<sqn&&i*sqn+j<n;j++){
			for(int k=0;k<n;k++)T[k]=(T[k]+(ll)F[i*sqn+j]*Q[j][k])%mod;
		}
		// printf("===== %d =====\n",i);
		// for(int i=0;i<n;i++)print(T[i]," \n"[i==n-1]);
		// for(int i=0;i<n;i++)print(P[i]," \n"[i==n-1]);
		mul(T,P,T,n,n),mul(P,S,P,n,n);
		for(int i=0;i<n;i++)R[i]=inc(R[i],T[i]);
	}
	for(int i=0;i<n;i++)print(R[i]," \n"[i==n-1]);
}