#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <vector>
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
typedef vector<int> VI;
#define PB push_back
#define MP make_pair
#define SZ size()
#define CL clear()
#define AA first
#define BB second
#define EPS 1e-8
#define ZERO(x) memset((x), 0, sizeof(x))
const int INF = ~0U >> 1;
const double PI = acos(-1.0);

int m, n;
char r[3][30];
int e[3][30];
const int MAX_N = 30 * 30 * 30;
int tmp[30];

struct CircularNode {
  int lst[30];
  int num;
  CircularNode *next;
  CircularNode(int n) {
    memset(lst, 0, sizeof(lst));
    num = n;
    next = NULL;
  }
  ~CircularNode() {
    if (next) {
      delete next;
      next = NULL;
    }
  }
};

struct CircularList {
  CircularNode *rt, *cur;
  ~CircularList() { delete rt; }
  CircularList() { rt = NULL; }
  void push_back(int a[], int m) {
    if (!rt) {
      rt = new CircularNode(m);
      cur = rt;
    } else {
      cur->next = new CircularNode(m);
      cur = cur->next;
    }

    for (int j = 0; j < m; j++) {
      cur->lst[a[j]] = j;
    }
  }
};

void mapping(int *r, int st) {
  int cc[30];
  for (int i = 0; i < m; i++) {
    cc[i] = ((tmp[i] + r[(tmp[i] - st + m) % m]) % m + m) % m;
  }
  for (int i = 0; i < m; i++) {
    tmp[i] = cc[i];
  }
}

int main() {
  int kase = 1;
  while (scanf("%d", &m), m) {
    if (kase != 1) puts("");
    printf("Enigma %d:\n", kase++);
    for (int i = 0; i < 3; i++) scanf("%s", r[i]);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < m; j++) {
        e[i][j] = r[i][j] - 'A' - j;
        //                printf("%d ",e[i][j]);
      }
      //            puts("");
    }

    CircularList *aCircularList = new CircularList;

    for (int st1 = 0; st1 < m; st1++) {
      for (int st2 = 0; st2 < m; st2++) {
        for (int st3 = 0; st3 < m; st3++) {
          for (int i = 0; i < m; i++) tmp[i] = i;
          mapping(e[0], st3);
          //                    for(int i=0;i<m;i++) printf("%d ",tmp[i]); puts("");
          mapping(e[1], st2);
          //                    for(int i=0;i<m;i++) printf("%d ",tmp[i]); puts("");
          mapping(e[2], st1);
          //                    for(int i=0;i<m;i++) printf("%d ",tmp[i]); puts("");
          aCircularList->push_back(tmp, m);
          //                    for(int i=0;i<m;i++){
          //                        printf("%d ",aCircularList->cur->lst[i]);
          //                    }
          //                    puts("");
        }
        //                exit(0);
      }
    }

    scanf("%d", &n);
    getchar();
    int kase = 1;
    while (n--) {
      CircularNode *p = aCircularList->rt;
      char c;
      while ((c = getchar()) != '\n') {
        //                printf("%d\n",p->lst[c-'A']);
        putchar('a' + p->lst[c - 'A']);
        p = p->next;
        if (!p) p = aCircularList->rt;
      }
      puts("");
    }

    delete aCircularList;
  }
  return 0;
}

/*
6
FDBCAE
ABDEFC
CDAFEB
1
ACE
*/