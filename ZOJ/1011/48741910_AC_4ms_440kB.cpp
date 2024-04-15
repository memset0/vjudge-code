#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

struct Signal {
  int left, right;
};
vector<Signal> table[20][20];
char tree[2100];

int n, m, k;
// n is the number of signals, m is the number of accepting signals, k is the number of signal transmitting elements.
int l;     // the level of the tree
int nodeN; // the number of nodes of the tree

void readTable() {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < k; j++) {
      table[i][j].clear();
      Signal pair;
      while (true) {
        scanf("%d%d", &pair.left, &pair.right);
        table[i][j].push_back(pair);
        char ch = getchar();
        if (ch == '\n') break;
      }
    }
}

void readTree() {
  char ch;
  nodeN = 0;
  for (int i = 0; i <= l; i++)
    for (int j = 0; j < (1 << i); j++) {
      cin >> ch;
      tree[++nodeN] = ch;
    }
}

bool judge(int signal, int node) {
  if (tree[node] == '*' || node > nodeN) {
    if (signal < n - m) return false;
    else
      return true;
  }
  int t = tree[node] - 'a';
  for (int i = 0; i < table[signal][t].size(); i++) {
    int signal1 = table[signal][t][i].left;
    int signal2 = table[signal][t][i].right;
    if (judge(signal1, node * 2) && judge(signal2, node * 2 + 1)) return true;
  }
  return false;
}

int main() {
#ifdef LOCAL
  freopen("in", "r", stdin);
#endif
  int kase = 0;
  while (scanf("%d%d%d", &n, &m, &k) && (n || m || k)) {
    if (kase++) printf("\n");
    printf("NTA%d:\n", kase);
    readTable();
    while (scanf("%d", &l) && (l != -1)) {
      readTree();
      if (judge(0, 1)) printf("Valid\n");
      else
        printf("Invalid\n");
    }
  }
  return 0;
}