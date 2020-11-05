#include<bits/stdc++.h>
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
const int N=5e3+10,L=28,M=(1<<L),mod=998244353;
int T,n;
std::vector<int> G[N];
inline int fpow(int a,int b){
	int s=1;
	for(;b;b>>=1,a=(long long)a*a%mod)
		if(b&1)s=(long long)s*a%mod;
	return s;
}
struct bignum:std::vector<int>{
	using std::vector<int>::vector;
	inline void clear(){while(size()&&!back())pop_back();}
	inline int trans(){
		int w=1,res=0;
		for(int i=0;i<size();i++){
			res=(res+(long long)(this->operator[](i))*w)%mod;
			w=(long long)w*M%mod;
		}
		return res;
	}
	inline std::string str(){
		if(!size())return "empty";
		std::string t="";
		for(int i=0;i<size();i++){
			for(int j=0;j<L;j++)t+='0'+((this->operator[](i)>>j)&1);
		}
		return t;
	}
	inline void operator<<=(int k){
		int s=k/L,t=k%L;
		// printf("%d %d\n",s,t);
		bignum b(s);
		long long r=0;
		for(int i=0;i<size();i++){
			r+=(long long)(this->operator[](i))<<t;
			b.push_back(r%M),r/=M;
		}
		if(r)b.push_back(r);
		*this=b;
	}
};
inline bignum operator+(bignum a,bignum b){
	a.resize(std::max(a.size(),b.size())+1);
	for(int i=0;i<b.size();i++){
		a[i]+=b[i];
		if(a[i]>=M)a[i]-=M,a[i+1]++;
	}
	a.clear();
	return a;
}
inline bool operator>(bignum a,bignum b){
	if(a.size()!=b.size())return a.size()>b.size();
	for(int i=(int)a.size()-1;i>=0;i--){
		if(a[i]!=b[i])return a[i]>b[i];
	}
	return false;
}
inline bignum bit(int k){
	bignum res={1};
	res<<=k;
	return res;
}
struct atom{
	bignum x;
	int k;
	inline void inc(){
		x=x+bit(k);
	}
	inline std::string str(){
		return "{" + x.str() + "," + std::to_string(k) + "}";
	}
}O,I,dp[N];
inline void fit(atom &a,atom &b){
	if(a.k>b.k){
		b.x<<=a.k-b.k;
		b.k=a.k;
	}
	if(b.k>a.k){
		a.x<<=b.k-a.k;
		a.k=b.k;
	}
}
inline atom operator+(atom a,atom b){
	fit(a,b);
	a.x=a.x+b.x;
	return a;
}
inline bool operator>(atom a,atom b){
	fit(a,b);
	return a.x>b.x;
}
void dfs(int u){
	for(int v:G[u])dfs(v);
	if(G[u].size()==0){
		dp[u]=O;
	}else if(G[u].size()==1){
		dp[u]=dp[G[u][0]];
	}else{
		int f=0,g=1;
		for(int i=2;i<G[u].size();i++)
			if(dp[G[u][i]]>dp[G[u][f]]){
				g=f,f=i;
			}else if(dp[G[u][i]]>dp[G[u][g]]){
				g=i;
			}
		atom x=dp[G[u][f]];
		atom y=dp[G[u][f]]+dp[G[u][g]];
		y.k++,y.inc();
		dp[u]=x>y?x:y;
		// printf("! %s\n! %s\n",x.str().c_str(),y.str().c_str());
	}
	// printf("dp[%d] = %s\n",u,dp[u].str().c_str());
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	I.inc();
	// for(int i=1;i<10;i++)std::cout<<bit(i).str()<<std::endl;
	for(read(T);T--;){
		read(n);
		for(int i=1;i<=n;i++)G[i].clear();
		for(int fa,i=2;i<=n;i++){
			read(fa);
			G[fa].push_back(i);
		}
		dfs(1);
		int f=dp[1].x.trans(),g=fpow(2,dp[1].k);
		// printf(">> %d %d\n",f,g);
		int ans=(long long)f*fpow(g,mod-2)%mod;
		print(ans,'\n');
	}
}