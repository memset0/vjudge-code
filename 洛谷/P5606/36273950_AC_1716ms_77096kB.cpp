#include<bits/stdc++.h>
#define int long long
#define ll long long
#define poly std::vector<int>
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();if(f)x=-x;
}
const int N=4e5+10,mod=998244353;
int n,m,l,ans,min,a[N],c[N],s[N],v[N],pinv[N],w[N<<2],rev[N<<2],f[N],g[N],fac[N],ifac[N];
std::multiset<int> s1,s2;
inline int dec(int a,int b){return (a-=b)<0?a+mod:a;}
inline int inc(int a,int b){return (a+=b)>=mod?a-mod:a;}
inline int fpow(int a,int b){int s=1;for(;b;b>>=1,a=(ll)a*a%mod)if(b&1)s=(ll)s*a%mod;return s;}
void finit(int n){
	pinv[0]=pinv[1]=1;
	for(int i=2;i<=n;i++)pinv[i]=(ll)(mod-mod/i)*pinv[mod%i]%mod;
}
int pinit(int len){
	int lim=1,k=0;while(lim<len)lim<<=1,++k;if(!k)return 1;
	for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
	for(int len=1,wn;len<lim;len<<=1){
		wn=fpow(3,(mod-1)/(len<<1)),w[len]=1;
		for(int i=1;i<len;i++)w[i+len]=(ll)w[i+len-1]*wn%mod;
	}return lim;
}
void dft(poly &a,int lim){
	a.resize(lim);
	for(int i=0;i<lim;i++)if(i<rev[i])std::swap(a[i],a[rev[i]]);
	if(lim>1)for(int i=0;i<lim;i+=2){int x=a[i],y=a[i+1];a[i]=inc(x,y),a[i+1]=dec(x,y);}
	for(int len=2;len<lim;len<<=1)
		for(int i=0;i<lim;i+=len<<1)
			for(int j=0;j<len;j++){
				int x=a[i+j],y=(ll)w[j+len]*a[i+j+len]%mod;
				a[i+j]=inc(x,y),a[i+j+len]=dec(x,y);
			}
}
void idft(poly &a,int lim){
	std::reverse(&a[1],&a[lim]),dft(a,lim);int inv=fpow(lim,mod-2);
	for(int i=0;i<lim;i++)a[i]=(ll)a[i]*inv%mod;
}
poly mul(poly f,poly g,int rlen=-1){
	int len=f.size()+g.size()-1,lim=pinit(len);rlen=~rlen?rlen:len;
	dft(f,lim),dft(g,lim);
	for(int i=0;i<lim;i++)f[i]=(ll)f[i]*g[i]%mod;
	idft(f,lim);return f.resize(rlen),f;
}
poly inv(const poly &f,int len=-1){
	if((len=~len?len:f.size())==1)return poly{fpow(f[0],mod-2)};
	poly a=inv(f,(len+1)>>1),b(&f[0],&f[len]);int lim=pinit(len*2-1);
	dft(a,lim),dft(b,lim);
	for(int i=0;i<lim;i++)a[i]=(ll)a[i]*dec(2,(ll)a[i]*b[i]%mod)%mod;
	idft(a,lim);return a.resize(len),a;
}
poly operator%(const poly &f,const poly &g){
	int len=f.size()-g.size()+1;if(len<0)return f;
	poly a=f;std::reverse(a.begin(),a.end()),a.resize(len);
	poly b=g;std::reverse(b.begin(),b.end()),b.resize(len);
	poly q=mul(a,inv(b),len);std::reverse(q.begin(),q.end());
	poly r=mul(q,g,g.size()-1);for(int i=0;i<r.size();i++)r[i]=dec(f[i],r[i]);
	return r;
}
poly inte(poly f){for(int i=f.size()-1;i;i--)f[i]=(ll)f[i-1]*pinv[i]%mod;return f[0]=0,f;}
poly deri(poly f){for(int i=0;i<f.size()-1;i++)f[i]=(ll)f[i+1]*(i+1)%mod;return f[f.size()-1]=0,f;}
poly ln(poly f,int len=-1){if(~len)f.resize(len);return inte(mul(deri(f),inv(f),f.size()));}
poly exp(const poly &f,int len=-1){
	if((len=~len?len:f.size())==1)return poly{1};
	poly a=exp(f,(len+1)>>1),b=ln(a,len);
	for(int i=0;i<len;i++)if(b[i])b[i]=mod-b[i];b[0]=inc(b[0],1);
	for(int i=0;i<len&&i<f.size();i++)b[i]=inc(b[i],f[i]);return mul(a,b,len);
}
poly P[N<<2],R;
void segbuild(int u,int l,int r){
	if(l==r){P[u]=poly{dec(0,R[l]),1};return;}
	int mid=(l+r)>>1;
	segbuild(u<<1,l,mid);
	segbuild(u<<1|1,mid+1,r);
	P[u]=mul(P[u<<1],P[u<<1|1]);
}
void MPE(int u,int l,int r,const poly &a){
	if(l==r){R[l]=a[0];return;}
	int mid=(l+r)>>1;
	MPE(u<<1,l,mid,a%P[u<<1]);
	MPE(u<<1|1,mid+1,r,a%P[u<<1|1]);
}
poly MPE(poly a,poly b){
	int l=std::max(a.size(),b.size()),rlen=b.size();
	a.resize(l),b.resize(l),R=b;segbuild(1,0,l-1),MPE(1,0,l-1,a);
	return R.resize(rlen),R;
}
void facinit(int n){
	fac[0]=fac[1]=ifac[0]=ifac[1]=1;
	for(int i=2;i<n;i++)fac[i]=(ll)fac[i-1]*i%mod;
	for(int i=2;i<n;i++)ifac[i]=(ll)(mod-mod/i)*ifac[mod%i]%mod;
	for(int i=2;i<n;i++)ifac[i]=(ll)ifac[i-1]*ifac[i]%mod;
}
poly dc(int l,int r){
	if(l==r){return poly{s[l],1};}
	int mid=(l+r)>>1;
	return mul(dc(l,mid),dc(mid+1,r));
}
void solve(std::multiset<int> &set,int *res){
	m=0,min=1000000000;poly k(1),F,G,H;
	if(set.size()==0){res[0]=1;return;}
	if(set.size()==1){res[1]=1;return;}
	while(set.size()>1)
		if((ll)(*set.begin())*(*--set.end())<=l){
			a[++m]=*set.begin(),c[m]=1,set.erase(set.begin());
		}else{
			a[++m]=*--set.end(),c[m]=-1,set.erase(--set.end());
		}
	a[++m]=*set.begin();
	for(int i=2;i<=m;i++)s[i]=s[i-1]+c[i-1],min=std::min(min,s[i]);
	for(int i=1;i<=n;i++)k.push_back(i);
	// for(int i=1;i<=m;i++)printf("%d%c",a[i]," \n"[i==m]);
	// for(int i=1;i<=m;i++)printf("%d%c",c[i]," \n"[i==m]);
	// for(int i=1;i<=m;i++)printf("%d%c",s[i]," \n"[i==m]);
	F=MPE(dc(1,m),k),G.resize(n+1);
	if(min<0)for(int i=1;i<=-min;i++)F[i]=0;
	// for(int i=1;i<=n;i++)printf("%d%c",F[i]," \n"[i==n]);
	for(int i=1;i<=n;i++)F[i]=(ll)(i&1?mod-F[i]:F[i])*ifac[i]%mod;
	for(int i=0;i<=n;i++)G[i]=ifac[i];
	// for(int i=0;i<n;i++)printf("%d%c",G[i]," \n"[i==n-1]);
	H=mul(F,G,n+1);
	for(int i=1;i<=n;i++)res[i]=(ll)H[i]*fac[i]%mod*(i&1?mod-1:1)%mod;
}
signed  main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(l),facinit(n+5);
	for(int i=1;i<=n;i++)read(v[i]),(v[i]>=0?s1:s2).insert(std::abs(v[i]));
	solve(s1,f),solve(s2,g);
	// for(int i=0;i<=n;i++)printf("%d%c",f[i]," \n"[i==n]);
	// for(int i=0;i<=n;i++)printf("%d%c",g[i]," \n"[i==n]);
	for(int i=1;i<=n;i++)ans=(ans+2ll*f[i]*g[i]%mod+(ll)f[i]*g[i-1]%mod+(ll)f[i-1]*g[i]%mod)%mod;
	std::cout<<ans<<std::endl;
}