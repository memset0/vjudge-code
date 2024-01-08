#include<bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
using pii=pair<int,int>;
const int N=25;
int n,bl,wl;
string s;
bool ban[N];
pii b[N],w[N];
pii move(pii u,char c){
	if(c=='L')--u.first;
	if(c=='R')++u.first;
	if(c=='D')--u.second;
	if(c=='U')++u.second;
	return u;
}
int main(){
#ifdef memset0
	freopen("E.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>s;
	vector<pii> ans;
	for(int x=0;x<(1<<n);x++){
		for(int i=0;i<n;i++)ban[i]=(x>>i)&1;
		bl=wl=0;
		pii u={0,0};
		w[wl++]={0,0};
		for(int i=0;i<n;i++){
			pii v=move(u,s[i]);
			if(ban[i]){
				b[bl++]=v;	
			}else{
				w[wl++]=v;
				u=v;
			}
		}
		bool fl=true;
		for(int i=0;fl&&i<bl;i++)
			for(int j=0;j<wl;j++)
				if(b[i]==w[j]){
					fl=false;
					break;
				}
		if(fl){
			ans.push_back(u);
		}
	}
	sort(all(ans));
	ans.erase(unique(all(ans)),ans.end());
	cout<<ans.size()<<endl;
	for(const auto &it:ans){
		cout<<it.first<<" "<<it.second<<'\n';
	}
}