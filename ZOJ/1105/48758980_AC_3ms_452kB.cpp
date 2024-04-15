#include <algorithm>
#include <cstring>
#include <iostream>
#include <list>
#include <math.h>
#include <queue>
#include <set>
#include <vector>
using namespace std;

int main() {
  double x0, y0;
  while (cin >> x0 >> y0) {
    string x1;
    double y1, x2, y2;
    double sum = 0;
    while (cin >> x1 && x1 != "java") {
      cin >> y1 >> x2 >> y2;
      double dx = x2 - stod(x1);
      double dy = y2 - y1;
      sum += sqrt(dy * dy + dx * dx);
      //			cout << "sum:" << sum << endl;
    }
    sum = sum / 1000 * 2 / 20;
    //		cout << sum<<endl;;
    sum *= 60;
    //		cout << sum<<endl;
    printf("%d:", (int)(sum + 0.5) / 60);
    int minute = int(sum + 0.5) % 60;
    if (minute < 10) {
      cout << "0" << minute << endl;
    } else {
      cout << minute << endl;
    }
  }
}
