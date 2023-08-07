#include<bits/stdc++.h>
using namespace std;
vector<string> ans;
struct frac{
	int n,m;
	bool fl;
	// fl=0 10^n / (10^m - 1)
	// fl=1 (10^n - 1) / 10^m
	frac trans(){
		frac y;
		string s;
		y.fl=fl^1;
		if(fl==0){
			if(n<m){
				s+='0';
				y.n=m;
				y.m=n;
			}else{
				int t=n%m;
				s+='1';
				for(int i=0;i<n/m-1;i++){
					for(int j=0;j<m-1;j++)s+='0';
					s+='1';
				}
				for(int i=0;i<t;i++)s+='0';
				y.n=m;
				y.m=t;
			}
		}else{
			for(int i=0;i<n-m;i++){
				s+='9';
			}
			y.n=m;
			y.m=m;
		}
		ans.push_back(s);
		return y;
	}
}x;
int main(){
#ifdef memset0
	// freopen("F.in","r",stdin);
	freopen("continued.in","r",stdin);
#else
	freopen("continued.in","r",stdin);
	freopen("continued.out","w",stdout);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>x.n>>x.m;
	while(!(x.fl==true&&x.m==0)){
		x=x.trans();
	}
	x.trans();
	cout<<((int)ans.size()-1)<<endl;
	for(int i=0;i<ans.size();i++){
		cout<<ans[i]<<" \n"[i+1==ans.size()];
	}
}