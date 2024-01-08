#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e7+9,mod=104857601;
int n,m,ans,fac[N],ifac[N];
inline int norm(int x){return x<(mod>>1)?x:x-mod;}
inline int sub(int a,int b){return a-=b,a<0?a+mod:a;}
inline int add(int a,int b){return a+=b,a>=mod?a-mod:a;}
inline int power(int a,int b){
  int s=1;
  for(;b;b>>=1,a=(ll)a*a%mod)
    if(b&1) s=(ll)s*a%mod;
  return s;
}
inline int C(int n,int m){
	if(n<m)return 0;
	return (ll)fac[n]*ifac[n-m]%mod*ifac[m]%mod;
}
vector<int> rev,rt;
void getRevRoot(int n){
  int m=__lg(n); // log(n)/log(2)+1e-8;
  rev.resize(n);
  for(int i=1;i<n;i++){
    rev[i]=rev[i>>1]>>1|(i&1)<<(m-1);
  }
  static int len=1;
  if(len<n){
    rt.resize(n);
    for(;len<n;len<<=1){
      int uni=power(3,(mod-1)/(len<<1));
      rt[len]=1;
      for(int i=1;i<len;i++){
        rt[i+len]=(ll)rt[i+len-1]*uni%mod;
      }
    }
  }
}
void ntt(vector<int> &f,int n){
  f.resize(n);
  for(int i=0;i<n;i++){
    if(i<rev[i]) swap(f[i],f[rev[i]]);
  }
  for(int len=1;len<n;len*=2){
    for(int i=0;i<n;i+=len*2){
      for(int j=0;j<len;j++){
        int x=f[i+j];
        int y=(ll)f[i+j+len]*rt[j+len]%mod;
        f[i+j]=add(x,y);
        f[i+j+len]=sub(x,y);
      }
    }
  }
}
vector<int> operator*(vector<int> f,vector<int> g){
  int n=1,m=(int)(f.size()+g.size())-1;
  while(n<m) n<<=1;
  int invn=power(n,mod-2);
  getRevRoot(n),ntt(f,n),ntt(g,n);
  for(int i=0;i<n;i++)f[i]=(ll)f[i]*g[i]%mod;
  reverse(f.begin()+1,f.end()),ntt(f,n);
  f.resize(m);
  for(int i=0;i<m;i++)f[i]=(ll)f[i]*invn%mod;
  return f;
}
vector<int> polyInv(vector<int> f,int n){
  if(n==1) return {power(f[0],mod-2)};
  f.resize(n);
  vector<int> g=polyInv(f,n/2),h(n);
  g.resize(n);
  for(int i=0;i<n/2;i++) h[i]=g[i];
  int invn=power(n,mod-2);
  getRevRoot(n),ntt(f,n),ntt(g,n);
  for(int i=0;i<n;i++) f[i]=(ll)f[i]*g[i]%mod;
  reverse(f.begin()+1,f.end()),ntt(f,n);
  for(int i=1;i<n/2;i++)f[i]=0;
  for(int i=n/2;i<n;i++)f[i]=(ll)f[i]*invn%mod;
  f[0]=1,ntt(f,n);
  for(int i=0;i<n;i++)f[i]=(ll)f[i]*g[i]%mod;
  reverse(f.begin()+1,f.end()),ntt(f,n);
  for(int i=n/2;i<n;i++)h[i]=sub(0,(ll)f[i]*invn%mod);
  return h;
}
vector<int> operator~(vector<int> f){
  if(f.empty())return f;
  int n=1,m=f.size();
  while(n<m) n<<=1;
  f=polyInv(f,n);
  f.resize(m);
  return f;
}
int main(){
#ifdef memset0
	freopen("H.in","r",stdin);
#endif
	// for(int g=2;;g++){
	// 	// set<int> st;
	// 	cerr<<"! "<<g<<endl;
	// 	int x=g;
	// 	bool fl=true;
	// 	for(int i=2;i<mod;i++){
	// 		x=(ll)x*g%mod;
	// 		if(x==1){
	// 			cerr<<"! "<<i<<endl;
	// 			fl=false;
	// 			break;
	// 		}
	// 		// st.insert(x);
	// 	}
	// 	if(fl){
	// 		cerr<<"! "<<g<<endl;
	// 	}
	// }
	fac[0]=ifac[0]=ifac[1]=1;
	for(int i=2;i<N;i++){
		ifac[i]=(ll)(mod-mod/i)*ifac[mod%i]%mod;
	}
	for(int i=1;i<N;i++){
		fac[i]=(ll)fac[i-1]*i%mod;
		ifac[i]=(ll)ifac[i-1]*ifac[i]%mod;
	}
	vector<int> f,g,h;
	cin>>n>>m;
	if(m==1||m==n-1){
		cout<<1<<endl;
		return 0;
	}
	f.resize(m);
	for(int i=1;i<m;i++){
		f[i]=mod-C(i*2-1,i-1);
	}
	// for(int i=0;i<m;i++)cerr<<f[i]<<" \n"[i+1==m];
	g.resize(m);
	for(int i=0;i<m;i++){
		g[i]=C(i<<1,i);
	}
	// for(int i=0;i<m;i++)cerr<<norm(g[i])<<" \n"[i+1==m];
	g=~g;
	// for(int i=0;i<m;i++)cerr<<norm(g[i])<<" \n"[i+1==m];
	long long ans=C(n+m-2,m-1);
	// cerr<<"! "<<ans<<endl;
	h=f*g,h.resize(m);
	for(int i=1;i<m;i++){
		ans+=2ll*C(n+m-1-i*2,m-i-1)*h[i]%mod;
		// cerr<<"! "<<C(n+m-1-i*2,m-i-1)<<" "<<norm(h[i])<<endl;
	}
	ans%=mod;
	h=h*h;
	h.resize(m);
	for(int k=1;k<m;k++){
		ans+=1ll*C(n+m-k*2,m-k-1)*h[k]%mod;
	}
	ans%=mod;
	// cout<<(ans%mod+mod)%mod<<endl;
	f.clear(),f.resize(m);
	for(int i=0;i<m;i++){
		f[i]=mod-C(n-m+i+1,i);
	}
	h=f*g,h.resize(m);
	h=h*h,h.resize(m);
	for(int i=0;i<m;i++){
		ans+=1ll*C(m*3-n-4-i*2,m-1-i)*h[i]%mod;
		// cerr<<"! "<<C(m*3-n-4-i*2,m-1-i)<<" "<<norm(h[i])<<endl;
	}
	cout<<(ans%mod+mod)%mod<<endl;
}
/*
...#####
#...####
##...###
###...##
####...#
#####...
*/