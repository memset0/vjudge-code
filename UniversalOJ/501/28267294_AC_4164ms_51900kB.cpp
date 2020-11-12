#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=1e6+10;
int n,res[N],a[2][N],min[2][N],max[2][N];
void dfs(int i,int w,int lst){
	res[i]=w,lst-=w;
	if(i==1){
		for(int i=1;i<=(n<<1);i++)putchar('A'+res[i]);
		putchar('\n'),exit(0);
	}
	if(a[0][i-1]<=a[w][i]&&min[0][i-1]<=lst&&lst<=max[0][i-1])dfs(i-1,0,lst);
	if(a[1][i-1]<=a[w][i]&&min[1][i-1]<=lst&&lst<=max[1][i-1])dfs(i-1,1,lst);
}
int main(){
#ifdef local
	freopen("1.in","r",stdin);
#endif
	read(n);
	for(int i=1;i<=(n<<1);i++)read(a[0][i]);
	for(int i=1;i<=(n<<1);i++)read(a[1][i]);
	min[0][1]=max[0][1]=0;
	min[1][1]=max[1][1]=1;
	for(int i=2;i<=(n<<1);i++)
		for(int k=0;k<2;k++){
			min[k][i]=1e9,max[k][i]=-1e9;
			if(a[0][i-1]<=a[k][i])min[k][i]=std::min(min[k][i],min[0][i-1]+k),max[k][i]=std::max(max[k][i],max[0][i-1]+k);
			if(a[1][i-1]<=a[k][i])min[k][i]=std::min(min[k][i],min[1][i-1]+k),max[k][i]=std::max(max[k][i],max[1][i-1]+k);
		}
	if(min[0][n<<1]<=n&&n<=max[0][n<<1])dfs(n<<1,0,n);
	if(min[1][n<<1]<=n&&n<=max[1][n<<1])dfs(n<<1,1,n);
	puts("-1");
}