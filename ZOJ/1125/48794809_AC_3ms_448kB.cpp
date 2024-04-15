#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;

int main() {
#ifdef memset0
  freopen("temp.in", "r", stdin);
#endif

  char in[16], out[16];
  int i, j, n, exp, man, zero;
  double num;

  cout << "Program 6 by team X" << endl;
  while (scanf("%s", in) != EOF) {
    man = 0;
    exp = 0;
    zero = 1;
    if (in[0] == '1') out[0] = '-';
    else
      out[0] = ' ';
    for (i = 1; i < 8; i++) {
      exp = exp << 1;       // 注意，移位的时候后面不能再跟算式，否则出错
      exp += (in[i] - '0'); // 处理的是字符，要用ASCii码比较
      if (in[i] != '0') zero = 0;
    }
    exp = exp - 63;
    for (i = 8; i < 16; i++) {
      man = man << 1;
      man += (in[i] - '0');
      if (in[i] != '0') zero = 0;
    }
    num = (1 + double(man) / 256) * pow(2.0, exp);
    // fprintf(stderr, "num = %.10lf\n", num);
    exp = 0;
    if (num > 10 + eps) {
      while (num > 10 - eps) {
        num /= 10;
        exp++;
      }
    } else if (num < 1 - eps) {
      while (num < 1 + eps) {
        num *= 10;
        exp--;
      }
    }
    if (zero) cout << " 0.000000e+000";
    else {
      cout << out[0];
      printf("%.6fe", num);
      if (exp >= 0) {
        cout << "+0";
        if (exp < 10) cout << '0';
        cout << exp;
      } else {
        cout << "-0";
        if (exp > -10) cout << '0';
        cout << -exp;
      }
    }
    cout << endl;
  }
  cout << "End of program 6 by team X";
  return 0;
}