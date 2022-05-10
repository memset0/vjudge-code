#pragma GCC optimize("Ofast")
#pragma GCC target("popcnt,tune=native")
#include<bits/stdc++.h>
const int S=1<<21; char ibuf[S],*iS,*iT;
#define getchar() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,S,stdin),(iS==iT?EOF:*iS++)):*iS++)
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=1e6+10,M=2.7e5+10,mod=1e9+7;
const long long modLimit=10e18;
int n,max,k,lim=1,cnt,ans,g[M],phi[M],vis[M],pri[M];
long long f[M];
int main(){
	read(n);
	for(int i=1,x;i<=n;i++)read(x),max=std::max(max,x),g[x]++;
	while(lim<=max)lim<<=1,k++;
	// fprintf(stderr,"clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
	f[0]=1;
	while(g[0]--){
		f[0]<<=1;
		if(f[0]>(modLimit>>1))f[0]%=mod;
	}
	for(int x=1;x<lim;x++){
		for(int y=x;y;y=(y-1)&x)if((x^y)<y){
			f[x]+=f[x^y]*g[y];
			if(f[x]>modLimit)f[x]%=mod;
		}else break;
		f[x]%=mod;
	}
	// fprintf(stderr,"clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
	phi[1]=1;
	for(int i=2;i<=lim;i++){
		if(!vis[i])pri[++cnt]=i,phi[i]=i-1;
		for(int j=1;j<=cnt&&i*pri[j]<=lim;j++){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0){phi[i*pri[j]]=phi[i]*pri[j];break;}
			else phi[i*pri[j]]=phi[i]*(pri[j]-1);
		}
	}
	for(int i=0;i<lim;i++)ans=(ans+f[i]%mod*phi[i+1])%mod;
	printf("%d\n",ans);
	// fprintf(stderr,"clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
}