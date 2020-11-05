#include<bits/stdc++.h>
using namespace std;
const int N=2e3+10;
const double eps=1e-10;
namespace geometry{
  struct node{
    double x,y;
    inline bool operator<(const node &rhs)const{
      return (abs(x-rhs.x)<=eps)?(y-rhs.y<-eps):(x-rhs.x<-eps);
    }
    inline bool operator==(const node &rhs)const{
      return abs(x-rhs.x)<=eps&&abs(y-rhs.y)<=eps;
    }
  };
  struct line{
    node a,b;
    inline bool operator<(const line &rhs)const{
      return a==rhs.a?b<rhs.b:a<rhs.a;
    }
  };
  inline double cross(const node &u,const node &a,const node &b){
    return (a.x-u.x)*(b.y-u.y)-(b.x-u.x)*(a.y-u.y);
  }
  inline double squaredDistance(const node &a,const node &b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
  }
  inline double distance(const node &a,const node &b){
    return sqrt(squaredDistance(a,b));
  }
  inline node intersection(const line &a,const line &b){
    double u=((a.a.y-b.a.y)*(b.a.x-b.b.x)-(a.a.x-b.a.x)*(b.a.y-b.b.y))/
      ((a.a.x-a.b.x)*(b.a.y-b.b.y)-(a.a.y-a.b.y)*(b.a.x-b.b.x));
    node p={u*(a.a.x-a.b.x)+a.a.x,u*(a.a.y-a.b.y)+a.a.y};
    return p;
  }
  inline pair<bool,node> intersectionLimited(const line &a,const line &b){
    node res=intersection(a,b);
    if(isnan(res.x)||isnan(res.y))return {false,res};
    if((res.x<a.a.x&&res.x<a.b.x)||(res.x>a.a.x&&res.x>a.b.x))return {false,res};
    if((res.x<b.a.x&&res.x<b.b.x)||(res.x>b.a.x&&res.x>b.b.x))return {false,res};
    if((res.y<a.a.y&&res.y<a.b.y)||(res.y>a.a.y&&res.y>a.b.y))return {false,res};
    if((res.y<b.a.y&&res.y<b.b.y)||(res.y>b.a.y&&res.y>b.b.y))return {false,res};
    return {true,res};
  }
  inline bool insideConvex(const node &x,const vector<node> &a){
    bool target=cross(a[0],a[1],x)<eps;
    for(int i=1;i<a.size();i++)
      if(target!=cross(a[i],a[(i+1)%a.size()],x)<eps){
        return false;
      }
    return true;
  }
  inline bool insidePolygon(const node &x,const vector<node> &a){
    vector<double> deg(a.size());
    for(int i=0;i<a.size();i++){
      deg[i]=atan2(a[i].y-x.y,a[i].x-x.x);
    }
    double sum=0;
    for(int i=0;i<a.size();i++){
      double cur=deg[i]-deg[(i+1)%a.size()];
      if(cur<-M_PI)cur+=M_PI;
      if(cur>M_PI)cur-=M_PI;
      sum+=cur;
    }
    return abs(sum/M_PI)>eps;
  }
  deque<node> halfPlane(const vector<line> &plane){
    // for(const line &a:plane)cerr<<"Segment "<<a.a.x<<" "<<a.a.y<<" "<<a.b.x<<" "<<a.b.y<<endl;
    deque<node> q;
    deque<line> ql;
    for(const line &u:plane){
      while(q.size()&&cross(u.a,u.b,q.back())<eps){
        q.pop_back(),ql.pop_back();
      }
      while(q.size()&&cross(u.a,u.b,q.front())<eps){
        q.pop_front(),ql.pop_front();
      }
      if(ql.size()){
        q.push_back(intersection(ql.back(),u));
      }
      ql.push_back(u);
    }
    while(q.size()&&cross(ql.front().a,ql.front().b,q.back())<eps){
      q.pop_back(),ql.pop_back();
    }
    return q;
  }
}
using namespace geometry;
int n;
vector<node> a;
double ans;
set<node> voronoiNode;
set<line> voronoiEdge;
void satisifyNode(const node &x){
  double cur=numeric_limits<float>::infinity();
  for(int i=1;i<=n;i++){
    cur=min(cur,squaredDistance(x,a[i]));
  }
  ans=max(ans,cur);
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
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
    vector<pair<node,double>> rest;
    for(int j=0;j<n;j++)if(i!=j){
      rest.push_back({a[j],atan2(a[j].y-a[i].y,a[j].x-a[i].x)});
    }
    sort(rest.begin(),rest.end(),[&](const pair<node,double> &x,const pair<node,double> &y){
      return x.second<y.second;
    });
    vector<line> plane;
    // cerr<<"Circle "<<a[i].x<<" "<<a[i].y<<" 5"<<endl;
    for(const auto &it:rest){
      node mid{(a[i].x+it.first.x)/2,(a[i].y+it.first.y)/2};
      node delta{a[i].x-mid.x,a[i].y-mid.y};
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
  }
  for(const node &x:voronoiNode){
    // cerr<<x.x<<" "<<x.y<<" "<<insidePolygon(x,a)<<endl;
    if(insidePolygon(x,a)){
      satisifyNode(x);
    }
  }
  for(const line &e:voronoiEdge){
    for(int i=0;i<a.size();i++){
      auto status=intersectionLimited(line{a[i],a[(i+1)%a.size()]},e);
      if(status.first){
        // cerr<<status.second.x<<" "<<status.second.y<<endl;
        satisifyNode(status.second);
      }
    }
  }
  cout<<fixed<<setprecision(12)<<sqrt(ans)<<endl;
}