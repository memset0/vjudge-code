#include<bits/stdc++.h>
#define all(x) begin(x),end(x)
using namespace std;
using lll=__int128;
const int N=1e5+9;
int n,a[N];
char f[N];
lll sum;
int main(){
#ifdef memset0
	freopen("B.in","r",stdin);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin>>n;
	fill_n(f,n+1,'0');
	char sgn='0';
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=(lll)a[i]*((lll)(1)<<70);
		if(a[i]==0){
			f[i]=f[i-1];
		}else{
			if(sum>0)f[i]='+';
			if(sum<0)f[i]='-';
			if(sum==0)f[i]=sgn;
		}
		if(sum%2==1)sgn='+';
		if(sum%2==-1)sgn='-';
		sum/=2;
	}
	for(int i=1;i<=n;i++)cout<<f[i];
	cout<<endl;
}