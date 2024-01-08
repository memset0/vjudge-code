#include<bits/stdc++.h>
#include <stdio.h>
using namespace std;
const int N=1e4;
int n,m,n1,n2,sz;
string s1[N+10],s2[N+10],tmp,rk[(N<<1)+10];
map<string,int>mp;
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		cin>>tmp;
		if(!mp[tmp])mp[tmp]=1,s1[++n1]=tmp;
	}
	mp.clear();
	for(int i=1;i<=m;++i){
		cin>>tmp;
		if(!mp[tmp])mp[tmp]=1,s2[++n2]=tmp;
	}
	mp.clear();
	for(int i=1;i<=n1||i<=n2;++i){
		if(i<=n1){
			if(!mp[s1[i]])mp[s1[i]]=1,rk[++sz]=s1[i];
		}
		if(i<=n2){
			if(!mp[s2[i]])mp[s2[i]]=1,rk[++sz]=s2[i];
		}
	}
	for(int i=1;i<=sz;++i)cout<<rk[i]<<"\n";
	return 0;
}