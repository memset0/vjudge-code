#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();if(f)x=-x;
}
const int N=4e6+10,mod=1e9+7;
int T,n,lim,ans,f[N],g[N];
char s[N];
inline void update(int &a,int b){a+=b;if(a>=mod)a-=mod;}
void solve(int l,int r){
	if(l+1==r){
		// printf("> %d %d\n",l,f[l]);
		if(l==n+1)ans=f[l];
		return;
	}
	int mid=(l+r)>>1;
	// printf(">> [%d %d] [%d %d]\n",l,mid-1,mid,r-1);
	solve(l,mid);
	for(int i=l,j=mid;i<mid;i++,j++)update(f[j],f[i]*g[j]);
	solve(mid,r);
	for(int i=l,j=mid;i<mid;i++,j++)update(f[j],f[i]);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif	
	for(read(T);T--;){
		scanf("%s",s+1),n=strlen(s+1),lim=1;
		while(lim<=n+1)lim<<=1;
		memset(f,0,lim<<2),memset(g,0,lim<<2);
		f[0]=1,g[n+1]=1,ans=-1;
		for(int i=1;i<=n;i++)g[i]=s[i]=='?';
		solve(0,lim);
		// for(int i=0;i<lim;i++)printf("%d%c",f[i]," \n"[i==lim-1]);
		printf("%d %d\n",n+1,ans);
	}
} // 123 