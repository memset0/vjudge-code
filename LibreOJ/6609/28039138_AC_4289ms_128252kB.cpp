#include<bits/stdc++.h>
const int N=2e6+10,M=4.2e6,mod=943718401;
int n,k,lim=1,rev[M];
long long m;
struct z{
	int x;
	z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}ans,fac[N<<1],dec[N<<1],fic[N<<1],pw2[N],pi2[N],f[M],g[M],w[M];
inline z fpow(z a,int b){z f=1;for(;b;b>>=1,a=a*a)if(b&1)f=f*a;return f;}
void dft(z *a){
	for(int i=0;i<lim;i++)if(i<rev[i])std::swap(a[i],a[rev[i]]);
	for(int len=1;len<lim;len<<=1)
		for(int i=0;i<lim;i+=(len<<1))
			for(int j=0;j<len;j++){
				z x=a[i+j],y=a[i+j+len]*w[j+len];
				a[i+j]=x+y,a[i+j+len]=x-y;
			}
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	scanf("%d%lld",&n,&m);
	pi2[0]=pw2[0]=dec[0]=fac[0]=fic[0]=fic[1]=1;
	for(int i=2;i<=(n<<1);i++)fic[i]=(mod-mod/i)*fic[mod%i];
	for(int i=1;i<=(n<<1);i++)fac[i]=fac[i-1]*i,fic[i]=fic[i-1]*fic[i],dec[i]=dec[i-1]*((m-i+1)%mod);
	for(int i=1;i<=n;i++)pw2[i]=pw2[i-1]+pw2[i-1],pi2[i]=pi2[i-1]*((mod+1)>>1);
	for(int i=0;i<=n;i++)f[i]=fac[(n-i)<<1]*pw2[i]*(i&1?mod-1:1)*fic[i]*fic[n-i],g[i]=fic[i];
	while(lim<=(n<<1))lim<<=1,++k;
	for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
	for(int len=1;len<lim;len<<=1){
		z wn=fpow(7,(mod-1)/(len<<1)); w[len]=1;
		for(int i=1;i<len;i++)w[i+len]=w[i+len-1]*wn;
	}
	dft(f),dft(g);
	for(int i=0;i<lim;i++)f[i]=f[i]*g[i];
	dft(f),std::reverse(f+1,f+lim);
	for(int i=0;i<=n;i++)ans=ans+dec[(n<<1)-i]*pi2[i]*f[i]*fic[(n-i)<<1];
	printf("%d\n",(ans*fac[n]*pi2[n]*fpow(lim,mod-2)).x);
}
