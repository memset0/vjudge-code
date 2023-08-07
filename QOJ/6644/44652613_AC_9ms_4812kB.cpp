#include<bits/stdc++.h>
using namespace std;
const int N=1e3+9;
int T,n,m;
bool ans[N][N];
int count(){
	int cnt=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(i+1<=n&&ans[i][j]!=ans[i+1][j])++cnt;
			if(j+1<=n&&ans[i][j]!=ans[i][j+1])++cnt;
		}
	return cnt;
}
bool solve(int n,int m){
	// fprintf(stderr,"=== solve %d %d ===\n",n,m);
	if(n<=3){
		static int id[10][10];
		int tot=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				id[i][j]=tot++;
		for(int x=0;x<(1<<n*n);x++){
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++){
					ans[i][j]=(x>>id[i][j])&1;
				}
			if(count()==m)return true;
		}
		return false;
	}
	if(m==1)return false;
	if(m==2*n*(n-1)-1)return false;
	int cnt[5],cho[5];
	memset(cnt,0,sizeof(cnt));
	memset(cho,0,sizeof(cho));
	cnt[2]=n&1?4:2;
	cnt[3]=((n-2)/2)*4;
	cnt[4]=(n*n+1)/2-cnt[2]-cnt[3];
	// fprintf(stderr,">> %d %d %d\n",cnt[2],cnt[3],cnt[4]);
	if(m&1){
		m-=3;
		--cnt[3];
		++cho[3];
	}
	while(m>=6&&cnt[3]>=2){
		m-=6;
		cnt[3]-=2;
		cho[3]+=2;
	}
	while(m>=4&&cnt[4]){
		m-=4;
		cnt[4]--;
		cho[4]++;
	}
	while(m>=2&&cnt[2]){
		m-=2;
		cnt[2]--;
		cho[2]++;
	}
	// assert(m==0);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			ans[i][j]=false;
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if((i+j)%2==0){
				int cur=4;
				if(i==1||i==n)--cur;
				if(j==1||j==n)--cur;
				if(cho[cur]){
					--cho[cur];
					ans[i][j]=true;
				}
			}
	return true;
}
int main(){
#ifdef memset0
	freopen("N.in","r",stdin);
#endif
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		bool found=solve(n,m);
		if(found){
			printf("Possible\n");
			for(int i=1;i<=n;i++){
				for(int j=1;j<=n;j++){
					putchar(ans[i][j]?'R':'B');
				}
				putchar('\n');
			}
			// assert(count()==m);
		}else{
			printf("Impossible\n");
		}
	}
}