#include<string>
#include<vector>
#include<iostream>
int n,t,ans;
std::string s;
std::vector<std::string> a,b;
std::string getline(){
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
	std::cin>>t;
	a.pop_back(),b.pop_back();
	for(int i=0;i<std::min(a.size(),b.size());i++){
		for(int j=0;j<std::min(a[i].size(),b[i].size());j++)
			ans+=a[i][j]==b[i][j];
	}
	std::cout<<(int)(ans*60/(double)t+0.5)<<std::endl;
}