#include<bits/stdc++.h>
const int N=1e5+10,mod=1e9+7;
struct z {
	int x;
	z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}f[N];
inline z fpow(z a,int b){z s(1);for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}
int n,m,lim,cnt,pri[N],vis[N];
void fwt(z *a,int lim){
	for(int len=1;len<lim;len<<=1)
		for(int i=0;i<lim;i+=(len<<1))
			for(int j=0;j<len;j++){
				z x=a[i+j],y=a[i+j+len];
				a[i+j]=x+y,a[i+j+len]=x-y;
			}
}
void ifwt(z *a,int lim){
	fwt(a,lim);z inv=fpow(lim,mod-2);
	for(int i=0;i<lim;i++)a[i]=a[i]*inv;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	vis[0]=vis[1]=true;
	for(int i=2;i<=50000;i++){
		if(!vis[i])pri[++cnt]=i;
		for(int j=i+i;j<=50000;j+=i)vis[j]=true;
	}
	while(scanf("%d%d",&n,&m)!=EOF){
		lim=1;while(lim<=m)lim<<=1;
		for(int i=0;i<lim;i++)f[i]=(vis[i]==false)&&(i<=m);
		fwt(f,lim);
		for(int i=0;i<lim;i++)f[i]=fpow(f[i],n);
		ifwt(f,lim);
		printf("%d\n",f[0]);
	}
}