#include<bits/stdc++.h>
#pragma GCC target("avx")
#pragma GCC target("popcnt")
#pragma GCC target("tune=native")
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("inline-functions-called-once")
using namespace std;
using i64=long long;
using u64=unsigned long long;
const int S=1<<15; char ibuf[S],obuf[S],*iS,*iT,*oS=obuf,*oT=oS+S-1;
#define flush() (fwrite(obuf,1,oS-obuf,stdout),oS=obuf,void())
#define getchar() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,S,stdin),(iS==iT?EOF:*iS++)):*iS++)
#define putchar(x) (*oS++=(x),oS==oT?flush():void())
template<class T> inline void write(T x){if(x>9)write(x/10);putchar(x%10+'0');}
const int N=1e6+10,p0=998244353,p1=1000000007,px=131131;
int n,c,top,s[N],la[N],h0[N],h1[N],pw0[N],pw1[N],stk[N];
vector<tuple<int,int,int>> runs;
template<const u64 p> struct ExactDiv{
	u64 t,i;
	inline ExactDiv():t(u64(-1)/p),i(mul_inv(p)){}
	inline bool divide(u64 n){return n*i<=t;}
	inline bool divide(i64 n){return u64(n<0?-n:n)*i<=t;}
	inline u64 mul_inv(u64 n){u64 x=n;for(int i=0;i<5;++i)x*=2-n*x;return x;}
};
ExactDiv<p0>moder0;
ExactDiv<p1>moder1;
template<const int p> constexpr int dec(int a,int b){return (a-=b)<0?a+p:a;}
template<const int p> constexpr int inc(int a,int b){return (a+=b)>=p?a-p:a;} 
template<const int p> void initpow(int *pw){pw[0]=1; for(int i=1;i<=n;i++)pw[i]=(i64)pw[i-1]*px%p;}
template<const int p> void init(int *h){h[0]=0; for(int i=1;i<=n;i++)h[i]=((i64)h[i-1]*px+s[i-1])%p;}
inline bool equal(int i,int j,int m){
	if(!moder0.divide((i64)h0[i]*pw0[m]-h0[i+m]-(i64)h0[j]*pw0[m]+h0[j+m]))return false;
	//if(!moder1.divide((i64)h1[i]*pw1[m]-h1[i+m]-(i64)h1[j]*pw1[m]+h1[j+m]))return false;
	return true;
}
#define search() { \
	if(check(max>>1)){ \
		int l=(max>>1)+1,r=max,mid,res=max>>1; \
		while(l<=r){mid=(l+r)>>1; check(mid)?(res=mid,l=mid+1):(r=mid-1);} \
		callback(res); \
	}else{ \
		for(int k=0;;k++)if(!check(1<<k)){ \
			int res=0; \
			while(~(--k))if(res+=1<<k,!check(res))res-=1<<k; \
			callback(res); \
		} \
	} \
}
inline bool diff(int la,int ra,int lb,int rb){
#define callback(res) return res==max?na<nb:s[la+res]<s[lb+res];
#define check(m) (((m)<=max)&&equal(la,lb,m))
	int na=ra-la+1,nb=rb-lb+1,max=std::min(na,nb); search();
#undef check
#undef callback
}
#define callback(res) return res;
inline int lcs(int i,int j){
#define check(m) ((m)<=max&&equal(i-(m)+1,j-(m)+1,m))
	int max=std::min(i,j)+1; search();
#undef check
}
inline int lcp(int i,int j){
#define check(m) ((m)<=max&&equal(i,j,m))
	int max=n-std::max(i,j); search();
#undef check
}
#undef callback
void lyndon(int *res){
	stk[top=1]=res[n-1]=n-1;
	for(int i=n-2;i>=0;i--){
		stk[++top]=i;
		while(top>1&&diff(i,stk[top],stk[top]+1,stk[top-1]))top--;
		res[i]=stk[top];
	}
}
int main(){
	while(isalpha(c=getchar()))s[n++]=c;
	initpow<p0>(pw0);
	//initpow<p1>(pw1);
	cerr<<clock()/double(CLOCKS_PER_SEC)<<endl;
	for(int _=0;_<2;_++){
		for(int i=0;i<n;i++)s[i]=128-s[i];
		init<p0>(h0);
		//init<p1>(h1);
		lyndon(la);
		cerr<<clock()/double(CLOCKS_PER_SEC)<<endl;
		for(int i=0,j,l,r;i<n;i++){
			j=la[i],l=i-lcs(i-1,j),r=j+lcp(i,j+1);
			if(r-l+1>=(j-i+1<<1))runs.emplace_back(std::make_tuple(j-i+1,l,r+1));
		}
		cerr<<clock()/double(CLOCKS_PER_SEC)<<endl;
	}
	sort(runs.begin(),runs.end());
	int cnt=1;
	for(int i=1;i<runs.size();i++){
		if(get<0>(runs[i])!=get<0>(runs[i-1])||get<1>(runs[i])!=get<1>(runs[i-1]))++cnt;
	}
	cerr<<clock()/double(CLOCKS_PER_SEC)<<endl;
	write(cnt),putchar('\n');
#define output(i) \
	write(get<0>(runs[i])),putchar(' '), \
	write(get<1>(runs[i])),putchar(' '), \
	write(get<2>(runs[i])),putchar('\n');
	output(0);
	for(int i=1;i<runs.size();i++){
		if(get<0>(runs[i])!=get<0>(runs[i-1])||get<1>(runs[i])!=get<1>(runs[i-1]))output(i);
	}
	cerr<<clock()/double(CLOCKS_PER_SEC)<<endl;
	return flush(),0;
}