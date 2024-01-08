#include<bits/stdc++.h>
using namespace std;
const int A=1e3;
int T,g,n,a,sz;
map<string,int>ap;
string tmp[A+10],na[A+10];
void Solve(int l,int r,int tt,int dir){
	if(!n)return;
	//cout<<"SOLVE "<<l<<" "<<r<<" "<<tt<<" "<<dir<<"\n";
	if(dir){
		if(tt==1){
			for(int i=l+1;i<=r&&n;++i){
				cout<<na[i-1]<<" "<<na[i]<<"\n";
				--n;
			}
			//cout<<"END.\n";
			return;
		}else{
			for(int i=l;i+tt<=r&&n;++i){
				if((i-l)&1){
					Solve(i+1,r,tt-1,0);
					if(!n)break;
					cout<<na[i]<<" "<<na[i+tt]<<"\n";
					--n;
				}else{
					Solve(i+1,r,tt-1,1);
					if(!n)break;
					cout<<na[i]<<" "<<na[i+1]<<"\n";
					--n;
				}
			}
		}
	}else{
		if(tt==1){
			for(int i=r-1;i>=l&&n;--i){
				cout<<na[i+1]<<" "<<na[i]<<"\n";
				--n;
			}
			//cout<<"END.\n";
			return;
		}else{
			for(int i=r;i-tt>=l&&n;--i){
				if((r-i)&1){
					Solve(l,i-1,tt-1,1);
					if(!n)break;
					cout<<na[i]<<" "<<na[i-tt]<<"\n";
					--n;
				}else{
					Solve(l,i-1,tt-1,0);
					if(!n)break;
					cout<<na[i]<<" "<<na[i-1]<<"\n";
					--n;
				}
			}
		}
	}
	//cout<<"END.\n";
}
int main(){
	cin>>T;
	while(T--){
		cin>>g>>n>>a;
		ap.clear();
		for(int i=1;i<=a;++i)cin>>tmp[i];
		for(int i=1;i<=g;++i)cin>>na[i],ap[na[i]]=1;
		sz=g;
		for(int i=1;i<=a;++i)if(!ap[tmp[i]])na[++sz]=tmp[i];
		//for(int i=1;i<=a;++i)cout<<"A "<<i<<"="<<na[i]<<"\n";
		--n,Solve(1,a,g,1);
		assert(!n);
		if(T)cout<<'\n';
	}
	return 0;
}
/*
2
2 4 4
ali bob carl dude
ali bob
2 4 5
ali bob carl dude earl
carl dude
3
4 13 6
1 2 3 4 5 6
1 2 3 4
4 14 6
1 2 3 4 5 6
1 2 3 4
4 15 6
1 2 3 4 5 6
1 2 3 4

1
2 6 4
1 2 3 4
1 2
*/