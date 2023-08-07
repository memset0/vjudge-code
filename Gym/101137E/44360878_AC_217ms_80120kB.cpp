#include<bits/stdc++.h>
#define N 300005
#define re 
#define ll long long
using namespace std;
int n,m,K,q,T;
inline void Rd(int &res){
	re char c;res=0;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
	while(c=getchar(),c>47);
} 
int a[N],f[N][4][4],cnt[N];
struct node{
	int x,t1,t2;
}pre[N][4][4];
int to[N];
bool mk[N];
int ans[N],tot;
int main(){
	Rd(n);
	for(re int i=1;i<=n;i++)Rd(a[i]);
	sort(a+1,a+n+1);
	for(re int i=1;i<=n;i++){
		int v=a[i];
		while(v)cnt[i]++,v/=10;
	}
	for(re int i=0;i<=n;i++)
		for(re int j=0;j<4;j++)
			for(re int k=0;k<4;k++)f[i][j][k]=1e9;
	
	f[0][0][0]=0;
	for(re int i=1;i<=n;i++)
		for(re int j=0;j<4;j++)
			for(re int k=0;k<4;k++)if(f[i-1][j][k]<1e9){
				
				int res=f[i-1][j][k]+1+cnt[i];
				if(res<f[i][k][0]){
					f[i][k][0]=res;
					pre[i][k][0]=(node){0,j,k};
				}
				res=f[i-1][j][k]+1+cnt[i]+1+cnt[i];
				if(res<f[i][k][1]){
					f[i][k][1]=res;
					pre[i][k][1]=(node){0,j,k};
				}
				if(res<f[i][k][2]){
					f[i][k][2]=res;
					pre[i][k][2]=(node){0,j,k};
				}
				if(res<f[i][k][3]){
					f[i][k][3]=res;
					pre[i][k][3]=(node){0,j,k};
				}
				
				if(j==1||j==2){
					if(i>2&&a[i]-a[i-2]==2&&f[i][k][j]>f[i-1][j][k]+cnt[i]-cnt[i-2]){
						f[i][k][j]=f[i-1][j][k]+cnt[i]-cnt[i-2];
						pre[i][k][j]=(node){i-2,j,k};
					}
				}
				if(k==1||k==2){
					if(i>1&&a[i]-a[i-1]==2&&f[i][k][k]>f[i-1][j][k]+cnt[i]-cnt[i-1]){
						f[i][k][k]=f[i-1][j][k]+cnt[i]-cnt[i-1];
						pre[i][k][k]=(node){i-1,j,k};
					}
				}
				
				if(k==3){
					if(i>1&&a[i]-a[i-1]==1&&f[i][k][k]>f[i-1][j][k]+cnt[i]-cnt[i-1]){
						f[i][k][k]=f[i-1][j][k]+cnt[i]-cnt[i-1];
						pre[i][k][k]=(node){i-1,j,k};
					}
					
				}
				
			}
	
//	for(re int j=0;j<4;j++)
//		for(re int k=0;k<4;k++)
//			if(f[n][j][k]!=1e9)printf("f[%d][%d][%d]=%d\n",n,j,k,f[n][j][k]);
	
	int x0=0,y0=0,ans0=1e9;
	for(re int j=0;j<4;j++)
		for(re int k=0;k<4;k++)if(f[n][j][k]<ans0){
			ans0=f[n][j][k];
			x0=j,y0=k;
		} 
	
	int t1=x0,t2=y0;
	for(re int i=n;i>=1;i--){
		to[i]=pre[i][t1][t2].x;
		int x1=pre[i][t1][t2].t1;
		int y1=pre[i][t1][t2].t2;
		t1=x1;
		t2=y1;
	}
	
	mk[0]=1;
	bool f=1;
	for(re int i=n;i>=1;i--)if(!mk[i]){
		int p=i;tot=0;
		while(!mk[p]){
			ans[++tot]=a[p];
			mk[p]=1;
			p=to[p];
		}
		if(f==0)putchar(',');
		else f=0;
		if(tot==1)printf("%d",ans[1]);
		else if(ans[1]-ans[2]==1)printf("%d-%d",ans[tot],ans[1]);
		else{
			if(ans[1]%2==1)printf("%d#%d",ans[tot],ans[1]);
			else printf("%d%%%d",ans[tot],ans[1]);
		}
	}
	
	putchar('\n');
	
	
	
	return 0;
}


