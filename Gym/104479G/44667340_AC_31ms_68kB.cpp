#include<bits/stdc++.h>
using namespace std;
const int N=1e4+1;
int ans=1,vis[N];
vector<int> pri;
bool ask(int x){
	if(x>1e4)return false;
	static string s;
	cout<<"? "<<x<<endl;
	cin>>s;
	return s[0]=='Y';
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	for(int i=2;i<N;i++){
		if(!vis[i]){
			pri.push_back(i);
		}
		for(int j=i*2;j<N;j+=i){
			vis[j]=true;
		}
	}
	for(int x:pri){
		if(ask(x)){
			int cur=x;
			while(ask(cur*x)){
				cur*=x;
			}
			ans*=cur;
		}
	}
	cout<<"! "<<ans<<endl;
}