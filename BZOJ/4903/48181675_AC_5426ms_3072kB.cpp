#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0;register char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
}
const int N=3e5,mod=1e9+7;
int n,k,max,lim=1,c[20],a[N],f[N],g[N];
inline int inc(int a,int b){return (a+=b)>=mod?a-mod:a;}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n);
	for(int i=1;i<=n;i++){
		read(a[i]),max=std::max(max,a[i]);
		g[a[i]]=i,f[a[i]]=1;
	}
	while(lim<=max)lim<<=1,++k;
	for(int x=lim-1;x>=0;x--)if(f[x]&&g[x]){
		for(int y=x&(x-1);y;y=x&(y-1))
			if(g[y]>g[x]){
				// printf("%d -> %d : %d\n",x,y,f[x]);
				f[y]=inc(f[x],f[y]);
			}
		f[0]=inc(f[0],f[x]-1);
	}
	printf("%d\n",f[0]);
}