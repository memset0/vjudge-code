#include<bits/stdc++.h>
using namespace std;
const int M=100009;
int n;
int a[M],b[M];
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; i++)scanf("%d",&a[i]);
	for(int i=1; i<=n; i++)scanf("%d",&b[i]);
	sort(a+1,a+1+n);
	sort(b+1,b+1+n);
	int l1=1,l2=1,r1=n,r2=n,ans=0;
	while(l1<=r1&&l2<=r2) {
		if(a[l1]>b[l2])ans+=2,l1++,l2++;
		else if(a[r1]>b[r2])ans+=2,r1--,r2--;
		else if(a[l1]==b[r2])ans++,l1++,r2--;
		else l1++,r2--;
	}
	printf("%d ",ans);
	l1=1,l2=1,r1=n,r2=n,ans=0;
	while(l1<=r1&&l2<=r2) {
		if(b[l1]>a[l2])ans+=2,l1++,l2++;
		else if(b[r1]>a[r2])ans+=2,r1--,r2--;
		else if(b[l1]==a[r2])ans++,l1++,r2--;
		else l1++,r2--;
	}
	printf("%d\n",2*n-ans);
	return 0;
}