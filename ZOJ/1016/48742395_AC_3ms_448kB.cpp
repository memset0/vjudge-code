#include <iostream>
#include <string>
using namespace std;
int main() {
  int icase, arr[21];
  cin >> icase;
  while (icase--) {
    int size, num, temp = 0, temp1, arrt = 0, k = 0;
    string str;
    cin >> size;
    for (int j = 0; j < size; j++) {
      cin >> num;
      temp1 = num;
      num -= temp;
      for (int i = 0; i < num; i++) {
        str += '(';
      }
      str += ')';
      arrt = num + arrt + 1;
      arr[k++] = arrt - 1;
      temp = temp1;
    }
    for (int i = 0; i < size; i++) {
      int j = 0;
      str[arr[i]] = '@';
      for (j = arr[i] - 1; j > 0; j--) {
        if (str[j] == '(') {
          str[j] = '@';
          break;
        }
      }
      cout << ((arr[i] - j) / 2) + 1;
      if (i != size - 1) cout << ' ';
    }
    cout << endl;
  }
  return 0;
}