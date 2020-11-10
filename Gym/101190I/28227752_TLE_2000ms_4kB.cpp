#include<bits/stdc++.h>
int m;
enum ways{left,right};
inline int go(int st,int dir,int pa){
  static std::string rsp;
  std::cout<<st<<' '<<(dir==left?"left":"right")<<' '<<pa<<std::endl<<std::flush;
  std::cin>>rsp;
  if(rsp=="treasure")exit(0);
  if(rsp=="left")return left;
  if(rsp=="right")return right;
  return -1;
}
int dfs(){
  std::vector<int> opt(m),dep(m);
  for(int tem,i=0;i<m;i++){
    tem=opt[i]=go(1,left,1);
    if(opt[i]==left){
      tem=go(0,right,0),++dep[i];
      while(tem==left)tem=go(0,left,0),++dep[i];
      for(int t=1;t<dep[i];t++)tem=go(0,left,0);
    }else if(opt[i]==right){
      int cnt=0;
      while(tem==right)tem=go(0,right,0),++cnt;
      while(tem==left)tem=go(0,left,0),++dep[i];
      for(int t=1;t<cnt+dep[i];t++)tem=go(0,tem,0);
    }else{
      dep[i]=dfs()-1;
    }
  }
  int fallback=-1;
  for(int i=0;i<m;i++)
    if(fallback==-1||dep[i]>dep[fallback]){
      fallback=i;
    }
  if(~fallback){
    int tem=go((fallback+1)%m,right,(fallback+1)%m);
    while(tem!=left)tem=go(0,right,0);
    for(int i=2;i<dep[fallback];i++)go(0,left,0);
  }
  return ~fallback?dep[fallback]:114514;
}
int main(){
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);
  std::cin>>m;
  dfs();
}