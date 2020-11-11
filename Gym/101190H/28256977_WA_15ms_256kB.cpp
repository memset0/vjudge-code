#include <iostream>
#include <vector>
std::string s;
int x;
int f[65537];
std::vector<std::pair<int, int>> ans;
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  while (true) {
    std::cin >> s;
    std::cin >> s >> x;
    int l = -32768, r = 32767;
    if (s == ">=") {
      l = std::max(l, x);
    } else {
      r = std::min(r, x);
    }
    if (!(std::cin >> s)) {
      if (l <= r) {
        ++f[l + 32768];
        --f[r + 32769];
      }
      break;
    }
    if (s == "||") {
      if (l <= r) {
        ++f[l + 32768];
        --f[r + 32769];
      }
      continue;
    }
    std::cin >> s;
    std::cin >> s >> x;
    if (s == ">=") {
      l = std::max(l, x);
    } else {
      r = std::min(r, x);
    }
    if (l <= r) {
      ++f[l + 32768];
      --f[r + 32769];
    }
    if (!(std::cin >> s))
      break;
  }
  for (int i = 1; i <= 65536; ++i)
    f[i] += f[i - 1];
  for (int i = 0; i < 65536; ++i) {
    if (f[i] == 0)
      continue;
    int j = i;
    while (f[j + 1] > 0)
      ++j;
    ans.emplace_back(i - 32768, j - 32768);
    i = j;
  }
  if (ans.empty()) {
    std::cout << "false";
  } else {
    for (int i = 0; i < int(ans.size()); ++i) {
      int l = ans[i].first, r = ans[i].second;
      if (l == -32768 && r == 32767) {
        std::cout << "true";
      } else if (l == -32768) {
        std::cout << "x <= " << r;
      } else if (r == 32767) {
        std::cout << "x >= " << l;
      } else {
        std::cout << "x >= " << l << " && x <= " << r;
      }
      if (i != int(ans.size()) - 1)
        std::cout << " ||\n";
    }
  }
  return 0;
}
