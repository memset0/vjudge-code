#include <bits/stdc++.h>
using namespace std;
const int MAXN=110;
int t,n,m,cnt,a[MAXN][MAXN],md[MAXN*MAXN*10][2];
int hs (int x,int y) {return (x-1)*m+y;}
void trip (int x,int y,int t) {
	if (t==1) {
		cnt++;
		md[cnt][0]=2,md[cnt][1]=y;
		cnt++;
		md[cnt][0]=1,md[cnt][1]=x;
		cnt++;
		md[cnt][0]=2,md[cnt][1]=y;
		cnt++;
		md[cnt][0]=1,md[cnt][1]=x;
		swap(a[x][y],a[x][m-y+1]);
		swap(a[x][y],a[n-x+1][y]);
	} else if (t==2) {
		cnt++;
		md[cnt][0]=1,md[cnt][1]=x;
		cnt++;
		md[cnt][0]=2,md[cnt][1]=m-y+1;
		cnt++;
		md[cnt][0]=1,md[cnt][1]=x;
		cnt++;
		md[cnt][0]=2,md[cnt][1]=m-y+1;
		swap(a[x][y],a[n-x+1][m-y+1]);
		swap(a[x][m-y+1],a[n-x+1][m-y+1]);
	} else if (t==3) {
		cnt++;
		md[cnt][0]=1,md[cnt][1]=n-x+1;
		cnt++;
		md[cnt][0]=2,md[cnt][1]=y;
		cnt++;
		md[cnt][0]=1,md[cnt][1]=n-x+1;
		cnt++;
		md[cnt][0]=2,md[cnt][1]=y;
		swap(a[x][y],a[n-x+1][y]);
		swap(a[n-x+1][y],a[n-x+1][m-y+1]);
	} else {
		cnt++;
		md[cnt][0]=2,md[cnt][1]=m-y+1;
		cnt++;
		md[cnt][0]=1,md[cnt][1]=n-x+1;
		cnt++;
		md[cnt][0]=2,md[cnt][1]=m-y+1;
		cnt++;
		md[cnt][0]=1,md[cnt][1]=n-x+1;
		swap(a[x][m-y+1],a[n-x+1][m-y+1]);
		swap(a[x][m-y+1],a[n-x+1][y]);
	}
	return;
}
int solve (int x,int y,int t) {
	int uu=a[x][y],vv=a[x][m-y+1],xx=a[n-x+1][y],yy=a[n-x+1][m-y+1];
	int tmp1[5],tmp2[5];
	tmp1[1]=uu,tmp1[2]=vv,tmp1[3]=xx,tmp1[4]=yy;
	tmp2[1]=hs(x,y),tmp2[2]=hs(x,m-y+1),tmp2[3]=hs(n-x+1,y),tmp2[4]=hs(n-x+1,m-y+1);
	sort(tmp1+1,tmp1+5);
	sort(tmp2+1,tmp2+5);
	for (int i=1;i<=4;i++) {if (tmp1[i]!=tmp2[i]) {return 0;}}
	int u=(uu>vv)+(uu>xx)+(uu>yy)+1,v=(vv>uu)+(vv>xx)+(vv>yy)+1;
	int xxx=(xx>uu)+(xx>vv)+(xx>yy)+1,yyy=(yy>uu)+(yy>vv)+(yy>xx)+1;
	if (v==1) {
		trip(x,y,2),trip(x,y,2);
	} else if (xxx==1) {
		trip(x,y,1);
	} else if (yyy==1) {
		trip(x,y,2);
	}
	uu=a[x][y],vv=a[x][m-y+1],xx=a[n-x+1][y],yy=a[n-x+1][m-y+1];
	u=(uu>vv)+(uu>xx)+(uu>yy)+1,v=(vv>uu)+(vv>xx)+(vv>yy)+1;
	xxx=(xx>uu)+(xx>vv)+(xx>yy)+1,yyy=(yy>uu)+(yy>vv)+(yy>xx)+1;
	if (xxx==2) {
		trip(x,y,4);
	} else if (yyy==2) {
		trip(x,y,4),trip(x,y,4);
	}
	uu=a[x][y],vv=a[x][m-y+1],xx=a[n-x+1][y],yy=a[n-x+1][m-y+1];
	u=(uu>vv)+(uu>xx)+(uu>yy)+1,v=(vv>uu)+(vv>xx)+(vv>yy)+1;
	xxx=(xx>uu)+(xx>vv)+(xx>yy)+1,yyy=(yy>uu)+(yy>vv)+(yy>xx)+1;
	if (xxx==3) {return 1;}
	if (t==0) {return 0;}
	if (t==1) {
		cnt++;
		md[cnt][0]=1,md[cnt][1]=n-x+1;
		for (int i=1;i<=m/2;i++) {swap(a[n-x+1][i],a[n-x+1][m-i+1]);}
	} else {
		cnt++;
		md[cnt][0]=2,md[cnt][1]=y;
		for (int i=1;i<=n/2;i++) {swap(a[i][y],a[n-i+1][y]);}
		trip(x,y,3);
	}
	return 1;
}
void print () {
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=m;j++) {
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return;
}
int main () {
	scanf("%d",&t);
	for (int ii=1;ii<=t;ii++) {
		scanf("%d%d",&n,&m); 
		swap(n,m);
		cnt=0;
		for (int i=1;i<=n;i++) {
			for (int j=1;j<=m;j++) {
				scanf("%d",&a[i][j]);
			}
		}
		int flg=0;
		if (n!=1&&m!=1) {
			
		for (int i=1;i<=n/2;i++) {
			if (!solve(i,1,1)) {flg=1;break;}
		}
		for (int j=2;j<=m/2;j++) {
			if (!solve(1,j,2)) {flg=1;break;}
		}
		
		}
		//print();
		for (int i=2;i<=n/2;i++) {
			if (flg) {break;}
			for (int j=2;j<=m/2;j++) {
				if (!solve(i,j,0)) {
					flg=1;
					break;
				}
			}
		}
		//print();
		if (n%2==1) {
			int flg2=1,rw=(n+1)/2;
			for (int i=1;i<=m;i++) {
				if (a[rw][i]!=hs(rw,i)) {flg2=0;break;}
			}
			if (!flg2) {
				flg2=1;
				for (int i=1;i<=m;i++) {
					if (a[rw][i]!=hs(rw,m-i+1)) {flg2=0,flg=1;break;}
				}
				if (flg2) {
					cnt++;
					md[cnt][0]=1,md[cnt][1]=rw;
					for (int i=1;i<=m/2;i++) {swap(a[rw][i],a[rw][m-i+1]);}
				}
			}
		}
		if (m%2==1) {
			int flg2=1,col=(m+1)/2;
			for (int i=1;i<=n;i++) {
				if (a[i][col]!=hs(i,col)) {flg2=0;break;}
			}
			if (!flg2) {
				flg2=1;
				for (int i=1;i<=n;i++) {
					if (a[i][col]!=hs(n-i+1,col)) {flg2=0,flg=1;break;}
				}
				if (flg2) {
					cnt++;
					md[cnt][0]=2,md[cnt][1]=col;
					for (int i=1;i<=n/2;i++) {swap(a[i][col],a[n-i+1][col]);}
				}
			}
		}
		if (flg) {
			printf("IMPOSSIBLE\n");
		} else {
			printf("POSSIBLE %d",cnt);
			for (int i=1;i<=cnt;i++) {
				if (md[i][0]==1) {printf(" R%d",md[i][1]);}
				else {printf(" C%d",md[i][1]);}
			}
			printf("\n");
		}
	}
	return 0;
}