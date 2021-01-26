#include<bits/stdc++.h>
using namespace std;
int lstx,lsty;
void play(int x,int y){
  cout<<x<<" "<<y<<endl<<flush;
  cin>>lstx>>lsty;
}
int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>lstx>>lsty;
  play(5,5);
  play(6,4);
  play(8,8);
  if(lstx==12){
    play(13,13);
  }else{
    play(12,12);
  }
  if(lstx!=7||lsty!=3){
    play(7,5);
    play(6,6);
    play(6,5);
    play(6,3);
    play(6,2);
  }else{

  }
}