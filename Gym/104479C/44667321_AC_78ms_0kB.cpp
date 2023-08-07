#include<bits/stdc++.h>
using namespace std;
int n,m,tmp;
long long s1,s2;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)scanf("%d",&tmp),s1+=tmp;
	for(int i=1;i<=m;++i)scanf("%d",&tmp),s2+=tmp;
	printf("%lld",s1*s2);
	return 0;
}