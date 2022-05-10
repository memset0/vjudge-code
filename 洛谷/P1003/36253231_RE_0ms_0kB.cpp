#include <iostream>
#include <cstdio>
using namespace std;
int db[20000][20000];
int main()
{
	int n,a,b,g,k,x,y;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d%d%d",&a,&b,&g,&k);
		for (int ii=a;ii<=(a+g-1);ii++)
		for (int iii=b;iii<=(b+k-1);iii++)
		db[ii][iii]=i;
	}
	scanf("%d%d",x,y);
	printf("%d",db[x][y]);
	return 0;
}