#include<bits/stdc++.h>
using namespace std;
char v[2001][5];
int zz=0;
bool ok=false;
void fuck(int x,int y,int z) {
	if(!ok)++zz;
	if(ok)cout<<v[x]<<' '<<v[y]<<' '<<v[z]<<'\n';
}
void ffk(int r,int dx,int dy,int dz) {
	for(int i=0;i<r;++i) {
		for(int j=0;j<r;++j) {
			int z=(i+j)%r;
			fuck(i+dx,j+dy,z+dz);
		}
	}
}
int main() {
	cin.sync_with_stdio(false); cin.tie(0);
	int n; cin>>n;
	for(int i=1;i<=2000;++i) {
		sprintf(v[i],"%d",i);
	}
	ffk(n/2,1,1,1);
	ffk(n-n/2,n/2+1,n/2+1,n/2+1);
	cout<<zz<<'\n';
	ok=true;
	ffk(n/2,1,1,1);
	ffk(n-n/2,n/2+1,n/2+1,n/2+1);
	return 0;
}