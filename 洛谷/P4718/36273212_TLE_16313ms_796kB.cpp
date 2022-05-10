// test


#include<bits/stdc++.h>
#define int long long
using namespace std;
long long ans;
unsigned long long f,g;
inline long long read(){
	long long num=0; char g=getchar(); while(g<48||57<g) g=getchar();
	while(47<g&&g<58) num=(num<<1)+(num<<3)+g-48,g=getchar(); return num;
}
inline long long gcd(long long a,long long b){
	if(!b) return a; return gcd(b,a%b);
}
inline long long mul(long long a,long long b,long long p){
	long long ans=0;
	while(b>0) {if(b&1) {ans=ans+a; if(ans>=p) ans-=p;} b=b>>1,a=a+a; if(a>=p) a-=p;}
	return ans;
}
inline long long pows(long long u,long long c,long long p){
	long long ans=1;
	while(c>0){
		if(c&1) ans=mul(ans,u,p); c=c>>1,u=mul(u,u,p);
	}
	return ans;
}
inline bool check(long long u,long long k){
	long long c=k-1,x=pows(u,c,k); if(x!=1) return false;
	while(!(c&1)){
		c=c>>1; long long x=pows(u,c,k); if(x!=1&&x!=k-1) return false; if(x==k-1) return true;
	}
	return true;
}
inline unsigned long long getrand(){
	f=((f<<5)^(g>>3)+233333)*19260817,g=(((f<<3)*23333)^((g>>4)*666666))+8888888; return f+g;
}
inline bool millar_rabin(long long u){
	if(u==2||u==3||u==5||u==7||u==11||u==13) return true;
	if((!(u%2))||(!(u%3))||(!(u%5))||(!(u%7))||(!(u%11))||(!(u%13))) return false;
	if(!check(2,u)) return false; if(!check(3,u)) return false;
	if(!check(5,u)) return false; if(!check(7,u)) return false;
	if(!check(11,u)) return false; if(!check(13,u)) return false; return true;
}
inline long long spilt(long long u){
	long long c=getrand()%(u-1)+1,t=getrand()%u,vt=(mul(t,t,u)+c)%u,vq=(mul(vt,vt,u)+c)%u;
//	cout<<c<<"ssss"<<' '<<vt<<' '<<vq<<endl;
	while(vt!=vq){
		long long f=gcd(abs(vt-vq),u);
//		if(c==2) puts("xx");
//		cout<<abs(vt-vq)<<"ssss"<<endl;
		if(f!=1){
//			cout<<f<<"ssss"<<endl;
			return f;
		}
//		cout<<vt<<' '<<vq<<' '<<c<<' '<<u<<' '<<mul(vt,vt,u)+c<<endl;
		vt=mul(vt,vt,u)+c; if(vt>=u) vt-=u;
		vq=mul(vq,vq,u)+c; if(vq>=u) vq-=u;
		vq=mul(vq,vq,u)+c; if(vq>=u) vq-=u;
	}
	return 1;
}
inline void rho(long long u){
	if(u==1) return;
	if(millar_rabin(u)) {ans=max(ans,u); return;}
	long long x=1; while(x==1) x=spilt(u); rho(u/x),rho(x);
}
signed main(){
	int t=read();
	while(t--){
		long long x=read(); ans=0;
		if(millar_rabin(x)) puts("Prime");
		else rho(x),cout<<ans<<endl;
	}
	return 0;
}