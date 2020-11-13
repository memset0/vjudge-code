#include<bits/stdc++.h>
using namespace std;
const int N=2e3+10;
const double inf=2e4,eps=1e-15;
namespace geometry{
  const double mathPI=acos(-1);
  template<class T> inline T abs(const T &x){return x<0?-x:x;}
  struct point{
    double x,y;
    inline bool operator<(const point &rhs)const{
      return (abs(x-rhs.x)<=eps)?(y-rhs.y<-eps):(x-rhs.x<-eps);
    }
    inline bool operator==(const point &rhs)const{
      return abs(x-rhs.x)<=eps&&abs(y-rhs.y)<eps;
    }
  };
  struct line{
    point a,b;
    inline bool operator<(const line &rhs)const{
      return a==rhs.a?b<rhs.b:a<rhs.a;
    }
  };
  inline double squaredDistance(const point &a,const point &b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
  }
  inline double distance(const point &a,const point &b){
    return sqrt(squaredDistance(a,b));
  }
  inline double cross(const point &u,const point &a,const point &b){
    return (a.x-u.x)*(b.y-u.y)-(b.x-u.x)*(a.y-u.y);
  }
  inline point intersect(const line &a,const line &b){
    double u=((a.a.y-b.a.y)*(b.a.x-b.b.x)-(a.a.x-b.a.x)*(b.a.y-b.b.y))/
      ((a.a.x-a.b.x)*(b.a.y-b.b.y)-(a.a.y-a.b.y)*(b.a.x-b.b.x));
    point p={u*(a.a.x-a.b.x)+a.a.x,u*(a.a.y-a.b.y)+a.a.y};
    return p;
  }
  inline bool checkSegmentCrossed(const line &a,const line &b){
    return ((cross(a.a,a.b,b.a)<eps)^(cross(a.a,a.b,b.b)<eps))&&((cross(b.a,b.b,a.a)<eps)^(cross(b.a,b.b,a.b)<eps));
  }
  inline bool insideConvex(const point &x,const vector<point> &a){
    bool target=cross(a[0],a[1],x)<eps;
    for(int i=1;i<a.size();i++)
      if(target!=(cross(a[i],a[(i+1)%a.size()],x)<eps))
        return false;
    return true;
  }
  inline bool insidePolygon(const point &x,const vector<point> &a){
    vector<double> deg(a.size());
    for(int i=0;i<a.size();i++){
      deg[i]=atan2(a[i].y-x.y,a[i].x-x.x);
    }
    double sum=0;
    for(int i=0;i<a.size();i++){
      double cur=deg[i]-deg[(i+1)%a.size()];
      if(cur<=-mathPI)cur+=mathPI;
      if(cur>=mathPI)cur-=mathPI;
      sum+=cur;
    }
    return abs(sum)>.5*mathPI;
  }
  deque<point> halfPlane(const vector<line> &source){
    vector<pair<line,double>> plane(source.size());
    for(int i=0;i<plane.size();i++){
      plane[i]={source[i],atan2(source[i].b.y-source[i].a.y,source[i].b.x-source[i].a.x)};
    }
    sort(plane.begin(),plane.end(),[&](const pair<line,double> &a,const pair<line,double> &b){
      return abs(a.second-b.second)>eps?a.second<b.second:cross(a.first.a,b.first.a,b.first.b)>eps;
    });
    deque<point> q;
    deque<line> ql;
    for(int i=0;i<plane.size();i++){
      if(i&&abs(plane[i].second-plane[i-1].second)<eps)continue;
      line cur=plane[i].first;
      while(q.size()&&cross(cur.a,cur.b,q.back())<-eps)q.pop_back(),ql.pop_back();
      while(q.size()&&cross(cur.a,cur.b,q.front())<-eps)q.pop_front(),ql.pop_front();
      if(ql.size())q.push_back(intersect(ql.back(),cur));
      ql.push_back(cur);
    }
    while(q.size()>1&&cross(ql.front().a,ql.front().b,q.back())<eps)q.pop_back(),ql.pop_back();
    return q;
  }
}
using namespace geometry;
int n;
vector<point> a;
double ans;
set<point> voronoiNode;
set<line> voronoiEdge;
void satisifyNode(const point &x){
  if(isnan(x.x)||isnan(x.y))return;
  double cur=numeric_limits<double>::infinity();
  for(int i=0;i<n;i++){
    cur=min(cur,squaredDistance(x,a[i]));
  }
  // cerr<<"check "<<x.x<<" "<<x.y<<" "<<cur<<endl;
  ans=max(ans,cur);
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  // cerr<<fixed<<setprecision(4);
  cin>>n;
  a.resize(n);
  for(int i=0;i<n;i++){
    cin>>a[i].x>>a[i].y;
  }
  for(int i=0;i<n;i++){
    satisifyNode({(a[i].x+a[(i+1)%n].x)/2,(a[i].y+a[(i+1)%n].y)/2});
    // cerr<<"Segment "<<a[i].x<<" "<<a[i].y<<" "<<a[(i+1)%n].x<<" "<<a[(i+1)%n].y<<endl;
  }
  // cerr<<endl;
  for(int i=0;i<n;i++){
    vector<line> plane={
      {{inf+5,inf+5},{-inf,inf}},
      {{-inf,inf},{-inf,-inf}},
      {{-inf,-inf},{inf,-inf}},
      {{inf,-inf},{inf+5,inf+5}},
    };
    // cerr<<"Circle "<<a[i].x<<" "<<a[i].y<<" 5"<<endl;
    for(int j=0;j<n;j++)if(i!=j){
      point mid{(a[i].x+a[j].x)/2,(a[i].y+a[j].y)/2};
      point delta{a[i].x-mid.x,a[i].y-mid.y};
      plane.push_back({{mid.x-delta.y,mid.y+delta.x},{mid.x+delta.y,mid.y-delta.x}});
    }
    auto convex=halfPlane(plane);
    for(int i=0;i<convex.size();i++){
      // cerr<<convex[i].x<<" "<<convex[i].y<<endl;
      voronoiNode.insert(convex[i]);
      line e={convex[i],convex[(i+1)%convex.size()]};
      if(e.a.x<e.b.x)swap(e.a,e.b);
      voronoiEdge.insert(e);
    }
    // cerr<<endl;
  }
  for(const point &x:voronoiNode){
    // cerr<<x.x<<" "<<x.y<<" "<<insidePolygon(x,a)<<endl;
    if(insidePolygon(x,a)){
      satisifyNode(x);
    }
  }
  // cerr<<endl;
  for(const line &e:voronoiEdge){
    for(int i=0;i<a.size();i++){
      line target{a[i],a[(i+1)%a.size()]};
      if(checkSegmentCrossed(e,target)){
        satisifyNode(intersect(e,target));
      }
    }
  }
  cout<<fixed<<setprecision(12)<<sqrt(ans)<<endl;
}