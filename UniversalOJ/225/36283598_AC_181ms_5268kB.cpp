#include<bits/stdc++.h>
int n,m,k;
std::vector<std::pair<int,int>> f[2];
inline void no_solution(){puts("-1"),exit(0);}
int main(){
#ifdef local
	freopen("1.in","r",stdin);
#endif
	scanf("%d%d%d",&n,&m,&k);
	if(k==1)no_solution();
	if(k==2&&n>1&&m>1)no_solution();
	if(n<=2||m<=2){
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				f[(i+j)&1].push_back({i,j});
	}else{
		if(!(m&1)){
			for(int i=0;i<n;i++)
				for(int j=0;j<m;j++)
					f[((i>>1)+j)&1].push_back({i,j});
		}else{
			for(int i=0;i<n;i++)
				for(int j=0;j<m;j++)
					f[(i+(j>>1))&1].push_back({i,j});
		}
	}
	if(f[0].size()<f[1].size())std::swap(f[0],f[1]);
	for(int x,y,fl=0;f[fl].size();fl^=1){
		std::tie(x,y)=f[fl].back(),f[fl].pop_back();
		printf("%d %d\n",x+1,y+1);
	}
}