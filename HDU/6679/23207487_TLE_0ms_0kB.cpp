#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();if(f)x=-x;
}
const int N=1e5+10,mod=1e9+7;
int T,n,f[N],g[N];
char s[N];
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif	
	for(read(T);T--;){
		scanf("%s",s+1),n=strlen(s+1),f[0]=g[0]=g[n+1]=1;
		for(int i=1;i<=n;i++)g[i]=s[i]=='?';
		for(int i=1;i<=n+1;i++){
			f[i]=0;
			for(int j=0;j<i;j++)
				if((i|j)==i){
					// printf("> %d %d : %d %d\n",i,j,f[j],g[j]);
					f[i]=(f[i]+f[j]*g[j])%mod;
				}
		}
		// for(int i=0;i<=n+1;i++)printf("%d%c",f[i]," \n"[i==n+1]);
		// for(int i=0;i<=n+1;i++)printf("%d%c",g[i]," \n"[i==n+1]);
		printf("%d %d\n",n+1,f[n+1]);
	}
}