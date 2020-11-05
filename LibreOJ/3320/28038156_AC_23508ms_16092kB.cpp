#include<bits/stdc++.h>
const int N=2e3+10;
int n,a[N][N];
char s[N];
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)a[i][i]=-1;
	for(int i=2;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<i;j++)a[i][j]=a[j][i]=s[j]=='B';
	}
	// for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)printf("%d%c",a[i][j]," \n"[j==n]);
	for(int i=1;i<=n;i++){
		int col;
		std::list<int> path{i};
		std::list<int>::iterator it;
		for(int j=1;j<=n;j++)if(i!=j){
			if(path.size()==1){
				path.push_back(j);
				col=a[path.front()][path.back()];
				it=std::prev(path.end());
			}else if(std::next(it)==path.end()){
				path.push_back(j);
				if(col==a[*it][j])++it;
			}else{
				int l=*std::prev(it),m=*it,r=*std::next(it);
				if(a[l][j]==col&&a[j][m]==col)path.insert(it,j);
				else if(a[l][j]!=col&&a[j][m]!=col)path.insert(it,j),--it,--it;
				else if(a[m][j]!=col&&a[j][r]!=col)path.insert(std::next(it),j);
				else if(a[m][j]==col&&a[j][r]==col)path.insert(std::next(it),j),++it,++it;
				else if(a[m][j]==col)path.insert(std::next(it),j),++it;
				else path.insert(it,j),--it;
			}
			if(it==path.begin()){
				it=std::prev(path.end());
				col=a[*path.begin()][*std::next(path.begin())];
			}
			// printf("\e[31m%d\e[2m[%d]\e[0m\e[2m ",*it,col);for(int x:path)printf("%d ",x);printf("\e[0m\n");
		}
		printf("%d\n",n);for(int x:path)printf("%d ",x);putchar('\n');
	}
}
