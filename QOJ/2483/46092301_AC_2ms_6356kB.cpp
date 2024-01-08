#include<bits/stdc++.h>
using namespace std;
const int N=1e5;
int n,m,sx,sy,ex,ey,vx,vy,g,op;
int nx,ny,mx,my,mm;
double ans;
vector<int>v[N+10];
int Check(int x,int y){
	//cout<<"CHECK "<<x<<" "<<y<<"\n";
	long long t1=1ll*(x-sx)*abs(vy),t2=1ll*abs(y-sy)*vx;
	return t1==t2?0:(t1<t2?1:-1);
}
int Calc(int x,int y){
	if(v[x+1][y]>max(v[x][y],v[x+1][y+1])&&v[x][y+1]>max(v[x][y],v[x+1][y+1]))return min(v[x+1][y],v[x][y+1]);
	return max(v[x][y],v[x+1][y+1]);
}
int main(){
	scanf("%d%d%d%d%d%d",&n,&m,&sx,&sy,&ex,&ey);
	for(int i=1;i<=(n>>1);++i)v[i].resize((m>>1)+1);
	for(int i=1;i<=(m>>1);++i){
		for(int j=1;j<=(n>>1);++j)scanf("%d",&v[j][i]);
	}
	if(sx>ex)swap(sx,ex),swap(sy,ey);
	vx=ex-sx,vy=ey-sy;
	ans=sqrt(1.0*vx*vx+1.0*vy*vy);
	if(vy<0){
		vy=-vy;
		sy=m-sy,ey=m-ey;
		for(int i=1;i<=(n>>1);++i){
			for(int j=1;j<(m>>1)-j+1;++j)swap(v[i][j],v[i][(m>>1)-j+1]);
		}
	}
	if(!vx){
		if(sy>ey)swap(sy,ey);
		for(int i=sy;i<ey;i+=2)ans+=abs(v[sx+1>>1][i+1>>1]-v[sx+1>>1][i+3>>1]);
		printf("%.10lf",ans);
		return 0;
	}
	if(!vy){
		for(int i=sx;i<ex;i+=2)ans+=abs(v[i+1>>1][sy+1>>1]-v[i+3>>1][sy+1>>1]);
		printf("%.10lf",ans);
		return 0;
	}
	//cout<<"ANS="<<ans<<"\n";
	//cout<<"from "<<sx<<" "<<sy<<" to "<<ex<<" "<<ey<<"\n";
	nx=mx=sx-(sx&1);
	ny=sy-(sy&1),my=ny+2;
	op=0;
	while(mx<ex||my<ey){
		//cout<<"("<<nx<<","<<ny<<") ("<<mx<<","<<my<<")\n";
		if(nx==mx){
			if(op)ans+=abs(v[nx>>1][my>>1]-v[nx+2>>1][my>>1]);
			op=Check(nx+2,my);
			if(op>0)nx+=2,mx=nx;
			else if(op<0)mx+=2,(vy<0?my=ny:ny=my);
			else{
				nx+=2,mx=nx;
				if(mx>ex||my>ey)break;
				mm=Calc(mx>>1,my>>1);
				ans+=(mm<<1)-v[mx>>1][my>>1]-v[mx+2>>1][my+2>>1];
				ny=my,my+=2;
			}
		}else{
			if(op)ans+=abs(v[mx>>1][ny>>1]-v[mx>>1][ny+2>>1]);
			op=Check(mx,ny+2);
			if(op>0)nx+=2,my+=2;
			else if(op<0)ny+=2,my=ny;
			else{
				ny+=2,my=ny;
				if(mx>ex||my>ey)break;
				mm=Calc(mx>>1,my>>1);
				ans+=(mm<<1)-v[mx>>1][my>>1]-v[mx+2>>1][my+2>>1];
				nx=mx,ny=my,my+=2;
			}
		}
		//cout<<"ANS="<<ans<<"\n";
	}
	printf("%.12lf",ans);
	return 0;
}
/*
8 8 1 7 7 1
2 3 2 0
2 1 1 1
1 2 0 0
0 0 0 1
*/