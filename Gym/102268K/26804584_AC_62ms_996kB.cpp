#include<bits/stdc++.h>
const int mod=998244353;
int n,m;
std::string s;
std::map<std::string,int> id;
std::map<std::string,std::string> dp;
std::string trans(std::string s){
	std::string r;
	for(int i=0;i<s.length();i++){
		r=r+s[i];
		if(dp.find(r)!=dp.end())r=dp[r];
	}
	// std::cerr<<"trans "<<s<<" -> "<<r<<std::endl;
	assert(id.find(r)!=id.end());
	return r;
}
struct mat{
	int x[12][12];
	inline mat(){memset(x,0,576);}
	inline void print(){
		puts("---");
		for(int i=0;i<12;i++)
			for(int j=0;j<12;j++)
				if(x[i][j])printf("%d %d %d\n",i,j,x[i][j]);
	}
}mov,res;
mat operator*(const mat &a,const mat &b){
	mat c;
	for(int i=0;i<12;i++)
		for(int j=0;j<12;j++)
			for(int k=0;k<12;k++)
				c.x[i][j]=(c.x[i][j]+(long long)a.x[i][k]*b.x[k][j])%mod;
	return c;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	std::cin>>n>>s>>m;
	id[""]=0;
	id["a"]=1;
	dp["aa"]="";
	id["ab"]=2;
	id["aba"]=3;
	id["abb"]=4;
	dp["abaa"]="ab";
	dp["abab"]="bba";
	dp["abba"]="bab";
	dp["abbb"]="a";
	id["b"]=5;
	id["ba"]=6;
	dp["baa"]="b";
	id["bab"]=7;
	dp["baba"]="abb";
	id["babb"]=8;
	dp["babba"]="bbab";
	dp["babbb"]="ba";
	id["bb"]=9;
	id["bba"]=10;
	dp["bbaa"]="bb";
	id["bbab"]=11;
	dp["bbaba"]="babb";
	dp["bbabb"]="aba";
	dp["bbb"]="";
	for(auto it=id.begin();it!=id.end();it++){
		mov.x[id[trans(it->first+'a')]][it->second]=1;
		mov.x[id[trans(it->first+'b')]][it->second]=1;
	}
	res.x[0][0]=1;
	for(;m;m>>=1,mov=mov*mov)if(m&1)res=mov*res;
	printf("%d\n",res.x[id[trans(s)]][0]);
	// res.print();
}