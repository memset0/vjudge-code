#include <cstdio>
#include <algorithm>
 
int n,a[100001],ans=100000;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",a+i);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=60&&j<i;j++){
			int X=0;
			for(int k=0;k<=j;k++)X^=a[i-k];
			if((i<n&&X>a[i+1])||((i-j>1)&&X<a[i-j-1]))ans=std::min(ans,j);
		}
	}
	if(ans==100000)puts("-1");
	else printf("%d\n",ans);
}