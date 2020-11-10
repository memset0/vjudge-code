#include<bits/stdc++.h>
using namespace std;
const int N=1005;
struct pic{
	int h,w,l,r,u,d,x,y;char c[N][N];
	inline void in(){
		int i,j;scanf("%d%d",&h,&w);l=u=1<<30;
		for(i=1;i<=h;++i)for(scanf("%s",c[i]+1),j=1;j<=w;++j)if(c[i][j]=='*')
			l=min(l,j),r=max(r,j),u=min(u,i),d=max(u,i),!x?x=i,y=j:0;
	}
}A,B,C;
inline void ck(const pic&A,const pic&B,const pic&C,int dx,int dy,int o){
	static bool b[N*2][N*2];int i,j,L,R,U,D,l=1<<30,u=1<<30,r=0,d=0;
	memset(b,0,sizeof b);
	U=min(A.u,B.u+dx);D=max(A.d,B.d+dx);L=min(A.l,B.l+dy);R=max(A.r,B.r+dy);
	auto opt=[&](const pic&A,int sx,int sy){
		for(i=A.u;i<=A.d;++i)for(j=A.l;j<=A.r;++j)
			b[sx+i][sy+j]^=A.c[i][j]=='*';
	};
	opt(A,1-U,1-L);opt(B,1-U+dx,1-L+dy);
	for(i=D-U+1;i;--i)for(j=R-L+1;j;--j)if(b[i][j])
		l=min(l,j),r=max(r,j),u=min(u,i),d=max(d,i);
	if(!C.r){if(r)return;}else{
		if(d-u+1!=C.d-C.u+1 || r-l+1!=C.r-C.l+1)return;
		for(i=1;i<=d-u+1;++i)for(j=1;j<=r-l+1;++j)if(b[u+i-1][l+j-1]!=(C.c[C.u+i-1][C.l+j-1]=='*'))return;
	}
	int X,Y;
	if(o==0)X=dx,Y=dy;else X=U+u-1-C.u,Y=L+l-1-C.l;
	if(o==2)X=-X,Y=-Y;
	printf("YES\n%d %d\n",Y,X);exit(0);
}
int main(){
//	freopen("kids.in","r",stdin);freopen("kids.out","w",stdout);
//	freopen("4847/2.in","r",stdin);
	A.in();B.in();C.in();ck(A,B,C,A.x-B.x,A.y-B.y,0);
	if(C.r)ck(A,C,B,A.x-C.x,A.y-C.y,1),ck(B,C,A,B.x-C.x,B.y-C.y,2);
	puts("NO");
}
// dasfdsfasdfads afsd a