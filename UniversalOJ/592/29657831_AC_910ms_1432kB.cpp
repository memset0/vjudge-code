#include<bits/stdc++.h>
#include"meeting.h"
using namespace std;
const int N=1e3+9,S=10;
int m;
vector<int> V[N];
vector<pair<int,int>> ans;
mt19937 rng(20040725);
inline bool check(int a,int b){return !meeting({a,b});}
inline bool check(int a,vector<int> x){x.push_back(a); return !meeting(x);}
void solveIn(int u,vector<int> v){
	// fprintf(stderr,"solveIn %d,%d [%d]\n",u,(int)v.size(),check(u,v));
	shuffle(v.begin(),v.end(),rng);
	function<void(int,int)> divide=[&](int l,int r){
		if(l>r||!check(u,vector<int>(v.begin()+l,v.begin()+r)))return;
		if(r-l==1){ans.emplace_back(u,v[l]); return;}
		divide(l,(l+r)>>1);
		divide((l+r)>>1,r);
	};
	if(v.size()&&check(u,v))divide(0,v.size());
}
vector<pair<int,int>> solve(int n){
  vector<int> p;
  for(int i=0;i<n;i++)p.push_back(i);
  shuffle(p.begin(),p.end(),rng);
  while(p.size()){
    V[m]={p.back()},p.pop_back();
    while(p.size()&&!check(p.back(),V[m]))V[m].push_back(p.back()),p.pop_back();
    m++;
  }
  for(int i=0;i<m;i++)
    for(int j=i+1;j<m;j++)
      for(int x:V[i])
        solveIn(x,V[j]);
	return ans;
}
