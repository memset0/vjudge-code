#include<bits/stdc++.h>
using namespace std;
const int N=1e2+5;
int tag;
void to(int a,int b){printf("%d to %d\n",a,b);}
void solve(int l,int r){
  if(r-l+1<=14){
    int len=(r-l+1)>>1;
    tag=len;
    if(len==4){
      to(r-2,l-2),to(l+2,r-2),to(l-1,l+2),to(r-1,l-1);
    }else if(len==5){
      to(r-2,l-2),to(l+2,r-2),to(l+5,l+2),to(l-1,l+5),to(r-1,l-1);
    }else if(len==6){
      to(l+9,l-2),to(l+6,l+9),to(l+1,l+6),to(l+5,l+1),to(l-1,l+5),to(l+10,l-1);
    }else if(len==7){
      to(l+7,l-2),to(l+4,l+7),to(l+11,l+4),to(l+2,l+11),to(l+8,l+2),to(l-1,l+8),to(l+12,l-1);
    }
  }else{
    to(r-2,l-2),to(l+2,r-2);
    solve(l+4,r-4);
  }
}
int main(){
  int n;scanf("%d",&n);
  if(n==3)return to(2,-1),to(5,2),to(3,-3),0;
  solve(1,n*2);
  int cur=-1+(n+tag),cnt=(n-tag)/4,l=0,r=cur+4;
  while(cnt--){
    to(l,cur),cur=l,l+=4;
    to(r,cur),cur=r,r+=4;
  }
}