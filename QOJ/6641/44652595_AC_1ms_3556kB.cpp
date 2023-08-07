#include<bits/stdc++.h>
using namespace std;
int main(){
#ifdef memset0
	freopen("K.in","r",stdin);
#endif
	int n,d;
	const int b=128;
	cin>>n>>d;
	vector<vector<int>> a={
		{},
		{1},
		{0,1},
		{1,1},
		{0,0,1},
		{1,0,1},
	};
	vector<int> ans;
	for(auto vec:a){
		int s=0;
		int w=1;
		for(int i=0;i<vec.size();i++){
			if(vec[i]){
				s+=w*d;
			}
			w*=128;
		}
		ans.push_back(s);
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<ans.size();j++){
			cout<<ans[j]<<" \n"[j+1==ans.size()];
		}
	}
}