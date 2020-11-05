#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0;char c=getchar();while(!isdigit(c))c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
}
const int N=3e5+10;
int n,a[N],b[N],c[N],f[N],p[N];
long long m;
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(m);
	for(int i=1,x;i<=n;i++)read(x),a[x]=i;
	for(int i=1,x;i<=n;i++)read(x),b[x]=i;
	for(int i=1;i<=n;i++)p[a[i]]=i;
	for(int i=1;i<=n;i++)if(m){
		if(m>=n-p[i]){
			m-=n-p[i],f[p[i]]=-n;
		}else{
			for(int j=1;j<=n-p[i];j++)c[j]=b[p[i]+j];
			std::sort(c+1,c+n-p[i]+1);
			// for(int j=1;j<=n-p[i];j++)printf("%d%c",c[j]," \n"[j==n-p[i]]);
			f[p[i]]=-c[m+1]+1;
			m=0;
		}
	}else{
		f[p[i]]=n;
	}
	puts("Yes");
	for(int i=1;i<=n;i++)printf("%d%c",f[i]," \n"[i==n]);
	for(int i=1;i<=n;i++)printf("%d%c",b[i]-1," \n"[i==n]);
}