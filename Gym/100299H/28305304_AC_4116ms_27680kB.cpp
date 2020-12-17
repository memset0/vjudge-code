#include <bits/stdc++.h>
using namespace std;
const int N=1e6+9,inf=0x3f3f3f3f;
int T,n,x[N][3][2];
vector<int> v[3];
inline bool check(int d1,int d2){
	if(!v[d1].size()||!v[d2].size())return true;
	int d=d1,L=inf,R=-inf;
	for(int i:v[d1])L=min(L,x[i][d][1]),R=max(R,x[i][d][0]);
	for(int i:v[d2])if(x[i][d][0]>L||x[i][d][1]<R)return false;
	d=d2,L=inf,R=-inf;
	for(int i:v[d1])L=min(L,x[i][d][1]),R=max(R,x[i][d][0]);
	for(int i:v[d2])if(x[i][d][0]>L||x[i][d][1]<R)return false;
	d=3-d1-d2,L=inf,R=-inf;
	for(int i:v[d1])L=min(L,x[i][d][1]),R=max(R,x[i][d][0]);
	for(int i:v[d2])if(x[i][d][0]>L||x[i][d][1]<R)return false;
	return true;
}
int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>T;
	while(T--){
		v[0].clear(),v[1].clear(),v[2].clear();
    cin>>n;
		for(int i=1;i<=n;++i){
			cin>>x[i][0][0]>>x[i][1][0]>>x[i][2][0];
			cin>>x[i][0][1]>>x[i][1][1]>>x[i][2][1];
			if(x[i][0][0]>x[i][0][1])swap(x[i][0][0],x[i][0][1]);
			if(x[i][1][0]>x[i][1][1])swap(x[i][1][0],x[i][1][1]);
			if(x[i][2][0]>x[i][2][1])swap(x[i][2][0],x[i][2][1]);
			if(x[i][0][0]==x[i][0][1])v[0].push_back(i);
			if(x[i][1][0]==x[i][1][1])v[1].push_back(i);
			if(x[i][2][0]==x[i][2][1])v[2].push_back(i);
		}
		if(v[0].size()&&(v[1].size()||v[2].size())&&check(0,1)&&check(0,2)){cout<<"YES"<<endl;continue;}
		if(v[1].size()&&(v[0].size()||v[2].size())&&check(1,0)&&check(1,2)){cout<<"YES"<<endl;continue;}
		if(v[2].size()&&(v[0].size()||v[1].size())&&check(2,0)&&check(2,1)){cout<<"YES"<<endl;continue;}
    cout<<"NO"<<endl;
	}
	return 0;
}//