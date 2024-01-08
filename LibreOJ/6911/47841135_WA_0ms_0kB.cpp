#include <bits/stdc++.h>
using namespace std;
int main() {
  char agic[20] = "You are right, but ";
  string s;
  cin >> s;
  for (int i = 0; i < 19; i++)
    if (s[i] != agic[i]) {
      cout << "Human" << endl;
      return 0;
    }
  cout << "AI" << endl;
}