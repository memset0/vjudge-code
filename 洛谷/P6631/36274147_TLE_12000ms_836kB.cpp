#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=1e5+10;
int T,n;
long long ans,a[N],c[3];
int main(){
	freopen("1.in","r",stdin);
	for(read(T);T--;){
		read(n);
		for(int i=1;i<=n;i++)read(a[i]);
		a[n+1]=a[n+2]=a[n+3]=a[n+4]=ans=0,n+=2;
		// for(int i=1;i<=n;i++)printf("%lld%c",a[i]," \n"[i==n]);
		for(int i=n;i>=1;i--)if(i-2>=1)a[i]-=a[i-2];
		// for(int i=1;i<=n;i++)printf("%lld%c",a[i]," \n"[i==n]);
		for(int i=1;i<=n;){
			// printf("i=%d u=%lld v=%lld c0=%lld c1=%lld c2=%lld ans=%lld\n",i,a[i],a[i+1],c[0],c[1],c[2],ans);
			if(a[i]>0&&a[i+1]>0){
				long long x=std::min(a[i],a[i+1]);
				a[i]-=x,a[i+1]-=x,c[2]+=x;
			}else if(a[i]<0&&a[i+1]<0&&c[2]>0){
				long long x=std::min(c[2],std::min(-a[i],-a[i+1]));
				a[i]+=x,a[i+1]+=x,c[2]-=x,ans+=x;
			}else if(a[i]>0){
				long long x=a[i];
				a[i]-=x,c[i&1]+=x;
			}else if(a[i]<0&&c[i&1]>0){
				long long x=std::min(-a[i],c[i&1]);
				a[i]+=x,c[i&1]-=x,ans+=x;
			}else if(a[i]<0&&c[2]>0){
				long long x=std::min(-a[i],c[2]);
				a[i]+=x,c[2]-=x,c[(i&1)^1]+=x,ans+=x;
			}else{
				puts("awsl!!!");
				break;
			}
			while(!a[i]&&i<=n)i++;
		}
		printf("%lld\n",ans);
	}
}