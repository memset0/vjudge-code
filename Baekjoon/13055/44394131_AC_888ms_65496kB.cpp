#include<bits/stdc++.h>
using namespace std;

#define Mod(x) (x>=P)&&(x-=P)
#define rep(i,a,b) for(ll i=a,i##end=b;i<=i##end;++i)
#define drep(i,a,b) for(ll i=a,i##end=b;i>=i##end;--i)

typedef long long ll;
char IO;
ll rd(ll res=0){
	bool f=0;
	while(IO=getchar(),IO<48||IO>57)
		f|=IO=='-';
	do res=(res<<1)+(res<<3)+(IO^48);
	while(IO=getchar(),isdigit(IO));
	return f?-res:res;
}
const int  M=5e6+10,P=998244353;
int A[M],B[M];
int rev[M];
int Pow(int a,int b){
	int res=1;
	for(;b;b>>=1,a=1ll*a*a%P)
		if(b&1)res=1ll*res*a%P;
	return res;
}
void NTT(int *a,int len,int Ty){
	rep(i,0,len-1)if(i<rev[i])swap(a[i],a[rev[i]]);
	for(int w=1;w<len;w<<=1){
		int h=Pow(3,(P-1)/w/2);
		for(int j=0;j<len;j+=w*2){
			int g=1;
			rep(i,0,w-1){
				int t=1ll*a[i+j+w]*g%P;
				a[i+j+w]=a[i+j]-t;
				if(a[i+j+w]<0)a[i+j+w]+=P;
				Mod(a[i+j+w]);
				a[i+j]=a[i+j]+t;
				Mod(a[i+j]);
				g=1ll*g*h%P;
			}
		}
	}
	if(Ty==-1){
		reverse(a+1,a+len);
		int inv=Pow(len,P-2);
		rep(i,0,len-1)a[i]=1ll*a[i]*inv%P;
	}
}
char s[M];
int main(){
	//cerr<<(&vio-&let)/1024.0/1024<<endl;
	scanf("%s",s+1);
	int n=strlen(s+1);
	rep(i,1,n)if(s[i]=='B')A[n-i]=1;
	rep(i,1,n)if(s[i]=='A')B[i]=1;
	int len=0,lim=1;
	while(lim<2*n)lim<<=1,len++;
	rep(i,0,lim)rev[i]=(rev[i>>1]>>1)|((i&1)<<(len-1));	
	NTT(A,lim,1),NTT(B,lim,1);
	rep(i,0,lim)A[i]=1ll*A[i]*B[i]%P;
	NTT(A,lim,-1);
	rep(i,1,n-1)printf("%d\n",A[i+n]);
	return 0;
}
