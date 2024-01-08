#include<bits/stdc++.h>

const int S=1<<21; char ibuf[S],*iS,*iT,obuf[S],*oS=obuf,*oT=oS+S-1;
#define flush() (fwrite(obuf,1,oS-obuf,stdout),oS=obuf,void())
#define getchar() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,S,stdin),(iS==iT?EOF:*iS++)):*iS++)
#define putchar(x) (*oS++=(x),oS==oT?flush():void())
struct Flusher_{~Flusher_(){flush();}}flusher_;

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
template<class T> inline T gcd(T n,T m){return m?gcd(m,n%m):n;}

const int N=1e5+10;
int T,n,k;
long long a,b,g;

inline bool check(long long a,long long b){
	return k==1?0:(k-1)*a+1>=b;
}

int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#else
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
#endif
	for(read(T);T--;){
		read(a),read(b),read(k),g=gcd(a,b),a/=g,b/=g;
		// puts(check(std::min(a,b),std::max(a,b))?"OBEY":"REBEL");
		puts(check(std::min(a,b),std::max(a,b))?"Yes":"No");
	}
}