#include "bits/stdc++.h"

int a[2011],b[2011];
int main()
{
	int task;
	scanf("%d",&task);
	while(task--)
	{
		int n;scanf("%d",&n);
		int premax=0;
		for(int i=1;i<=n;++i)scanf("%d",&a[i]);
		bool fail=0;
		for(int i=1;i<=n;++i)
		{
			if(a[i]==a[i-1]||a[i]==a[i-1]+1)
			{
				b[i]=a[i],premax=std::max(premax,a[i]);
			}
			else{fail=1;break;}
		}
		if(fail)puts("NO");
		else
		{
			puts("YES");
			for(int i=1;i<=n;++i)printf("%d ",a[i]);
			puts("");
		}
	}
	return 0;
}