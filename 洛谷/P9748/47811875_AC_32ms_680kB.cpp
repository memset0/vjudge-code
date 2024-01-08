#include<bits/stdc++.h>
using namespace std;
pair<int,int> bruteforce(int n){
	vector<int> a(n);
	for(int i=0;i<n;i++)a[i]=i+1;
	int ans1=0,ans2=-1;
	while(a.size()){
		++ans1;
		vector<int> b;
		for(int i=0;i<a.size();i++)
			if(i%3){
				b.push_back(a[i]);
			}else if(a[i]==n){
				ans2=ans1;
			}
		a.swap(b);
	}
	return {ans1,ans2};
}
pair<int,int> solve(int n){
	int ans1=0,ans2=-1;
	while(n){
		++ans1;
		if(ans2==-1&&n%3==1){
			ans2=ans1;
		}
		n=n-(n+2)/3;
	}
	return {ans1,ans2};
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin>>n;
	auto ans=solve(n);
	cout<<ans.first<<" "<<ans.second<<endl;
//	for(int n=1;n<=10000;n++){
//		auto bf=bruteforce(n);
//		auto ans=solve(n);
//		assert(bf.first==ans.first);
//		assert(bf.second==ans.second);
//	}
}