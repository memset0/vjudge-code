#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l),i##end=(r);i<=i##end;i++)
#define per(i,l,r) for(int i=(l),i##end=(r);i>=i##end;i--)
using namespace std;
const int N=5e5+9;
int n,a[N],p[N];
int main(){
#ifdef memset0
	freopen("C.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	rep(i,1,n)cin>>a[i];
	sort(a+1,a+n+1);
	multiset<int> st;
	for(int i=1;i<n-i;i++){
		st.insert(a[i]+a[n-i]);
		p[i]=n-i;
		p[n-i]=i;
	}
	int ans=(*--st.end())-(*st.begin());
	for(int i=n,j=n-1;j>=1;i--,j--){
		st.erase(st.find(a[j]+a[p[j]]));
		st.insert(a[i]+a[p[j]]);
		int k=p[j];
		p[k]=i;
		p[i]=k;
		ans=min(ans,(*--st.end())-(*st.begin()));
		// fprintf(stderr,"%d->%d\n",i,j);
		// for(int x:st)cerr<<x<<endl;
	}
	cout<<ans<<endl;
}