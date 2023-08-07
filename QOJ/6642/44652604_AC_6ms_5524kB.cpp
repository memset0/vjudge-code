#include "bits/stdc++.h"
const int MAXN = 1000011;
int a[MAXN];
int main()
{
	std::ios::sync_with_stdio(0),std::cin.tie(0);
	int task;
	std::cin>>task;
	while(task--)
	{
		int n,cnt=0;std::cin>>n;
		for(int i=1;i<=n;++i)
		{
			std::cin>>a[i];
			cnt+= (a[i]>1);
		}
		if(cnt>=2)puts("Grundy");
		else if(cnt==1)puts(n%3==0|n%3==1?"Sprague":"Grundy");
		else puts(n%3==1?"Sprague":"Grundy");
	}
	return 0;
}