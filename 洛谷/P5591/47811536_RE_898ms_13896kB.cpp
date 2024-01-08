#include<bits/stdc++.h>
using namespace std;
const int N=2e6+1e5+7,p=998244353;
int n,q,k,t,lim,f[N],g[N],wn[N],rev[N];
inline int read(){
	int num=0; char g=getchar(); while(g<48||57<g) g=getchar();
	while(47<g&&g<58) num=(num<<1)+(num<<3)+g-48,g=getchar(); return num;
}
inline long long pows(long long u,int v){
	long long ans=1; while(v>0) {if(v&1) ans=ans*u%p; u=u*u%p,v=v>>1;} return ans;
}
inline int inc(int a,int b){
	if(a+b>=p) return a+b-p; return a+b;
}
inline int mul(int a,int b){
	return 1ll*a*b%p;
}
inline int getit(long long u){
	return (u*(u-1)/2)%k;
}
inline void ntt(int *s){
	for(int i=0;i<lim;i++) if(rev[i]<i) swap(s[i],s[rev[i]]);
	for(int d=1;d<lim;d=d<<1){
		long long w=pows(3,(p-1)/(d<<1));
		for(int i=0,r=d<<1;i<lim;i+=r){
			long long wn=1;
			for(int j=0;j<d;j++,wn=wn*w%p){
				long long a=s[i+j],b=s[i+j+d]*wn%p;
				s[i+j]=inc(a,b),s[i+j+d]=inc(a,p-b);
			}
		}
	}
}
inline void intt(int *s){
	for(int i=0;i<lim;i++) if(rev[i]<i) swap(s[i],s[rev[i]]);
	for(int d=1;d<lim;d=d<<1){
		long long w=pows(332748118,(p-1)/(d<<1));
		for(int i=0,r=d<<1;i<lim;i+=r){
			long long wn=1;
			for(int j=0;j<d;j++,wn=wn*w%p){
				long long a=s[i+j],b=s[i+j+d]*wn%p;
				s[i+j]=inc(a,b),s[i+j+d]=inc(a,p-b);
			}
		}
	}
	long long inv=pows(lim,p-2);
	for(int i=0;i<lim;i++) s[i]=s[i]*inv%p;
}
int main(){
	n=read(),q=read(),k=read();
	lim=1,t=0; while(lim<=(k<<1)) lim=lim<<1,t++;
	for(int i=0;i<lim;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(t-1));
	wn[0]=1,wn[1]=pows(3,(p-1)/k);
	for(int i=2;i<=k;i++) wn[i]=mul(wn[1],wn[i-1]);
	for(int i=0;i<k;i++) f[i]=mul(i,wn[getit(i)]);
	for(int i=0;i<k;i++) g[i]=mul(pows(inc(mul(wn[i],q),1),n),wn[getit(i)]);
	ntt(f),ntt(g); for(int i=0;i<lim;i++) f[i]=1ll*f[i]*g[i]%p; intt(f); int sum=0;
	for(int i=0;i<lim;i++) sum=inc(sum,mul(f[i],wn[k-getit(i)]));
	sum=inc(mul(pows(q+1,n-1),mul(mul(q,n),pows(k,p-2))),p-mul(sum,pows(k,p-3)));
	cout<<sum<<endl;
	return 0;
}