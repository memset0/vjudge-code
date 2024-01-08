#include<bits/stdc++.h>
using namespace std;
int T,n;
bool check(int n){
	while(n%2==0)n/=2;
	while(n%5==0)n/=5;
	return n!=1;
}
int main(){
#ifdef memset0
	freopen("D.in","r",stdin);
#endif
	cin>>T;
	while(T--){
		cin>>n;
		cout<<(check(n)?"Yes":"No")<<endl;
	}
}