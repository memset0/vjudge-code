#ifdef DBG1
  #define _GLIBCXX_DEBUG
#endif
 
#include <cstdio>
#include <cassert>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
 
#ifdef DBG1
    #define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
    #define eprintf(...)
#endif
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
typedef pair <int, int> pii;
 
#define TASKNAME "cactus"
 
struct Operation {
private:
  char ch;
  int i1, i2, i3;
public:
  Operation(char ch, int i1, int i2, int i3) : ch(ch), i1(i1), i2(i2), i3(i3) {}
 
  static Operation recolor(int v, int c1, int c2);
  static Operation connect(int v, int c1, int c2);
  static Operation join(int v, int u);
 
  void print() const {
    if (ch == 'j') {
      printf("%c %d %d\n", ch, i1 + 1, i2 + 1);
    } else {
      printf("%c %d %d %d\n", ch, i1 + 1, i2 + 1, i3 + 1);
    }
  }
};
 
Operation Operation::recolor(int v, int c1, int c2) {
  return Operation('r', v, c1, c2);
}
 
Operation Operation::connect(int v, int c1, int c2) {
  return Operation('c', v, c1, c2);
}
 
Operation Operation::join(int v, int u) {
  return Operation('j', v, u, -1);
}
 
void dfs(int s, int par,
         const vector <vector<int>> & ed,
         vector <int> & st,
         vector <int> & used,
         vector <vector<vector<int>>> & cycles) {
  if (used[s] == 2) {
    return;
  }
  if (used[s] == 1) {
    vector <int> cycle;
    int i = int(st.size()) - 1;
    while (i >= 0 && st[i] != s) {
      cycle.push_back(st[i]);
      --i;
    }
    assert(i >= 0);
    cycle.push_back(s);
    reverse(cycle.begin(), cycle.end());
    eprintf("cycle [");
    for (int v : cycle) {
      eprintf("%d ", v);
    }
    eprintf("]\n");
    cycles[s].emplace_back(std::move(cycle));
    return;
  }
 
  st.push_back(s);
  used[s] = 1;
  for (int v : ed[s]) {
    if (v == par) { continue; }
    dfs(v, s, ed, st, used, cycles);
  }
  st.pop_back();
  used[s] = 2;
}
 
void buildSubtree(int s,
                  const vector <vector<int>> & ed,
                  const vector <vector<vector<int>>> & cycles,
                  const vector <int> & perm,
                  vector <int> & used,
                  vector <Operation> & operations);
 
void buildCycle(const vector <int> & cycle, 
                const vector <vector<int>> & ed, 
                const vector <vector<vector<int>>> & cycles, 
                const vector <int> & perm, 
                vector <int> & used, 
                vector <Operation> & operations) {
  for (int v : cycle) {
    used[v] = 1;
  }
 
  vector <vector<int>> newPerm(2, perm);
  for (int i = 0; i < 2; ++i) {
    swap(newPerm[i][0], newPerm[i][i + 1]);
  }
 
  for (int i = 1; i < int(cycle.size()); ++i) {
    int cur = cycle[i];
    buildSubtree(cur, ed, cycles, newPerm[i % 2], used, operations);
  }
  operations.push_back(Operation::join(cycle[0], cycle[1]));
  operations.push_back(Operation::connect(cycle[0], perm[0], newPerm[1][0]));
  for (int i = 2; i < int(cycle.size()); ++i) {
    int prev = cycle[i - 1];
    int cur = cycle[i];
    operations.push_back(Operation::join(prev, cur));
    operations.push_back(Operation::connect(prev, perm[1], perm[2]));
    operations.push_back(Operation::recolor(prev, newPerm[(i - 1) % 2][0], perm[3]));
  }
  operations.push_back(Operation::connect(cycle[0], perm[0], newPerm[(int(cycle.size()) - 1) % 2][0]));
  operations.push_back(Operation::recolor(cycle.back(), newPerm[(int(cycle.size()) - 1) % 2][0], perm[3]));
}
 
void buildSubtree(int s,
                  const vector <vector<int>> & ed,
                  const vector <vector<vector<int>>> & cycles,
                  const vector <int> & perm,
                  vector <int> & used,
                  vector <Operation> & operations) {
  eprintf("%s %d color %d\n", __func__, s, perm[0]);
  used[s] = true;
  if (perm[0] != 0) {
    operations.push_back(Operation::recolor(s, 0, perm[0]));
  }
  for (const auto & cycle : cycles[s]) {
    buildCycle(cycle, ed, cycles, perm, used, operations);
  }
  vector <int> newPerm = perm;
  swap(newPerm[0], newPerm[1]);
  for (int v : ed[s]) {
    if (!used[v]) {
      buildSubtree(v, ed, cycles, newPerm, used, operations);
      operations.push_back(Operation::join(s, v));
      operations.push_back(Operation::connect(s, perm[0], newPerm[0]));
      operations.push_back(Operation::recolor(v, newPerm[0], perm[3]));
    }
  }
}
 
int main() {
  freopen(TASKNAME ".in", "r", stdin);
  freopen(TASKNAME ".out", "w", stdout);
 
  int n, m;
  scanf("%d%d", &n, &m);
  vector <vector<int>> ed(n);
  for (int i = 0; i < m; ++i) {
    int k;
    scanf("%d", &k);
    for (int j = 0, prev = -1; j < k; ++j) {
      int next;
      scanf("%d", &next);
      --next;
      if (j) {
        ed[prev].push_back(next);
        ed[next].push_back(prev);
      }
      prev = next;
    }
  }
 
  vector <vector<vector<int>>> cycles(n);
  vector <int> st;
  vector <int> used(n, 0);
  dfs(0, -1, ed, st, used, cycles);
 
  used.assign(n, 0);
  vector <Operation> operations;
  vector <int> perm(4);
  for (int i = 0; i < int(perm.size()); ++i) {
    perm[i] = i;
  }
  buildSubtree(0, ed, cycles, perm, used, operations);
 
  printf("%d\n", int(operations.size()));
  for (const auto & op : operations) {
    op.print();
  }
 
  return 0;
}