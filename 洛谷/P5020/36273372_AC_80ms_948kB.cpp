// luogu-judger-enable-o2
/*
Sooke bless me.
LJC00118 bless me.
Dilute bless me.
memset0 bless me.
memset1 bless me.
Daniel14311531 bless me.
T_AK bless me.
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

int a[110],n,T,cnt;
bool vis[25010];
int main(){
	scanf("%d",&T);
	for(int fd=1;fd<=T;++fd){
		scanf("%d",&n);
		memset(vis,0,sizeof vis);
		for(int i=1;i<=n;++i)scanf("%d",a+i);
		std::sort(a+1,a+n+1);
		vis[0]=1;
		cnt=0;
		for(int i=1;i<=n;++i)
			if(!vis[a[i]]){
				++cnt;
				for(int j=a[i];j<=a[n];++j)
					if(vis[j-a[i]])vis[j]=1;
			}
		printf("%d\n",cnt);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
