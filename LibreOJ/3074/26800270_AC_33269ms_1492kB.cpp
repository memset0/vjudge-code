#include<bits/stdc++.h>
namespace BigInt{
	const int bit=9,mod=1e9;
	struct bigint:std::vector<int>{
		inline bigint(){}
		inline bigint(int siz){resize(siz);}
		inline void pop_zero(){while(size()&&!back())pop_back();}
		inline std::string to_string()const{
			if(!size())return "0";
			std::string s;
			for(int i=0;i<size();i++){
				int t=this->operator[](i);
				for(int j=0;j<bit;j++)s.push_back('0'+t%10),t/=10;
			}
			while(s.back()=='0')s.pop_back();
			std::reverse(s.begin(),s.end());
			return s;
		}
		inline void from_number(long long x){clear(); while(x)push_back(x%mod),x/=mod;}
		inline void from_string(std::string s){
			long long t=0,m=1;
			clear(),std::reverse(s.begin(),s.end());
			while(s.length()%bit)s.push_back('0');
			resize(s.length()/bit);
			for(int i=0;i<s.length();i+=bit){
				for(int j=0,t=1;j<bit;j++,t*=10)this->operator[](i/bit)+=(s[i+j]-'0')*t;
			}
		}
	};
	inline bigint operator+(bigint a,const bigint &b){
		a.resize(std::max(a.size(),b.size()));
		for(int i=0;i<b.size();i++)a[i]+=b[i];
		for(int i=0;i+1<a.size();i++)if(a[i]>=mod)a[i]-=mod,a[i+1]++;
		if(a.size()&&a.back()>=mod)a.back()-=mod,a.push_back(1);
		return a;
	}
	inline void operator+=(bigint &a,const bigint &b){a=a+b;}
	inline bigint operator-(bigint a,const bigint &b){ //assert(a>b);
		for(int i=0;i<b.size();i++)a[i]-=b[i];
		for(int i=0;i+1<a.size();i++)if(a[i]<0)a[i]+=mod,a[i+1]--;
		return a.pop_zero(),a;
	}
	inline void operator-=(bigint &a,const bigint &b){a=a-b;}
	inline bigint operator*(const bigint &a,const bigint &b){
		bigint c(a.size()+b.size()+1);
		std::vector<long long> t(c.size());
		for(int i=0;i<a.size();i++)
			for(int j=0;j<b.size();j++){
				long long p=t[i+j]+(long long)a[i]*b[j];
				t[i+j]=p%mod;
				t[i+j+1]+=p/mod;
			}
		for(int i=0;i<t.size();i++)t[i+1]+=t[i]/mod,c[i]=t[i]%mod;
		return c.pop_zero(),c;
	}
	inline std::pair<bigint,int> div(const bigint &a,int b){
		bigint c(a.size()); long long d=0;
		for(int i=(int)a.size()-1;i>=0;i--)d=d*mod+a[i],c[i]=d/b,d%=b;
		return c.pop_zero(),std::make_pair(c,(int)d);
	}
	inline bigint operator/(const bigint &a,int b){return div(a,b).first;}
	inline bigint operator%(const bigint &a,int b){return div(a,b).second;}
}
using namespace BigInt;
const int N=55;
int m,n,a[N];
bigint t,f[N][N*10],g[N][N];
std::string str;
void DP(){
	f[0][0].from_number(1);
	for(int i=1;i<=n+2;i++)
		for(int j=0;j<=i*m;j++)
			for(int k=0;k<=j&&k<m;k++)
				f[i][j]+=f[i-1][j-k];
}
bigint ANS(int lim){
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			g[i][j].clear();
	g[0][0].from_number(1);
	for(int i=1;i<=n;i++){
		int l=std::min(lim,i-1)+2;
		for(int j=0;j<=l*m;j++)
			for(int k=0;k<=l+1;k++)
				if(!g[i-1][k].empty()&&(j+k)%m==a[i])
					g[i][(j+k)/m]+=g[i-1][k]*f[l][j];
	}
	return g[n][0];
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	std::cin>>m>>str;
	t.from_string(str);
	while(!t.empty()){
		auto it=div(t,m);
		// std::cerr<<t.to_string()<<" "<<it.first.to_string()<<" "<<it.second<<std::endl;
		a[++n]=it.second;
		t=it.first;
	}
	// for(int i=1;i<=n;i++)printf("%d%c",a[i]," \n"[i==n]);
	DP();
	bigint last;
	last.from_number(1);
	for(int i=0;i<n;i++){
		bigint cur=ANS(i);
		std::cout<<(cur-last).to_string()<<std::endl;
		last=cur;
	}
}