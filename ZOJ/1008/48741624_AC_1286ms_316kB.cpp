
#include <cstring>
#include <stdio.h>
using namespace std;
#define MaxN 5

struct sqr {
  int u;
  int r;
  int d;
  int l;
  int cnt; // 记录相同方块的个数，取代原来的bool used;
} Square[MaxN * MaxN];

int check[MaxN][MaxN];

int n;     // 方块的行和列数，因为是正方形，所以一个数即可
int t;     // t=n*n 方块总数
int types; // 归并后，总计有多少类方块
// 以上变量在每层递归中都需要，所以设为全局遍历

// 一个递归函数，crt表示当前正在排列第几块方块，crt=[0,t-1]
bool ArrangeSq(int crt) {
  int row, col;
  int i;

  if (crt == t)  // 递归结束条件
    return true; // 如果实在排列第N^2+1块方块，显然说明已排列完成

  // 由于最后所有方块排成n×n的形势，所以从左向右，从上到下数，第crt个方块必然位于（row，col）
  // 行列均以0开头
  row = crt / n;
  col = crt % n;

  for (i = 0; i < types; i++) {
    // 检查所有块，看看是否可以放在当前位置
    if (Square[i].cnt == 0) continue;                                      // 如果该方块被用尽，则跳过
    if (row > 0 && Square[i].u != Square[check[row - 1][col]].d) continue; // 从第二行开始，要检查上一行方块的下方数据是否与本方块上方数据一致，不合适则退出
    if (col > 0 && Square[i].l != Square[check[row][col - 1]].r) continue; // 若与左方数据不一致，也跳出，试试下一个

    // 如果能到达这里，说明找到一个合适的方块了
    check[row][col] = i;
    Square[i].cnt--; // 原先对used的操作被修改
    if (ArrangeSq(crt + 1)) return true;
    // 如果递归带回了好消息，则说明成功了
    // 如未成功，再试试i++后有没有机会，不过首先得把used恢复，checkSq恢复不恢复不受影响
    Square[i].cnt++;
  }
  return false; // 如果执行到这一步，证明穷尽所有值，均为找到合适的方块，必然是无解
}

int main() {
  int i, j;
  int index = 1; // 为了输出空行
  bool flag;
  int u, r, d, l;

  while (1) {
    scanf("%d", &n);
    if (n <= 0) break;

    // 读入一组新数据后重新赋值
    t = n * n;
    types = 0;
    memset(Square, 0, sizeof(Square));
    memset(check, -1, sizeof(check)); // 设置为-1，因为-1是个不可能出现的位置

    // 读入输入值，并保存在对应的Square结构中
    for (i = 0; i < t; i++) {
      scanf("%d%d%d%d", &u, &r, &d, &l);

      // 以下for循环是为了判断新输入的这个方块，是否和已有方块完全相同
      for (j = 0; j < types; j++) {
        if (Square[j].u == u && Square[j].r == r && Square[j].d == d && Square[j].l == l) {
          Square[j].cnt++; // 如果找到相同的方块，则将其计数器加1
          break;           // 只会存在一个相同的方块，找到后直接退出
        }
      }
      if (j == types) // 说明出现了一个新方块
      {
        types++;
        Square[j].u = u;
        Square[j].r = r;
        Square[j].d = d;
        Square[j].l = l;
        Square[j].cnt = 1;
      }
    }

    flag = ArrangeSq(0); // 递归开始，以及递归结束的地方

    if (index != 1) printf("\n"); // 为了满足题目要求，输出空行
    if (flag) printf("Game %d: Possible\n", index);
    else
      printf("Game %d: Impossible\n", index);

    index++;
  }
  return 0;
}