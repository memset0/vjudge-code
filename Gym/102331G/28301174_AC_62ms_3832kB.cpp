#include<bits/stdc++.h>
#define log(...) (void(0))
// #define log(...) fprintf(stderr,__VA_ARGS__)
#define debug log("\33[2mPassing [%s] in LINE %d\33[0m\n",__FUNCTION__,__LINE__);
const int N=3e5+10,mod=998244353;
int n;
char a[N];
struct z {
	int x;
	z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}ans,fac[N],ifac[N],cnt[N];
inline z C(int n,int m){return n<m?0:fac[n]*ifac[m]*ifac[n-m];}
inline z F(int n,int m){return C(n+1,m+1);}
inline z G(int i,int j){return F(n-1,i-1)-F(n-j-1,i-1);}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	scanf("%s",a+1),n=strlen(a+1);
	bool fl=1;
	for(int i=1;i<=n;i++)fl&=a[i]==a[1];
	if(fl){
		printf("%d\n",n);
		return 0;
	}
	fac[0]=ifac[0]=ifac[1]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
	for(int i=2;i<=n;i++)ifac[i]=(mod-mod/i)*ifac[mod%i];
	for(int i=1;i<=n;i++)ifac[i]=ifac[i-1]*ifac[i];
	for(int i=1;i<=n;i++)ans=ans+G(i,n-i+1);
	log("%d\n",ans);
	for(int i=1;i<=n;i++)if(a[i]!=a[i-1]&&a[i]==a[i+1]){
		int len=0;
		for(int j=1;j<=n;j++)if(a[i]==a[i+j-1]){
			++len;
		}else break;
		for(int j=1;j<=len;j++){
			ans=ans-G(i+j-1,len-j+1);
			log("> [%d %d] : %d\n",j,j+len-1,G(j,len-j+1));
		}
	}
	log("%d\n",ans);
	for(int i=2;i<=n;i++)if(a[i]!=a[i-1]&&a[i]==a[i+1]){
		for(int j=1;j<n;j++)if(a[i]==a[i+j-1]){
			ans=ans+C(n-j-1,i-2)*j;
			log("[%d %d] %d %d\n",i,i+j-1,j,C(n-j-1,i-2));
		}else break;
	}
	log("%d\n",ans);
	for(int i=1;i<=n-1;i++)if(a[i]==a[i-1]&&a[i]!=a[i+1]){
		for(int j=1;j<n;j++)if(a[i]==a[i-j+1]){
			ans=ans+C(n-j-1,n-i-1)*j;
			log("[%d %d] %d %d\n",i-j+1,i,j,C(n-j-1,n-i-1));
		}else break;
	}
	printf("%d\n",ans);
}