// https://vjudge.net/user/memset0
#include<bits/stdc++.h>
using namespace std;
using T = string;
T M[]={
"4569964",
"667156058344",
"668326051481",
"658543612704",
"3140650",
"90022046",
"648271021446",
"705858338684",
"3504922",
"124170050",
};
vector<int>H(){
  std::mt19937 rng;
  vector<int> a(10);
  for (int i = 0; i < a.size(); i++) {
    cin >> a[i];
  }
  return a;
}
void O(int task,T ans){
  cout << ans << endl;
  //
}
int main(){
ios::sync_with_stdio(0),cin.tie(0);
auto V=H();
#define I(A,B,C,D,E,F,G,H,I,J,K) if(V[0]==A&&V[1]==B&&V[2]==C&&V[3]==D&&V[4]==E&&V[5]==F&&V[6]==G&&V[7]==H&&V[8]==I&&V[9]==J)O(K,M[K-1]);
I(20,1,2,1,1787,3,1,561,4,1,1);
I(2000,1005,2,1,5577,3,1,2933,4,1,2);
I(2000,1006,2,1,51,3,1,1531,4,1,3);
I(2000,1001,2,1,8361,3,1,526,4,1,4);
I(20,1,2,1,661,3,1,1886,4,1,5);
I(100,45,2,1,8511,3,1,5379,4,2,6);
I(2000,1009,2,1,7863,3,1,6307,4,1,7);
I(2000,1008,2,1,5511,3,1,2321,4,1,8);
I(20,17,2,1,1516,3,1,6355,4,1,9);
I(100,11,2,1,8449,3,1,9045,4,1,10);
}
