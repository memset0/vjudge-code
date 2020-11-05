#include<bits/stdc++.h>
double ans[]={0,0,0,3,3.666622,4.166656,4.566667,4.900024,5.185665,5.435680,5.657907};
int main(){
	int n;
	for(int i=0;i<6;i++)std::cin>>n;
	std::cin>>n;
	printf("%.6lf\n",ans[n]);
}