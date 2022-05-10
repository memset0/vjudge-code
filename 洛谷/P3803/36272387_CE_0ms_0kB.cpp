#include<bits/stdc++.h>
#define log(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
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
namespace mem{
	const int N=1<<21;
	int n,m,a[N],b[N],w[N],rev[N];
	inline int dec(int a,int b){return (a-=b)<0&&(a+=mod),a;}
	inline int inc(int a,int b){return (a+=b)>=mod&&(a-=mod),a;}
	int dft_init(int len){
		int lim=1,k=0; while(lim<len)lim<<=1,++k;
		for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
		for(int len=1;len<lim;len<<=1){
			int wn=fpow(3,(mod-1)/(len<<1)); w[len]=1;
			for(int i=1;i<len;i++)w[i+len]=(long long)w[i+len-1]*wn%mod;
		}
		return lim;
	}
	void dft(int *a,int lim){
		for(int i=0;i<lim;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
		for(int len=1;len<lim;len<<=1)
			for(int i=0;i<lim;i+=(len<<1))
				for(int j=0;j<len;j++){
					int x=a[i+j],y=(long long)a[i+j+len]*w[j+len]%mod;
					a[i+j]=inc(x,y),a[i+j+len]=dec(x,y);
				}
	}
	void aknoip(){
		read(n),read(m),++n,++m;
		for(int i=0;i<n;i++)read(a[i]);
		for(int i=0;i<m;i++)read(b[i]);
		int lim=dft_init(n+m-1);
		dft(a,lim),dft(b,lim);
		for(int i=0;i<lim;i++)a[i]=(long long)a[i]*b[i]%mod;
		dft(a,lim),reverse(a+1,a+lim);
		int inv_lim=fpow(lim,mod-2);
		for(int i=0;i<n+m;i++)print((long long)a[i]*inv_lim%mod," \n"[i+1==n+m]);
	}
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	return mem::aknoip(),0;
}