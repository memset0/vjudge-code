#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

const int N=1e2+100;

int a,b,c;
int v[N][N];
bool flag=false;
string str[10]={"","FILL(1)","FILL(2)","DROP(1)","DROP(2)","POUR(1,2)","POUR(2,1)"};

struct node{
  int x,y,step;
  string s;
  node(int x,int y,int step,string s):x(x),y(y),step(step),s(s){}
};

inline void bfs(){
  queue <node> q;
  v[0][0]=1;
  q.push(node(0,0,0,"0"));
  while(!q.empty()){
    /* code */
    node tmp=q.front();
    q.pop();
    if(tmp.x==c||tmp.y==c){
      flag=1;
      cout<<tmp.step<<'\n';
      for(int i=1;i<tmp.s.length();++i)
        cout<<str[tmp.s[i]-'0']<<'\n';
      return;
    }
    if(tmp.x<a)
      if(!v[a][tmp.y])
        v[a][tmp.y]=1,q.push(node(a,tmp.y,tmp.step+1,tmp.s+"1"));
    if(tmp.y<b)
      if(!v[tmp.x][b])
        v[tmp.x][b]=1,q.push(node(tmp.x,b,tmp.step+1,tmp.s+"2"));
    if(tmp.x!=0)
      if(!v[0][tmp.y])
        v[0][tmp.y]=1,q.push(node(0,tmp.y,tmp.step+1,tmp.s+"3"));
    if(tmp.y!=0)
      if(!v[tmp.x][0])
        v[tmp.x][0]=1,q.push(node(tmp.x,0,tmp.step+1,tmp.s+"4"));
    if(tmp.x!=0&&tmp.y<b){
      int nx,ny;
      if(tmp.x<=b-tmp.y) nx=0,ny=tmp.x+tmp.y;
      else nx=tmp.x+tmp.y-b,ny=b;
      if(!v[nx][ny])
        v[nx][ny]=1,q.push(node(nx,ny,tmp.step+1,tmp.s+"5"));
    }
    if(tmp.y!=0&&tmp.x<a){
      int nx,ny;
      if(tmp.y<=a-tmp.x) nx=tmp.x+tmp.y,ny=0;
      else nx=a,ny=tmp.x+tmp.y-a;
      if(!v[nx][ny])
        v[nx][ny]=1,q.push(node(nx,ny,tmp.step+1,tmp.s+"6"));
    }
  }
}

int main(){
  cin>>a>>b>>c;
  bfs();
  if(!flag) puts("impossible");
  return 0;
}
