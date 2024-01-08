#include<bits/stdc++.h>
using namespace std;
const int N=3e4+9;
int T,n;
struct pt{
	int x,y,id;
	inline bool operator<(const pt &rhs)const{
		return x==rhs.x?y<rhs.y:x<rhs.x;
	}
}a[N];
int main(){
#ifdef memset0
	freopen("C.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		n*=3;
		for(int i=1;i<=n;i++){
			cin>>a[i].x>>a[i].y;
			a[i].id=i;
		}
		sort(a+1,a+n+1);
		n/=3;
		for(int i=1;i<=n;i++){
			cout<<a[i*3-2].id<<" "<<a[i*3-1].id<<" "<<a[i*3].id<<endl;
		}
	}
}