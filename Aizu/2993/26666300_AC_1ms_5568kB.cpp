#include<bits/stdc++.h>
typedef long long i64;
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=3e5+10,mod=998244353;
int n,p[N],cnt[N],vis[N];
struct z{
	int x;
	z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}w,ans;
inline z fpow(z a,int b){z s=1;for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}
int length(int u){vis[u]=1; return (vis[p[u]]?0:length(p[u]))+1;}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n);
	for(int i=1;i<=n;i++)read(p[i]);
	for(int i=1;i<=n;i++)if(!vis[i])cnt[length(i)]++;
	if(!cnt[1]&&!cnt[2]){puts("0"); return 0;}
	if(!cnt[1])for(int i=1;i<=n;i+=2)if(cnt[i]){puts("0"); return 0;}
	for(int i=1;i<=n;i++)if(cnt[i]){
		if(i==1)ans=cnt[i]==1?1:fpow(cnt[i],cnt[i]-2);
		else if(i==2&&!cnt[1])ans=fpow(cnt[i],cnt[i]-1)*fpow(i,cnt[i]-1);
		else{
			w=0;
			for(int j=1;j*j<=i;j++)if(i%j==0){
				w=w+j*cnt[j];
				if(j*j!=i&&j!=1)w=w+(i/j)*cnt[i/j];
			}
			ans=ans*w*fpow(w+i*cnt[i],cnt[i]-1);
		}
		// printf("%d %d %d\n",i,cnt[i],(int&)ans);
	}
	printf("%d\n",(int&)ans);
}