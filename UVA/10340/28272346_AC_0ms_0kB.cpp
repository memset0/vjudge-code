#include<bits/stdc++.h>
using namespace std;

string s, t;

int main() {
  while(cin >> s >> t){
    int p = 0;
    int fl = 1;
    for (int i=0; i < s.size(); i++) {
      p = t.find(s[i]);
      if (p != -1) t.erase(0, p+1);
      else {
        fl = 0;
        cout << "No\n";
        break;
      }
    }
    if(fl) printf("Yes\n");    
  }
  return 0;
}