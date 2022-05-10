#include<string>
#include<vector>
#include<iostream>
using namespace sdt;
int n,t,ans;
string s;
vector<string> a,b;
string getline(){
	std::string res;
	char c;
	while(c=getchar(),c!='\n'){
		if(c=='<'){
			if(res.size())res.pop_back();
		}else{
			res.push_back(c);
		}
	}
	return res;
}
int main(){
	do{
		s=getline();
		a.push_back(s);
	}while(s!="EOF");
	do{
		s=getline();
		b.push_back(s);
	}while(s!="EOF");
	cin>>t;
	a.pop_back(),b.pop_back();
	for(int i=0;i<min(a.size(),b.size());i++){
		for(int j=0;j<min(a[i].size(),b[i].size());j++)
			ans+=a[i][j]==b[i][j];
	}
	cout<<(int)(ans*60/(double)t+0.5)<<endl;
}