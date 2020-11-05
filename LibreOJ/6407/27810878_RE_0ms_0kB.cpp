#include<bits/stdc++.h>
using namespace std;
const int N=22;
const double G=9.80665;
namespace geometry{
  struct point{
    double x,y;
    inline bool operator<(const point &rhs)const{
      return x==rhs.x?y<rhs.y:x<rhs.x;
    }
  };
  struct line{
    point a,b;
  };
  inline int cross(const point &u,const point &a,const point &b){
    return (a.x-u.x)*(b.y-u.y)-(b.x-u.x)*(a.y-u.y);
  }
  inline bool crossSegmentify(const line &a,const line &b){
    return ((cross(a.a,a.b,b.a)<0)^(cross(a.a,a.b,b.b)<0))&&((cross(b.a,b.b,a.a)<0)^(cross(b.a,b.b,a.b)<0));
  }
  inline point intersect(const line &a,const line &b){
    double u=((a.a.y-b.a.y)*(b.a.x-b.b.x)-(a.a.x-b.a.x)*(b.a.y-b.b.y))/
      ((a.a.x-a.b.x)*(b.a.y-b.b.y)-(a.a.y-a.b.y)*(b.a.x-b.b.x));
    return {u*(a.a.x-a.b.x)+a.a.x,u*(a.a.y-a.b.y)+a.a.y};
  }
  inline double distance(const point &a,const point &b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
  }
}
using namespace geometry;
int n,m,sx,w,sy,dis[N][N],h[N][N],graph[N][N][N][N];
line l[N][N][4];
point p[N][N][2][2];
double v;
void BFS(){
  queue<pair<int,int>> q;
  dis[sx][sy]=1;
  q.push({sx,sy});
  while(q.size()){
    int ux,uy;
    tie(ux,uy)=q.front(),q.pop();
    for(int vx=1;vx<=n;vx++)
      for(int vy=1;vy<=m;vy++)
        if(graph[ux][uy][vx][vy]&&!dis[vx][vy]){
          dis[vx][vy]=dis[ux][uy]+1;
          q.push({vx,vy});
        }
  }
}
pair<double,double> calc(double d,double h){
  
}
bool verify(double vd,double vh,const vector<point> &tem){
  if(isnan(vd)||isnan(vh)||vd<=0||vh<=0||vd>=v||vh>=v){
    return false;
  }
  
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>m>>n>>w>>v>>sy>>sx;
  v=v*2/w;
  for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++){
      cin>>h[i][j];
      for(int x=0;x<2;x++)
        for(int y=0;y<2;y++){
          p[i][j][x][y].x=(i-1+x)<<1;
          p[i][j][x][y].y=(j-1+y)<<1;
        }
      l[i][j][0]={p[i][j][0][0],p[i][j][0][1]};
      l[i][j][1]={p[i][j][0][1],p[i][j][1][1]};
      l[i][j][2]={p[i][j][1][1],p[i][j][1][0]};
      l[i][j][3]={p[i][j][1][0],p[i][j][0][0]};
    }
  for(int ux=1;ux<=n;ux++)
    for(int uy=1;uy<=m;uy++){
      for(int vx=1;vx<=n;vx++)
        for(int vy=1;vy<=m;vy++)
          if(ux!=vx||uy!=vy){
            vector<point> lim,tem;
            line cur{{p[ux][uy][0][0].x+1,p[ux][uy][0][0].y+1},
              {p[vx][vy][0][0].x+1,p[vx][vy][0][0].y+1}};
            for(int i=1;i<=n;i++)
              for(int j=1;j<=m;j++)
                for(int k=0;k<4;k++)
                  if(crossSegmentify(l[i][j][k],cur)){
                    point ist=intersect(cur,l[i][j][k]);
                    lim.push_back({distance(cur.a,ist),(double)h[i][j]});
                  }
            auto v=calc(distance(cur.a,cur.b),h[vx][vy]-h[ux][uy]);
            graph[ux][uy][vx][vy]=verify(v.first,v.second,lim);
          }
    }
  BFS();
  for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++){
      if(dis[i][j]){
        cout<<dis[i][j]-1;
      }else{
        cout<<"X";
      }
      cout<<" \n"[j==m];
    }
}