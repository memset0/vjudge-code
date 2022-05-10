// luogu-judger-enable-o2
#include<bits/stdc++.h>
#define ll long long
#define poly std::vector<int>
template<class T>inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	if(f)x=-x;
}
template<class T>inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10+'0');
}
template<class T>inline void print(T x,char c){print(x),putchar(c);}
template<class T>inline void print(T x,int l,int r){for(int i=l;i<r;i++)print(x[i]," \n"[i==r-1]);}

const int N=1e5+10,mod=998244353;
int n,m;
poly a,b;

int pinv[N],w[N<<2],rev[N<<2];
inline int dec(int a,int b){return (a-=b)<0?a+mod:a;}
inline int inc(int a,int b){return (a+=b)>=mod?a-mod:a;}
inline int fpow(int a,int b){int s=1;for(;b;b>>=1,a=(ll)a*a%mod)if(b&1)s=(ll)s*a%mod;return s;}
void finit(int n){
	pinv[0]=pinv[1]=1;
	for(int i=2;i<=n;i++)pinv[i]=(ll)(mod-mod/i)*pinv[mod%i]%mod;
}
int pinit(int len){
	int lim=1,k=0;while(lim<len)lim<<=1,++k;
	for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
	for(int len=1,wn;len<lim;len<<=1){
		wn=fpow(3,(mod-1)/(len<<1)),w[len]=1;
		for(int i=1;i<len;i++)w[i+len]=(ll)w[i+len-1]*wn%mod;
	}return lim;
}
void dft(poly &a,int lim){
	a.resize(lim);
	for(int i=0;i<lim;i++)if(i<rev[i])std::swap(a[i],a[rev[i]]);
	// for(int i=0;i<lim;i+=2){int x=a[i],y=a[i+1];a[i]=inc(x,y),a[i+1]=dec(x,y);}
	for(int len=1;len<lim;len<<=1)
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
	idft(a,lim);return a.resize(lim),a;
}
poly inte(poly f){for(int i=f.size()-1;i;i--)f[i]=(ll)f[i-1]*pinv[i]%mod;return f[0]=0,f;}
poly deri(poly f){for(int i=0;i<f.size()-1;i++)f[i]=(ll)f[i+1]*(i+1)%mod;return f[f.size()-1]=0,f;}
poly ln(const poly &f){return inte(mul(deri(f),inv(f),f.size()));}

int main(){
	freopen("1.in","r",stdin);
	read(n),finit(n+5),a.resize(n);
	for(int i=0;i<n;i++)read(a[i]);
	print(inv(a),0,n);
}