#include<bits/stdc++.h>
using namespace std;
const int N=309;
int n,m,k,tot;
char b[N][2];
vector<char> a[N];
int main(){
#ifdef memset0
	freopen("K.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>m>>k;
	if(m>=k){
		cout<<"No"<<endl;
		return 0;
	}
	for(int i=0;i<n;i++){
		a[i].resize(k);
	}
	if(m==0){
		if(n>26){
			cout<<"No"<<endl;
			return 0;
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<k;j++){
				a[i][j]='a'+i;
			}
		}
	}else{
		for(char i='b';i<='z';i++)
			for(char j=i+1;j<='z';j++){
				b[tot][0]=i;
				b[tot][1]=j;
				tot++;
			}
		for(int i=0;i<n;i++){
			// cout<<i<<" "<<b[i][0]<<" "<<b[i][1]<<endl;
			for(int j=0;j<m-1;j++)a[i][j]='a';
			for(int x=0,j=m-1;j<k;j++,x^=1){
				// cerr<<i<<" "<<j<<" "<<x<<" "<<b[i][x]<<endl;
				a[i][j]=b[i][x];
			}
		}
	}
	cout<<"Yes"<<endl;
	for(int i=0;i<n;i++){
		for(int j=0;j<k;j++){
			cout<<a[i][j];
		}
		cout<<endl;
	}
}