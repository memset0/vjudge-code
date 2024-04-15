#include "bits/stdc++.h"
using namespace std;

int query(int x)
{
	cout<<"? "<<x<<endl;
	int f;
	cin>>f;
	return f;
}
int main()
{
	int n;
	cin>>n;
	int l=1,r=n,pre=0;
	while(l<r)
	{
		int mid=(l+r+1)>>1;
		int g=query(l);
		if(g==pre)
		{
			r=l;break;
		}
		int f=query(mid);
		if(f==pre+2)l=mid+1;
		else if(f==pre)++l,r=mid-1;
		else{l=r=mid;break;}
		pre=f;
	}
	cout<<"! "<<l<<endl;
	return 0;
}