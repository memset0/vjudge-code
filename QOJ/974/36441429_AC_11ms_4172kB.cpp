#include<bits/stdc++.h>
using namespace std;
const int N=1e5+9;
int n,a[N];
bool b[N<<1];
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++){
			if(b[a[i]^a[j]]){
				cout<<"Yes"<<endl;
				return 0;
			}
			b[a[i]^a[j]]=true;
		}
	cout<<"No"<<endl;
}