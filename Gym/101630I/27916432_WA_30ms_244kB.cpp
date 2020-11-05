#include<bits/stdc++.h>
using namespace std;
mt19937 rng(20040726); //Kanbe Kotori
const int N=1e4+10;
int n,m,a[N],e[N],o[N],p[N],anse[N],anso[N];
#ifdef memset0
inline bool check(int i,int j){
	return a[i]>a[j+(n>>1)];
}
#else
inline bool check(int i,int j){
	static string input;
	cout<<"? "<<i<<" "<<j<<endl<<flush;
	return cin>>input,input[0]=='>';
}
#endif
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n,m=n>>1;
#ifdef memset0
	for(int i=1;i<=n;i++)cin>>a[i];
#endif
	for(int i=1;i<=m;i++)e[i]=i;
	for(int i=1;i<=n-m;i++)o[i]=i,p[i]=1;
	shuffle(e+1,e+m+1,rng);
	for(int i=1;i<=m;i++){
		int l=1,r=n-m,mid,res=-1;
		while(l<=r){
			mid=(l+r)>>1;
			if(check(e[i],o[mid])){
				l=mid+1;
				res=p[mid];
			}else{
				r=mid-1;
			}
		}
		l=r=res;
		while(r<n-m&&p[r+1]==p[r])r++;
		mid=r;
		if(r<n-m){
			++r;
			while(r<n-m&&p[r+1]==p[r])r++;
		}
		vector<int> lv,rv;
		// cerr<<e[i]<<" >> "<<l<<","<<r<<endl;
		for(int j=l;j<=r;j++)check(e[i],o[j])?lv.push_back(o[j]):rv.push_back(o[j]);
		// cerr<<"LV: ";for(int x:lv)cerr<<x<<" ";cerr<<endl;
		// cerr<<"RV: ";for(int x:rv)cerr<<x<<" ";cerr<<endl;
		anse[e[i]]=(l-1+lv.size())<<1;
		for(int j=0;j<lv.size();j++)o[l+j]=lv[j];
		for(int j=0;j<rv.size();j++)o[l+lv.size()+j]=rv[j];
		if(rv.size()){
			l=r=l+lv.size();
			while(r<n-m&&p[r+1]==p[r])p[r]=l,r++;
			p[r]=l;
		}
		// for(int i=1;i<=n-m;i++)cerr<<o[i]<<" \n"[i==n-m];
		// for(int i=1;i<=n-m;i++)cerr<<p[i]<<" \n"[i==n-m];
	}
	for(int i=1;i<=n-m;i++)anso[o[i]]=(i<<1)-1;
	cout<<"! ";
	for(int i=1;i<=m;i++)cout<<anse[i]<<' ';
	for(int i=1;i<=n-m;i++)cout<<anso[i]<<" \n"[i==n-m];
}