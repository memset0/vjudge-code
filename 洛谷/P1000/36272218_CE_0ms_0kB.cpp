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
const int N=1e5+10,K=6,mod=998244353;
int n,k,m,lim,c[K],d[K];
inline int inc(int a,int b){return (a+=b)>=mod?a-mod:a;}
struct vec{
	int a[K];
	inline void clear(){memset(a,0,24);}
	inline void move(int j){
		static int b[K];
		for(int i=0;i+j<k;i++)b[i+j]=a[i];
		for(int i=k-j;i<k;i++)b[i+j-k]=a[i];
		// std::cout<<"move "<<j<<std::endl;
		// for(int i=0;i<k;i++)print(a[i]," \n"[i==k-1]);
		for(int i=0;i<k;i++)a[i]=b[i];
		// for(int i=0;i<k;i++)print(a[i]," \n"[i==k-1]);
	}
	inline void trans(){
		for(int i=0;i<k;i++)print(a[i]," \n"[i==k-1]);
	}
}f[N],p[K];
inline vec operator+(const vec &a,const vec &b){
	vec c;
	for(int i=0;i<k;i++)c.a[i]=inc(a.a[i],b.a[i]);
	return c;
}
inline vec operator*(const vec &a,const vec &b){
	vec c; c.clear();
	for(int i=0;i<k;i++){
		for(int j=0;i+j<k;j++)c.a[i+j]=(c.a[i+j]+(ll)a.a[i]*b.a[j])%mod;
		for(int j=k-i;j<k;j++)c.a[i+j-k]=(c.a[i+j-k]+(ll)a.a[i]*b.a[j])%mod;
	}
	return c;
}
inline vec fpow(vec a,int b){
	vec s; s.clear(),s.a[0]=1;
	for(;b;b>>=1,a=a*a)if(b&1)s=s*a;
	return s;
}
void fwt(vec *a){
	static vec b[K],d[K];
	for(int len=1;len<lim;len*=k)
		for(int i=0;i<lim;i+=len*k)
			for(int j=0;j<len;j++){
				for(int p=0;p<k;p++)b[p]=a[i+j+p*len],d[p].clear();
				// puts("-----");
				for(int c=0;c<k;c++){
					// for(int p=0;p<k;p++)b[p].trans();
					for(int p=0;p<k;p++)d[c]=d[c]+b[p];
					for(int p=1;p<k;p++)b[p].move(k-p);
				}
				// for(int p=0;p<k;p++)d[p].trans();
				// puts("-----");
				for(int p=0;p<k;p++)a[i+j+p*len]=d[p];
			}
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(k),read(m);
	lim=1; for(int t=m;t--;)lim*=k;
	for(int i=1,x;i<=n;i++)read(x),++c[x%k];
	for(int i=0;i<k;i++)++cp[i].a[0],++p[i].a[i];
	for(int i=0;i<lim;i++){
		memset(d,0,k<<2);
		for(int j=0;j<k;j++)d[i*j%k]+=c[j];
		f[i].a[0]=1;
		for(int j=0;j<k;j++)print(d[j]," \n"[j==k-1]);
		for(int j=0;j<k;j++)if(d[j])f[i]=f[i]*fpow(p[j],d[j]);
	}
	puts("=====");
	for(int i=0;i<lim;i++)f[i].trans();
	fwt(f);
	for(int i=0;i<lim;i++)f[i].trans();
	// for(int i=0;i<lim;i++)print(f[i].trans(),'\n');
}