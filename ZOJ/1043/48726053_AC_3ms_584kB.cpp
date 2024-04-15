#include <algorithm>
#include <iostream>
#include <stdio.h>
#define MAX std::max

#define N 2000
struct NODE {
  char c;   // 保存窗口的字母或者‘-’和‘|’
  int k;    // 窗口的宽度
  int h;    // 窗口的高度
  int l, r; // 左孩子和右孩子的数组下标
};
NODE node[N];   // 保存整个二叉树
char ans[N][N]; // 保存最终的图形

int k;
int chuli() // 输入
{
  scanf("%c", &node[k].c);
  int n = k;
  if (node[n].c == '|' || node[n].c == '-') {
    ++k;
    node[n].l = k;
    chuli();
    ++k;
    node[n].r = k;
    chuli();
    return 1;
  } else {
    return 0;
  }
}

int f(int n) // 计算每个窗口的大小
{
  if (node[n].c <= 'Z' && node[n].c >= 'A') {
    node[n].k = node[n].h = 2;
    return 1;
  }
  f(node[n].l);
  f(node[n].r);
  if (node[n].c == '|') {
    node[n].k = node[node[n].l].k + node[node[n].r].k;
    node[n].h = MAX(node[node[n].l].h, node[node[n].r].h);
  } else {
    node[n].k = MAX(node[node[n].l].k, node[node[n].r].k);
    node[n].h = node[node[n].l].h + node[node[n].r].h;
  }
  return 1;
}

void pr1(int x, int y, int l) // 画竖线，以点(x,y)为上端点，画一条长为l的线，其中，两个端点用‘*’表示。
{
  int i;
  ans[x][y] = '*';
  for (i = 1; i < l; i++) {
    ans[x + i][y] = '|';
  }
  ans[x + i][y] = '*';
}
void pr2(int x, int y, int l) // 画横线
{
  int i;
  ans[x][y] = '*';
  for (i = 1; i < l; i++) {
    ans[x][y + i] = '-';
  }
  ans[x][y + i] = '*';
}
int p(int x, int y, int i) //(x,y)表示当前窗口的左上角的坐标，i表示当前节点的数组下标。
{
  // p1();
  // getchar();
  if (node[i].c == '|') {
    node[node[i].l].h = node[node[i].r].h = node[i].h;
    node[node[i].r].k = node[i].k * node[node[i].r].k / (node[node[i].r].k + node[node[i].l].k);
    node[node[i].l].k = node[i].k - node[node[i].r].k; // 按比例分配宽度
    // 画竖线
    pr1(x, y + node[node[i].l].k, node[i].h);
    p(x, y, node[i].l);
    p(x, y + node[node[i].l].k, node[i].r);
  } else if (node[i].c == '-') {
    node[node[i].l].k = node[node[i].r].k = node[i].k;
    node[node[i].r].h = node[i].h * node[node[i].r].h / (node[node[i].r].h + node[node[i].l].h);
    node[node[i].l].h = node[i].h - node[node[i].r].h; // 按比例分配高度
    // 画横线
    pr2(x + node[node[i].l].h, y, node[i].k);
    p(x, y, node[i].l);
    p(x + node[node[i].l].h, y, node[i].r);
  } else {
    ans[x][y] = node[i].c; // 在窗口左上角填入字母
  }
  return 0;
}

void p1() // 输出窗口
{
  int i, j;
  for (i = 0; i <= node[1].h; i++) {
    for (j = 0; j <= node[1].k; j++) {
      printf("%c", ans[i][j]);
    }
    printf("\n");
  }
}

using namespace std;

int main() {
  int t, i, j, cas = 1;
  cin >> t;
  while (t--) {
    getchar();
    k = 1;
    chuli(); // 输入
    // cout<<"!!"<<endl;
    f(1); // 计算窗口大小
    // 画外框
    ans[0][0] = '*';
    for (j = 1; j < node[1].k; j++) ans[0][j] = '-';
    ans[0][j] = '*';
    for (i = 1; i < node[1].h; i++) {
      ans[i][0] = '|';
      for (j = 1; j < node[1].k; j++) ans[i][j] = ' ';
      ans[i][j] = '|';
    }
    ans[i][0] = '*';
    for (j = 1; j < node[1].k; j++) ans[i][j] = '-';
    ans[i][j] = '*';
    cout << cas++ << endl;
    p(0, 0, 1); // 处理整个框
    p1();       // 输出
  }
}