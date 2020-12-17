#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10,P0=998244353,P1=1e9+9;
int n,q,top,la[N],stk[N],p0[N],p1[N],h0[N],h1[N];
string s;
struct query{
	int l,r;
}qry[N];
struct run{
	int p,l,r;
	inline bool operator<(const run &rhs)const{
		return l==rhs.l?r<rhs.r:l<rhs.l;
	}
	inline bool operator==(const run &rhs)const{
		return l==rhs.l&&r==rhs.r;
	}
};
vector<run> runs;
template<const unsigned long long p> struct ExactDiv{
	using i64=long long;
	using u64=unsigned long long;
	u64 t,i;
	inline ExactDiv():t(u64(-1)/p),i(mul_inv(p)){}
	inline bool divide(u64 n){return n*i<=t;}
	inline bool divide(i64 n){return u64(n<0?-n:n)*i<=t;}
	inline u64 mul_inv(u64 n){u64 x=n;for(int i=0;i<5;++i)x*=2-n*x;return x;}
};
ExactDiv<P0> M0;
ExactDiv<P1> M1;
inline bool equal(int i,int j,int m){
	if(!M0.divide((long long)h0[i-1]*p0[m]-h0[i+m-1]-(long long)h0[j-1]*p0[m]+h0[j+m-1]))return false;
	if(!M1.divide((long long)h1[i-1]*p1[m]-h1[i+m-1]-(long long)h1[j-1]*p1[m]+h1[j+m-1]))return false;
	return true;
}
inline bool diff(int l0,int r0,int l1,int r1){
	int len=min(r0-l0+1,r1-l1+1),l=1,r=len,mid,res=0;
	while(l<=r){
		mid=(l+r)>>1;
		equal(l0,l1,mid)?(res=mid,l=mid+1):(r=mid-1);
	}
	return res==len?r0-l0+1<r1-l1+1:s[l0+res]<s[l1+res];
}
inline int lcp(int i,int j){
	int l=1,r=min(n-i+1,n-j+1),mid,res=0;
	while(l<=r){
		mid=(l+r)>>1;
		equal(i,j,mid)?(res=mid,l=mid+1):(r=mid-1);
	}
	return res;
}
inline int lcs(int i,int j){
	int l=1,r=min(i,j),mid,res=0;
	while(l<=r){
		mid=(l+r)>>1;
		equal(i-mid+1,j-mid+1,mid)?(res=mid,l=mid+1):(r=mid-1);
	}
	return res;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
//	cin>>n>>q>>s;
//	for(int i=1;i<=q;i++){
//		cin>>qry[i].l>>qry[i].r;
//	}
	cin>>s,n=s.length();
	p0[0]=p1[0]=1;
	for(int i=1;i<N;i++){
		p0[i]=131131ll*p0[i-1]%P0;
		p1[i]=131131ll*p1[i-1]%P1;
	}
	s.insert(s.begin(),' ');
	for(int rev=1;~rev;rev--){
		for(int i=1;i<=n;i++)s[i]=256-s[i];
		for(int i=1;i<=n;i++){
			h0[i]=(131131ll*h0[i-1]+s[i])%P0;
			h1[i]=(131131ll*h1[i-1]+s[i])%P1;
		}
		top=0;
		for(int i=n;i>=1;i--){
			stk[++top]=i;
			while(top>1&&diff(i,stk[top],stk[top]+1,stk[top-1]))top--;
			la[i]=stk[top];
		}
		for(int i=1,j,l,r;i<=n;i++){
			j=la[i],l=i-lcs(i-1,j),r=j+lcp(i,j+1);
			if(r-l+1>=((j-i+1)<<1)){
				runs.push_back({j-i+1,l,r});
			}
		}
	}
	sort(runs.begin(),runs.end());
	runs.erase(unique(runs.begin(),runs.end()),runs.end());
	cout<<runs.size()<<endl;
	for(const auto &r:runs){
		cout<<r.l<<" "<<r.r<<" "<<r.p<<endl;
	}
}