#include <iostream>
using namespace std;

#define MAX 1001

class Poly {
public:
  int de;             // degree
  bool mem[MAX << 1]; // member
};

void multpoly(Poly a, Poly b, Poly &res) {
  int i, j;
  res.de = a.de + b.de;
  for (i = 0; i <= res.de; i++) res.mem[i] = 0;
  for (i = a.de; i >= 0; i--)
    for (j = b.de; j >= 0; j--) res.mem[i + j] = (res.mem[i + j] + a.mem[i] * b.mem[j]) % 2;
}

void modpoly(Poly &a, Poly h) {
  int i, flag = 1;
  while (flag) {
    for (i = a.de; i >= 0 && (!a.mem[i]); i--)
      ;
    if (i < h.de) {
      a.de = i;
      flag = 0;
    } else {
      for (int j = h.de; j >= 0; i--, j--) a.mem[i] = (a.mem[i] + h.mem[j]) % 2;
    }
  }
}

void readpoly(Poly &a) {
  int i, mid;
  cin >> mid;
  a.de = mid - 1;
  for (i = a.de; i >= 0; i--) {
    cin >> a.mem[i];
  }
}

void solve() {
  Poly f, g, h, temp;
  readpoly(f);
  readpoly(g);
  readpoly(h);
  multpoly(f, g, temp);
  modpoly(temp, h);
  cout << temp.de + 1;
  for (int j = temp.de; j >= 0; j--) {
    cout << ' ' << temp.mem[j];
  }
  cout << endl;
}

int main() {
  int t;
  cin >> t;
  while (t--) solve();
  return 0;
}