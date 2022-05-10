#include<bits/stdc++.h>
int main(){
#ifdef memset0
	freopen("A.in","r",stdin);
#else
// 	freopen("save.in","r",stdin),freopen("save.out","w",stdout);
#endif
	int n,max=0;
	std::string name,str;
	std::vector<std::pair<std::string,int>> a;
	std::cin>>n;
	for(int i=0;i<n;i++){
		int cnt=0;
		std::cin>>name>>str;
		for(int i=0;i+2<str.size();i++){
			cnt+=str[i]=='s'&&str[i+1]=='o'&&str[i+2]=='s';
		}
		a.push_back(std::make_pair(name,cnt));
		max=std::max(max,cnt);
	}
	for(int i=0;i<a.size();i++)if(a[i].second==max){
		std::cout<<a[i].first<<" ";
	}
	std::cout<<std::endl<<max<<std::endl;
}