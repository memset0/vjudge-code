#include"prize.h"
#include<bits/stdc++.h>
std::mt19937 rng(20030417^std::chrono::steady_clock::now().time_since_epoch().count());
template<class T> inline T rand(T l,T r){return std::uniform_int_distribution<T>(l,r)(rng);}
namespace mem{
	int n,all;
	std::vector<std::pair<int,int>> res;
	std::pair<int,int> ask(int k){
		// printf("ask %d\n",k);
		--k;
		if(res[k].first||res[k].second)return res[k];
		const auto &v=::ask(k);
		if(v[0]+v[1]==0)throw k;
		return res[k]={v[0],v[1]};
	}
	void solve(int l,int r,int lsum,int rsum){
		// printf("solve %d %d %d %d\n",l,r,lsum,rsum);
		if(l>r)return;
		int mid=(l+r)>>1;
		std::pair<int,int> p=ask(mid);
		const std::function<void(int,int)> trans[2]={[&](int ml,int mr){
			if(p.first>lsum)solve(l,ml-1,lsum,p.second);
			if(p.second>rsum)solve(mr+1,r,p.first,rsum);
		},[&](int ml,int mr){
			if(p.second>rsum)solve(mr+1,r,p.first,rsum);
			if(p.first>lsum)solve(l,ml-1,lsum,p.second);
		}};
		if(p.first+p.second==all)return trans[rand(0,1)](mid,mid);
		int ml=mid,mr=mid;
		while(ml>l||mr<r){
			if(ml>l){
				p=ask(--ml);
				if(p.first+p.second==all)return trans[rand(0,1)](ml,mr);
			}
			if(mr<r){
				p=ask(++mr);
				if(p.first+p.second==all)return trans[rand(0,1)](ml,mr);
			}
		}
	}
	void main(){
		res.resize(n);
		for(int i=1;i<=450&&all<=300;i++){
			ask(rand(1,n));
			std::pair<int,int> p=ask(rand(1,n));
			all=std::max(all,p.first+p.second);
		}
		// printf("all=%d\n",all);
		solve(1,n,0,0);
	}
}
int find_best(int _n){try{mem::n=_n,mem::main();}catch(int e){return e;}}