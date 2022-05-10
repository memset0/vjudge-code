#include<bits/stdc++.h>
const int S=1<<21; char ibuf[S],*iS,*iT,obuf[S],*oS=obuf,*oT=oS+S-1;
#define flush() (fwrite(obuf,1,oS-obuf,stdout),oS=obuf,void())
#define getchar() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,S,stdin),(iS==iT?EOF:*iS++)):*iS++)
#define putchar(x) (*oS++=(x),oS==oT?flush():void())
struct Flusher_{~Flusher_(){flush();}}flusher_;
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
template<int mod> struct z{
	int x;
	inline z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
};
const int p0=998244353,p1=1e9+7,px=131131;
std::vector<z<p0>> w0;
std::vector<z<p1>> w1;
void init(int n){
	w0.resize(n+1),w1.resize(n+1),w0[0]=1,w1[0]=1;
	for(int i=1;i<=n;i++)w0[i]=w0[i-1]*px,w1[i]=w1[i-1]*px;
}
struct hash{
	int len;
	std::string s;
	std::vector<z<p0>> h0;
	std::vector<z<p1>> h1;
	void init(const std::string &t){
		s=t,len=s.length(),h0.resize(len+1),h1.resize(len+1),h0[0]=1,h1[0]=1;
		for(int i=1;i<=len;i++)h0[i]=h0[i-1]*px+s[i-1],h1[i]=h1[i-1]*px+s[i-1];
	}
	inline bool eq(int l0,int r0,int l1,int r1)const{
		if((h0[r0+1]-h0[l0]*w0[r0-l0+1]).x!=(h0[r1+1]-h0[l1]*w0[r1-l1+1]).x)return false;
		if((h1[r0+1]-h1[l0]*w1[r0-l0+1]).x!=(h1[r1+1]-h1[l1]*w1[r1-l1+1]).x)return false;
		return true;
	}
	inline bool diff(int la,int ra,int lb,int rb)const{
		int na=ra-la+1,nb=rb-lb+1,n=std::min(na,nb),l=1,r=n,mid,runs=0;
		while(l<=r)mid=(l+r)>>1,(eq(la,la+mid-1,lb,lb+mid-1)?(runs=mid,l=mid+1):(r=mid-1));
		return runs==n?na<nb:s[la+runs]<s[lb+runs];
	}
	inline int lcp(int i,int j){
		int l=1,r=std::min(len-i,len-j),mid,runs=0;
		while(l<=r)mid=(l+r)>>1,(eq(i,i+mid-1,j,j+mid-1)?(runs=mid,l=mid+1):(r=mid-1));
		return runs;
	}
	inline int lcs(int i,int j){
		int l=1,r=std::min(i+1,j+1),mid,runs=0;
		while(l<=r)mid=(l+r)>>1,(eq(i-mid+1,i,j-mid+1,j)?(runs=mid,l=mid+1):(r=mid-1));
		return runs;
	}
}h;
std::vector<int> lyndon(const std::string &s,const hash &h){
	int len=s.length();
	std::vector<int> f={len-1},g={len-1};
	for(int i=(int)len-2;i>=0;i--){
		f.push_back(i);
		while(f.size()>1&&h.diff(i,f.back(),f.back()+1,f[f.size()-2]))f.pop_back();
		g.push_back(f.back());
	}
	return std::reverse(g.begin(),g.end()),g;
}
void runs(std::string s){
	std::vector<std::tuple<int,int,int>> runs;
	int len=s.length();
	for(int fl=1;~fl;fl--){
		for(int i=0;i<len;i++)s[i]=256-s[i]; h.init(s);
		auto la=lyndon(s,h);
		for(int i=0,j,l,r;i<la.size();i++){
			j=la[i],l=i-h.lcs(i-1,j),r=j+h.lcp(i,j+1);
			if(r-l+1>=((j-i+1)<<1))runs.push_back(std::make_tuple(l+1,r+1,j-i+1));
		}
	}
	std::sort(runs.begin(),runs.end());
	runs.erase(std::unique(runs.begin(),runs.end()),runs.end());
	print(runs.size(),'\n');
	for(int i=0;i<runs.size();i++){
		print(std::get<0>(runs[i]),' ');
		print(std::get<1>(runs[i]),' ');
		print(std::get<2>(runs[i]),'\n');
	}
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	std::string s;
	std::cin>>s;
	init(s.length());
	runs(s);
}