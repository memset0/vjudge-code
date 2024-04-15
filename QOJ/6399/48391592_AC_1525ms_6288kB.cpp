#include<bits/stdc++.h>
#define all(x) begin(x),end(x)
#ifndef memset0
#define endl '\n'
#endif
using namespace std;
const int N=2e5+9;
int T,n,p,a[N],lg[N],ilg[N];
bool t[N];
bitset<N> b,c,d;
pair<vector<int>,int> bruteforce(){
	vector<int> sol;
	int ans=-1;
	for(int mex,c=0;c<p;c++){
		for(int i=0;i<p;i++)t[i]=false;
		for(int i=1;i<=n;i++)t[(long long)(c*a[i])%p]=true;
		for(mex=0;t[mex];mex++);
		if(mex>ans){
			ans=mex;
			sol={c};
		}else if(ans==mex){
			sol.push_back(c);
		}
	}
	return {sol,ans};
}
pair<vector<int>,int> solve(){
	b.reset();
	bool fl=false;
	for(int i=1;i<=n;i++){
		if(a[i])b.set((p-1-lg[a[i]])%(p-1));
		else fl=true;
	}
	if(!fl){
		return {{0},1};
	}
	c.reset();
	for(int i=0;i<p-1;i++){
		c.set(i);
	}
	for(int mex=1;;mex++){
		int x=lg[mex];
		d=c&((b<<x)|(b>>(p-1-x)));
		// cerr<<"mex="<<mex<<" x="<<x<<endl;
		// for(int i=0;i<p-1;i++)cerr<<c.test(i)<<" \n"[i+1==p-1];
		// for(int i=0;i<p-1;i++)cerr<<((b<<x)|(b>>(p-1-x))).test(i)<<" \n"[i+1==p-1];
		if(d.count()==0){
			vector<int> ans;
			for(size_t i=c._Find_first();i!=c.size();i=c._Find_next(i)){
				ans.push_back(ilg[i]);
			}
			if(mex==1)ans.push_back(0);
			return {ans,mex};
		}else{
			c=d;
		}
	}
	return {{},-1};
}
int main(){
#ifdef memset0
	freopen("F.in","r",stdin);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>n>>p;
		// cerr<<"n="<<n<<" p="<<p<<endl;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int g=1;g<=p;g++){
			fill_n(lg,p+5,-1);
			bool fl=true;
			lg[1]=0;
			for(int i=1,x=g;i<p-1;i++,x=(long long)x*g%p){
				if(lg[x]!=-1){fl=false;break;}
				lg[x]=i;
			}
			if(fl){
				// cerr<<"g="<<g<<endl;
				break;
			}
		}
		for(int i=1;i<p;i++)ilg[lg[i]]=i;
		// for(int i=1;i<p;i++)fprintf(stderr,"lg[%d]=%d\n",i,lg[i]);
		// cerr<<"LOG: ";for(int i=0;i<p;i++)cerr<<lg[i]<<" \n"[i+1==p];
		// cerr<<"ILG: ";for(int i=0;i<p;i++)cerr<<ilg[i]<<" \n"[i+1==p];
		auto ans=p==2?bruteforce():solve();
		cout<<ans.first.size()<<" "<<ans.second<<endl;
		sort(all(ans.first));
		for(int i=0;i<ans.first.size();i++)cout<<ans.first[i]<<" \n"[i+1==ans.first.size()];
		// ans=bruteforce();
		// cout<<ans.first.size()<<" "<<ans.second<<endl;
		// sort(all(ans.first));
		// for(int i=0;i<ans.first.size();i++)cout<<ans.first[i]<<" \n"[i+1==ans.first.size()];
		// assert(ans==bruteforce());
	}
}