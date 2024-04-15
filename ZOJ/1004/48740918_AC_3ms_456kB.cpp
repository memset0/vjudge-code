#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

// 封装在类中
class StackAnagram {
public:
  // Constructor
  StackAnagram(string src, string target) : src(src), target(target) {}
  // Destructor
  ~StackAnagram() {}
  // main中调用的函数
  void anagram();

private:
  stack<char> s;
  char *path;           //'i'、'o'序列
  vector<char *> paths; // 所有的进栈、出栈方式
  string src, target;

  void dfs(int i, int j);
};

void StackAnagram::anagram() {
  int n = src.size();
  path = new char[n];
  dfs(0, 0);
  // 由于dfs中先递归进栈情况后递归出栈，故 'i' 排在 'o' 前，与字典序相符，不需排序
  printf("[\n");
  for (char *p : paths) {
    for (int i = 0; i < 2 * n; i++) {
      cout << p[i] << " ";
    }
    cout << endl;
    free(p); // 释放内存
  }
  printf("]\n");
  free(path);
}

void StackAnagram::dfs(int i, int j) {
  int n = src.size();
  if (i == n && j == n) {                // 处理完毕
    char *currentPath = new char[2 * n]; // 复制到另一数组中，在anagram函数中输出后释放free
    memcpy(currentPath, path, 2 * n);
    paths.push_back(currentPath);
    return;
  }
  if (i < n) { // 可以进栈
    s.push(src[i]);
    path[i + j] = 'i';
    dfs(i + 1, j); // i增长
    s.pop();       // 还原
  }
  if (!s.empty() && s.top() == target[j]) { // 可以出栈(i >= j因为i等于进栈次数，j等于出栈次数，进栈次数大于等于出栈次数，这里j一定小于n)
    char tmp = s.top();
    s.pop(); // 出栈
    path[i + j] = 'o';
    dfs(i, j + 1); // j增长
    s.push(tmp);   // 还原
  }
}

int main() {
  string src, target;
  while (cin >> src) {
    cin >> target;
    StackAnagram stackAnagram(src, target);
    stackAnagram.anagram();
  }
  return 0;
}