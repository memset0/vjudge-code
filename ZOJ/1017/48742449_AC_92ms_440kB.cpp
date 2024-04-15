#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

int t, s, n;
bool area[110][110];

bool feasible(int x, int y, int length) {                                 // 进行深搜尝试
  if (x + length - 1 > 2 * s || y + 2 * length - 2 > 4 * s) return false; // 再放小三角形后，超出六边形范围
  if (y % 2 == 1) {                                                       // 放正三角
    for (int i = 0; i < length; i++) {
      for (int j = 0; j < 2 * i + 1; j++) {
        if (area[x + i][y + j] == false) return false;
      }
    }
  } else { // 放倒三角
    for (int i = 0; i < length; i++) {
      for (int j = 2 * i; j < 2 * length - 1; j++) {
        if (area[x + i][y + j] == false) return false;
      }
    }
  }
  return true;
}

void change(int x, int y, int length) { // 递归前改变状态，表示以访问过
  if (y % 2 == 1) {                     // 正三角
    for (int i = 0; i < length; i++) {
      for (int j = 0; j < 2 * i + 1; j++) {
        area[x + i][y + j] = false;
      }
    }
  } else { // 倒三角
    for (int i = 0; i < length; i++) {
      for (int j = 2 * i; j < 2 * length - 1; j++) {
        area[x + i][y + j] = false;
      }
    }
  }
}

void restore(int x, int y, int length) { // 递归后还原状态，以便进行下一个尝试
  if (y % 2 == 1) {                      // 正三角
    for (int i = 0; i < length; i++) {
      for (int j = 0; j < 2 * i + 1; j++) {
        area[x + i][y + j] = true;
      }
    }
  } else { // 倒三角
    for (int i = 0; i < length; i++) {
      for (int j = 2 * i; j < 2 * length - 1; j++) {
        area[x + i][y + j] = true;
      }
    }
  }
}

bool dfs(int x, int y, vector<int> &small) {
  if (x > 2 * s) return true;
  if (y > 4 * s) return dfs(x + 1, 1, small);

  if (area[x][y] == false) { // 当前位置试过
    int j;
    for (j = y + 1; j <= 4 * s; j++) { // 则从下一个没有试过的位置尝试
      if (area[x][j] == true) break;
    }
    return dfs(x, j, small);
  }
  for (int i = 0; i < n; i++) { // 深搜尝试
    if (feasible(x, y, small[i])) {
      change(x, y, small[i]);
      if (dfs(x, y + 1, small)) return true;
      restore(x, y, small[i]);
    } else
      break; // 三角形从小往大搜，当某个三角形不能放的时候，直接return
  }
  return false;
}

int main() {
  scanf("%d", &t); // cin >> t;
  while (t) {
    scanf("%d%d", &s, &n); // cin >> s >> n;
    vector<int> small;
    for (int i = 0; i < n; i++) {
      int t1;
      scanf("%d", &t1); // cin >> t1;
      small.push_back(t1);
    }
    bool success = false;
    ;
    sort(small.begin(), small.end());
    for (int i = 0; i < n; i++) { // 有小三角形边大于六边形，则去掉大的
      if (small[i] > s) {
        n = i;
        break;
      }
    }
    for (int i = 0; i < n; i++) { // 若小三角形边能整除六边形，则可以直接YES
      if (s % small[i] == 0) {
        success = true;
        break;
      } else {
        for (int j = 0; j < i; j++) {
          if (small[i] % small[j] == 0) {
            for (int k = i + 1; k < n; k++) small[k - 1] = small[k]; // 若小三角形的边能整除另一个三角形，去掉大的
            n--;
            i--;
            break;
          }
        }
      }
    }
    if (success) {
      printf("YES\n"); // cout << "YES" << endl;
      t--;
      continue;
    }
    memset(area, false, sizeof(area)); // 以/为x轴，最上的—为y轴,120度
    for (int i = 1; i <= s; i++) {     // 从正三角开始,上半部六边形
      for (int j = 1; j <= 2 * s + 2 * i - 1; j++) {
        area[i][j] = true;
      }
    }
    for (int i = s + 1; i <= 2 * s; i++) { // 从倒三角开始 ，下半部六边形
      for (int j = 2 * i - 2 * s; j <= 4 * s; j++) {
        area[i][j] = true;
      }
    }
    if (dfs(1, 1, small)) printf("YES\n"); // cout << "YES" << endl;
    else
      printf("NO\n"); // cout << "NO" << endl;
    t--;
  }
  return 0;
}
