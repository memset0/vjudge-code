#include<bits/stdc++.h>
#pragma GCC target("avx")
// #pragma GCC target("popcnt")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("no-stack-protector")
const int S=1<<21; char ibuf[S],*iS,*iT,obuf[S],*oS=obuf,*oT=oS+S-1;
#define flush() (fwrite(obuf,1,oS-obuf,stdout),oS=obuf,void())
#define getchar() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,S,stdin),(iS==iT?EOF:*iS++)):*iS++)
#define putchar(x) (*oS++=(x),oS==oT?flush():void())
struct Flusher_{~Flusher_(){flush();}}flusher_;
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=8,V=65010,M=10010,mod=998244353;
int n,m,q,lim;
namespace Task1{
	const int V=210;
	int F[2][N][V],S[N][V],ans[M];
	std::vector<int> G[N][N];
	std::vector<std::pair<int,int>> Q[N][N];
	inline void inc(int &a,int b){a+=b; if(a>=mod)a-=mod;}
	void solve(){
		for(int u,v,w,i=0;i<m;i++){
			read(u),read(v),read(w),--u,--v;
			G[u][v].push_back(w);
		}
		for(int u,v,w,i=0;i<q;i++){
			read(u),read(v),read(w),--u,--v;
			Q[u][v].push_back({i,w});
		}
		for(int s=0;s<n;s++){
			for(int i=0;i<n;i++){
				memset(S[i],0,(lim+1)<<2);
				memset(F[0][i],0,(lim+1)<<2);
			}
			F[0][s][0]=1;
			for(int _=1,fl=1;_<=lim;_++,fl^=1){
				for(int i=0;i<n;i++)memset(F[fl][i],0,(lim+1)<<2);
				for(int u=0;u<n;u++)
					for(int v=0;v<n;v++)
						for(int w:G[u][v])
							for(int i=0;i<=lim-w;i++){
								inc(F[fl][v][i+w],F[fl^1][u][i]);
							}
				for(int i=0;i<n;i++)
					for(int j=0;j<=lim;j++){
						inc(S[i][j],F[fl][i][j]);
					}
			}
			for(int t=0;t<n;t++)
				for(auto it:Q[s][t]){
					inc(ans[it.first],S[t][it.second]);
				}
		}
		for(int i=0;i<q;i++)print(ans[i],'\n');
	}
}
namespace Task2{
	const int V=65536<<1;
	int I[V],w[V],rev[V],F[N][N+1][V],T[N][V],TA[V],TB[V],TC[V],TS[V],TT[V],ans[N][N][V],tow[N][N][V],tmp[N][N][V];
	std::vector<std::tuple<int,int,int>> E;
	inline int nord(int a){return a+=a>>31&mod;}
	inline int sub(int a,int b){return (a-=b)<0?a+mod:a;}
	inline int add(int a,int b){return (a+=b)>=mod?a-mod:a;}
	inline int fpow(int a,int b){int s=1;for(;b;b>>=1,a=(long long)a*a%mod)if(b&1)s=(long long)s*a%mod;return s;}
	inline void fill(int *a,int x,int l=lim){std::fill(a,a+l,x);}
	inline void copy(int *a,int *b,int l=lim){std::copy(a,a+l,b);}
	int getlimit(int len){
		int lim=1;
		while(lim<=len)lim<<=1;
		for(int wn,len=1;len<=lim;len<<=1){
			wn=fpow(3,(mod-1)/(len<<1)),w[len]=1;
			for(int i=1;i<len;i++)w[i+len]=(long long)w[i+len-1]*wn%mod;
		}
		return lim;
	}
	void polyinit(int len){
		static int last=-1;
		if(len==last)return;
		int lim=1,k=0; last=len;
		while(lim<len)lim<<=1,++k;
		for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
	}
	void dft(int *a,int lim){
		polyinit(lim);
		for(int i=0;i<lim;i++)if(i<rev[i])std::swap(a[i],a[rev[i]]);
		for(int len=1;len<lim;len<<=1)
			for(int i=0;i<lim;i+=(len<<1))
				for(int j=0;j<len;j++){
					int x=a[i+j],y=(long long)a[i+j+len]*w[j+len]%mod;
					a[i+j]=add(x,y),a[i+j+len]=sub(x,y);
				}
	}
	void idft(int *a,int lim){
		std::reverse(a+1,a+lim),dft(a,lim);
		for(int i=0,inv=fpow(lim,mod-2);i<lim;i++)a[i]=(long long)a[i]*inv%mod;
	}
	void polysub(int *a,int *b,int *c,int l=lim){
		for(int i=0;i<l;i++)c[i]=sub(a[i],b[i]);
	}
	void polymul(int *a,int *b,int *c,int fa=0,int fb=0,int fc=0){
		fa?copy(a,TS,lim<<1):(copy(a,TS),fill(TS+lim,0),dft(TS,lim<<1));
		fb?copy(b,TT,lim<<1):(copy(b,TT),fill(TT+lim,0),dft(TT,lim<<1));
		for(int i=0;i<(lim<<1);i++)TS[i]=(long long)TS[i]*TT[i]%mod;
		fc?copy(TS,c,lim<<1):(idft(TS,lim<<1),copy(TS,c));
	}
	void polyinv(int *a,int *b){
		b[0]=fpow(a[0],mod-2);
		for(int len=2;len<=lim;len<<=1){
			copy(a,TS,len),fill(TS+len,0,len);
			copy(b,TT,len>>1),fill(TT+(len>>1),0,len|(len>>1));
			dft(TS,len<<1),dft(TT,len<<1);
			for(int i=0;i<(len<<1);i++)TS[i]=(long long)TT[i]*sub(2,(long long)TS[i]*TT[i]%mod)%mod;
			idft(TS,len<<1),copy(TS,b,len);
		}
	}
	inline void clear(int *a){
		idft(a,lim<<1),fill(a+lim,0),dft(a,lim<<1);
	}
	inline void rapid(int *a,int *b,int *c,int l=(lim<<1)){
		for(int i=0;i<l;i+=8){
			a[i]=nord((a[i]-(long long)b[i]*c[i])%mod);
			a[i+1]=nord((a[i+1]-(long long)b[i+1]*c[i+1])%mod);
			a[i+2]=nord((a[i+2]-(long long)b[i+2]*c[i+2])%mod);
			a[i+3]=nord((a[i+3]-(long long)b[i+3]*c[i+3])%mod);
			a[i+4]=nord((a[i+4]-(long long)b[i+4]*c[i+4])%mod);
			a[i+5]=nord((a[i+5]-(long long)b[i+5]*c[i+5])%mod);
			a[i+6]=nord((a[i+6]-(long long)b[i+6]*c[i+6])%mod);
			a[i+7]=nord((a[i+7]-(long long)b[i+7]*c[i+7])%mod);
		}
	}
	void solve(){
		lim=getlimit(std::max(15,lim));
		for(int u,v,w,i=0;i<m;i++){
			read(u),read(v),read(w),--u,--v;
			E.push_back(std::make_tuple(u,v,w));
		}
		for(int i=0;i<n;i++)for(int j=0;j<=n;j++)fill(F[i][j],0,lim<<1);
		for(const auto &it:E)F[std::get<1>(it)][std::get<0>(it)][std::get<2>(it)]++;
		for(int i=0;i<n;i++)F[i][i][0]=mod-1,tow[i][i][0]=mod-1;
		for(int i=0;i<n;i++)dft(tow[i][i],lim<<1);
		for(int i=0;i<n;i++)for(int j=0;j<n;j++)dft(F[i][j],lim<<1);
		for(int i=0;i<n;i++){
			idft(F[i][i],lim<<1),fill(F[i][i]+lim,0);
			polyinv(F[i][i],T[i]);
			fill(T[i]+lim,0),dft(T[i],lim<<1);
			for(int s=0;s<n;s++)clear(tow[s][i]);
			for(int j=i+1;j<n;j++)clear(F[i][j]);
			for(int j=i+1;j<n;j++){
				idft(F[j][i],lim<<1),fill(F[j][i]+lim,0);
				polymul(T[i],F[j][i],TA,1,0,0);
				fill(TA+lim,0),dft(TA,lim<<1);
				for(int k=i+1;k<n;k++)rapid(F[j][k],TA,F[i][k]);
				for(int s=0;s<n;s++)rapid(tow[s][j],TA,tow[s][i]);
			}
		}
		for(int s=n-1;s>=0;s--){
			for(int i=n-1;i>=0;i--){
				clear(tow[s][i]);
				polymul(tow[s][i],T[i],ans[s][i],1,1,0);
				fill(ans[s][i]+lim,0),dft(ans[s][i],lim<<1);
				for(int j=i-1;j>=0;j--)rapid(tow[s][j],ans[s][i],F[j][i]);
				idft(ans[s][i],lim<<1);
			}
		}
		for(int u,v,w,i=0;i<q;i++){
			read(u),read(v),read(w),--u,--v;
			print(ans[u][v][w],'\n');
		}
	}
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
	// freopen("ex_wander2.out","w",stdout);
#endif
	read(n),read(m),read(q),read(lim);
	Task2::solve();
	fprintf(stderr,"clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
}