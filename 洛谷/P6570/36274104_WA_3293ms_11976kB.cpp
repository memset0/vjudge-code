#include<bits/stdc++.h>
const int S=1<<21; char ibuf[S],*iS,*iT;
#define getchar() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,S,stdin),(iS==iT?EOF:*iS++)):*iS++)
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=1e6+10,M=2.7e5+10,mod=1e9+7;
int n,max,k,lim=1,cnt,a[N],phi[M],vis[M],pri[M];
struct z {
	int x;
	z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}ans,f[M],g[M];
inline z fpow(z a,int b){z s=1;for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;};
int main(){
#ifdef memset0
	freopen("C.in","r",stdin);
#endif
	read(n);
	for(int i=1;i<=n;i++)read(a[i]),max=std::max(max,a[i]),g[a[i]].x++;
	while(lim<=max)lim<<=1,k++;
	fprintf(stderr,"clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
	f[0]=1;
	for(int x=1;x<lim;x++){
		for(int y=x;y;y=(y-1)&x)if((x^y)<y){
			f[x]=f[x]+f[x^y]*g[y];
		}else break;
	}
	fprintf(stderr,"clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
	phi[1]=1;
	for(int i=2;i<=lim;i++){
		if(!vis[i])pri[++cnt]=i,phi[i]=i-1;
		for(int j=1;j<=cnt&&i*pri[j]<=lim;j++){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0){phi[i*pri[j]]=phi[i]*pri[j];break;}
			else phi[i*pri[j]]=phi[i]*(pri[j]-1);
		}
	}
	for(int i=0;i<lim;i++)ans=ans+phi[i+1]*f[i];
	printf("%d\n",ans.x);
	fprintf(stderr,"clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
}