#include<bits/stdc++.h>
const int N=8e5+10,mod=998244353;
int n,k,R[N];
struct z{
    int x;
    z(int x=0):x(x){}
    friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
    friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
    friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}res,W[N],fc[N],fi[N],F[N],G[N],H[N];
inline z fpow(z a,int b){z s(1);for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}
void initfac(int n){
	fc[0]=fc[1]=fi[0]=fi[1]=1;
	for(int i=2;i<=n;i++)fc[i]=fc[i-1]*i;
	for(int i=2;i<=n;i++)fi[i]=(mod-mod/i)*fi[mod%i];
	for(int i=2;i<=n;i++)fi[i]=fi[i-1]*fi[i];
}
void ntt(z *a,int lim){
	for(int i=0;i<lim;i++)if(i<R[i])std::swap(a[i],a[R[i]]);
	for(int len=1;len<lim;len<<=1)
		for(int i=0;i<lim;i+=(len<<1))
			for(int j=0;j<len;j++){
				z x=a[i+j],y=a[i+j+len]*W[j+len];
				a[i+j]=x+y,a[i+j+len]=x-y;
			}
}
int init(int len){
	int lim=1,k=0;while(lim<=len)lim<<=1,++k;
	for(int i=0;i<lim;i++)R[i]=(R[i>>1]>>1)|((i&1)<<(k-1));
	for(int len=1;len<lim;len<<=1){
		z w=fpow(3,(mod-1)/(len<<1)); W[len]=1;
		for(int i=1;i<len;i++)W[i+len]=W[i+len-1]*w;
	}
	return lim;
}
void mul(z *a,z *b,int lim){
	z inv=fpow(lim,mod-2);
	ntt(a,lim),ntt(b,lim);
	for(int i=0;i<lim;i++)a[i]=a[i]*b[i];
	std::reverse(a+1,a+lim),ntt(a,lim);
	for(int i=0;i<lim;i++)a[i]=a[i]*inv;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	scanf("%d%d",&n,&k),--n,initfac(k),H[0]=1;
	for(int i=0;i<=k;i++)F[i]=fpow(i,k)*fi[i];
	for(int i=0;i<=k;i++)G[i]=(i&1?mod-1:1)*fi[i];
	mul(F,G,init((k<<1)+2));
	for(int i=1;i<=k;i++)H[i]=H[i-1]*(n-i+1);
	for(int i=0;i<=k&&i<=n;i++)res=res+F[i]*H[i]*fpow(2,n-i);
	printf("%d\n",res*(n+1)*fpow(2,(long long)n*(n-1)/2%(mod-1)));
}