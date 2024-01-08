#include<bits/stdc++.h>
using namespace std;
const int mod=999983;
const int AD=4e5+1,N=50;
int T,n,K,l,s[N+10],fl[(AD<<1)+10],tim,prt[N+10];
int main(){
	scanf("%d",&T);
	while(T--){
		++tim;
		scanf("%d%d%d",&n,&K,&l);
		for(int i=1;i<=l;++i){
			scanf("%d",&s[i]);
			if(fl[s[i]+AD]!=tim){
				fl[s[i]+AD]=tim;
			}else{
				--i,--l;
			}
		}
		if(l>K){
			puts("0");
			continue;
		}
		printf("%d\n",n);
		for(int i=0;i<=l;++i)prt[i]=(!i);
		for(int i=1;i<=l;++i){
			for(int j=i;j>=0;--j){
				if(j)prt[j]=(1ll*(-s[i]+mod)*prt[j]+prt[j-1])%mod;
				else prt[j]=1ll*prt[j]*(-s[i]+mod)%mod;
			}
		}
		for(int i=1;i<=n;++i){
			printf("%d ",l);
			for(int j=l;j>=0;--j)printf("%lld%c",1ll*prt[j]*i%mod," \n"[!j]);
		}
	}
	return 0;
}