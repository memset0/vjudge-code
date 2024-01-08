#include<bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
map<char,string> mp={
	{'Y',"QQQ"},
	{'V',"QQW"},
	{'G',"QQE"},
	{'C',"WWW"},
	{'X',"QWW"},
	{'Z',"WWE"},
	{'T',"EEE"},
	{'F',"QEE"},
	{'D',"WEE"},
	{'B',"QWE"},
};
int calc(string a,string b){
	if(a==b)return 3;
	if(a[1]==b[0]&&a[2]==b[1])return 2;
	if(a[2]==b[0])return 1;
	return 0;
}
bool check(string a,string b){
	vector<int> p={0,1,2};
	do{
		bool fl=true;
		for(int i=0;i<3;i++)
			if(a[i]!=b[p[i]]){
				fl=false;
			}
		if(fl)return true;
	}while(next_permutation(all(p)));
	return false;
}
int main(){
#ifdef memset0
	freopen("I.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	string str;
	cin>>str;
	map<string,int> id;
	int tot=0;
	vector<string> pat;
	for(char x:{'Q','W','E'})
		for(char y:{'Q','W','E'})
			for(char z:{'Q','W','E'}){
				string a="   ";
				a[0]=x,a[1]=y,a[2]=z;
				id[a]=tot++;
				pat.push_back(a);
			}
	// for(auto [x,y]:id)cerr<<"! "<<x<<" "<<y<<endl;
	array<vector<int>,27> G;
	for(char x:{'Q','W','E'})
		for(char y:{'Q','W','E'})
			for(char z:{'Q','W','E'})
				for(char w:{'Q','W','E'}){
					string a="   ";
					string b="   ";
					a[0]=x,a[1]=y,a[2]=z;
					b[0]=y,b[1]=z,b[2]=w;
					G[id[a]].push_back(id[b]);
				}
	array<int,27> dp[2];
	fill(dp[0].begin(),dp[0].end(),0);
	vector<int> a(str.length());
	for(int i=0;i<a.size();i++){
		// cerr<<str[i]<<">>"<<mp[str[i]]<<">>"<<id[mp[str[i]]]<<endl;
		a[i]=id[mp[str[i]]];
	}
	array<array<bool,27>,27> ok;
	for(int i=0;i<27;i++){
		for(int j=0;j<27;j++){
			ok[i][j]=check(pat[i],pat[j]);
		}
	}
	for(int i=4;i<=(str.length()*4+3);i++){
		fill(dp[1].begin(),dp[1].end(),0);
		for(int x=0;x<27;x++){
			if(ok[a[dp[0][x]]][x]){
				dp[1][x]=max(dp[1][x],dp[0][x]+1);
			}
			for(int y:G[x]){
				dp[1][y]=max(dp[1][y],dp[0][x]);
			}
		}
		// cerr<<"i="<<i<<endl;
		for(int x=0;x<27;x++){
			// cerr<<x<<" "<<pat[x]<<" "<<dp[1][x]<<endl;
			if(dp[1][x]==a.size()){
				cout<<i<<endl;
				return 0;
			}
			dp[0][x]=dp[1][x];
		}
	}
	cout<<-1<<endl;
}