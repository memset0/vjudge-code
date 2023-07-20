#include<bits/stdc++.h>
using namespace std;
int main(){
	cin.tie(0),ios::sync_with_stdio(0);
	int T,n;
	string s;
	cin>>T;
	while(T--){
		cin>>n>>s;
		//cerr<<n<<" "<<s.length()<<endl;
		//cerr<<"'"<<s<<"'"<<endl;
		assert(s.length()==n);
		int i=0;
		while(i<n){
			int j=i+1;
			while(j<n&&s[j]!=s[i])j++;
			//cerr<<i<<" "<<j;
			assert(j<n);
			cout<<s[j];
			i=j+1;
		}
		cout<<endl;
	}
}
