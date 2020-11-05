#include<bits/stdc++.h>
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
	std::string s;
	std::vector<z<p0>> h0;
	std::vector<z<p1>> h1;
	void init(const std::string &t){
		s=t; int n=s.length(); h0.resize(n+1),h1.resize(n+1),h0[0]=1,h1[0]=1;
		for(int i=1;i<=n;i++)h0[i]=h0[i-1]*px+s[i-1],h1[i]=h1[i-1]*px+s[i-1];
	}
	inline bool eq(int l0,int r0,int l1,int r1)const{
		if((h0[r0+1]-h0[l0]*w0[r0-l0+1]).x!=(h0[r1+1]-h0[l1]*w0[r1-l1+1]).x)return false;
		if((h1[r0+1]-h1[l0]*w1[r0-l0+1]).x!=(h1[r1+1]-h1[l1]*w1[r1-l1+1]).x)return false;
		return true;
	}
	inline bool diff(int la,int ra,int lb,int rb)const{
		int na=ra-la+1,nb=rb-lb+1,n=std::min(na,nb),l=1,r=n,mid,res=0;
		while(l<=r)mid=(l+r)>>1,(eq(la,la+mid-1,lb,lb+mid-1)?(res=mid,l=mid+1):(r=mid-1));
		return res==n?na<nb:s[la+res]<s[lb+res];
	}
}h;
std::vector<int> lyndon(const std::string &s,const hash &h){
	std::vector<int> f={(int)s.length()-1};
	for(int i=(int)s.length()-2;i>=0;i--){
		f.push_back(i);
		while(f.size()>1&&h.diff(i,f.back(),f.back()+1,f[f.size()-2]))f.pop_back();
	}
	return std::reverse(f.begin(),f.end()),f;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	std::string s;
	std::cin>>s;
	init(s.length()),h.init(s);
	for(int i:lyndon(s,h))printf("%d ",i+1);
}
