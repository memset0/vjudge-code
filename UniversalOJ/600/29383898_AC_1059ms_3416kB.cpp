#include<bits/stdc++.h>
using namespace std;
int T,n,a,b,c,d,e,t,ans,pre;
vector<int> res;
inline void push(int x){ans=max(ans,max(pre+x,x)),pre=max(pre+x,x),res.push_back(x);}
inline void push(const vector<int> &v,int c){while(c--)for(int x:v)push(x);}
int main(){
#ifdef memset0
	freopen("C.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  for(cin>>T;T;--T){
    res.clear(),pre=0,ans=-1919810;
    cin>>a>>b>>c>>d>>e,n=a+b+c+d+e;
    if(c)push({0},c),c=0; //0
    if(b&&d)t=min(b,d),push({1,-1},t),b-=t,d-=t; //1,-1
    if(a&&e)t=min(a,e),push({2,-2},t),a-=t,e-=t; //2,-2
    if(b>1&&e)t=min(b>>1,e),push({2,-1,-1},t),b-=t<<1,e-=t; //-1,2
    if(ans<=1&&!e&&d&&d<=a+1){ //只有1,-2，无0,2,-1 
      push(1),d--;
      while(d)push(-2),a--,push(1),d--;
      while(a)push(-2),a--;
      goto out;
    }
    if(a&&d>1)t=min(a,d>>1),push({1,1,-2},t),a-=t,d-=t<<1; //-2,1
    if(!e&&d==1){ //正数只有一个1，剩下的都是负数 
      push({-2},a),push(1);
    }else if(!a&&b==1){ //负数只有一个-1，剩下的都是正数
      if(e)push(2),e--;
      push(-1),push({2},e);
    }else{ //乱放就行了 
      if(a||b)assert(!d&&!e);
      if(d||e)assert(!b&&!b);
      push({-2},a),push({-1},b),push({1},d),push({2},e);
    }
  out:cout<<ans<<'\n';for(int x:res)cout<<x<<' ';cout<<'\n';
  }
}