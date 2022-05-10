#include<bits/stdc++.h>
using namespace std;
int main(){
//#ifdef memset0
//	freopen("1.in","r",stdin);
//#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t-->0){
		int n;
		cin>>n;
		vector<int> a(n);
		vector<int> b(n);
		for(int i=0;i<n;i++){
			cin>>a[i];
		}
		for(int i=0;i<n;i++){
			cin>>b[i];
		}
		for(int i=0;i<n;i++)
			if(3*a[i]<b[i]){
				cout<<(i+1)<<endl;
				goto next;
			}
		cout<<-1<<endl;
	next:
		continue;
	}
}