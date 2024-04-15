#include <bits/stdc++.h>
using namespace std;

#define gets my_gets
#define data my_data

char *my_gets(char *str) {
  char c = getchar();
  while (c != '\n') {
    if (c == EOF) {
      *str++ = '\0';
      return NULL;
    }
    *str++ = c;
    c = getchar();
  }
  *str++ = '\0';
  return str;
}

struct {
  int who;
  int eNum;
} Q[10000];
vector<int> data[10000];
map<string, int> name;
map<string, int>::iterator pos;
int author[10000];
int paper[300];

void bfs(string Erdos) {
  memset(author, -1, sizeof(author));
  memset(Q, 0, sizeof(Q));

  int head = 0;
  int tail = 1;
  Q[head].who = name[Erdos];
  Q[head].eNum = 0;
  author[name[Erdos]] = 0;
  while (head != tail) {
    int nowAuthor = Q[head].who;
    int many = data[nowAuthor].size();
    for (int i = 0; i < many; i++)
      if (author[data[nowAuthor][i]] == -1) {
        author[data[nowAuthor][i]] = Q[head].eNum + 1;
        Q[tail].who = data[nowAuthor][i];
        Q[tail++].eNum = Q[head].eNum + 1;
      }
    head++;
  }
}

int main() {
  int p, n;
  bool title;
  int numAuthor, numPaper;
  int iCase = 0;
  char str[300];
  string fullName;
  while (scanf("%d%d", &p, &n) && (p || n)) {
    for (int i = 0; i < 10000; i++) data[i].clear();
    name.clear();
    numAuthor = 0;
    while (p--) {
      title = false;
      numPaper = 0;
      while (!title) {
        scanf("%s", str);
        int len = strlen(str);
        str[len - 1] = ' ';
        fullName = str;
        scanf("%s", str);
        len = strlen(str);

        if (str[len - 1] == ':') title = true;
        // 标题的前面可能没有冒号
        if (str[len - 1] == '.') title = true; // 最后字符不是逗号，是点

        str[len - 1] = '\0';
        fullName += str;

        pos = name.find(fullName);
        // 第一次读取的作者，予以编号
        if (pos == name.end()) name[fullName] = numAuthor++;
        paper[numPaper++] = name[fullName]; // 保存本篇论文的作者编号
        if (title) gets(str);               // gets()能读取空格
      }
      // 本篇论文中的作者编号，将论文合作者相互加入
      for (int i = 0; i < numPaper; i++)
        for (int j = 0; j < numPaper; j++)
          if (i != j) data[paper[i]].push_back(paper[j]);
    }

    string Erdos = "Erdos P.";
    pos = name.find(Erdos);
    if (pos == name.end()) name[Erdos] = numAuthor++; // 判断作者Erdos P.是否出现过，未出现加入

    bfs(Erdos);

    printf("Database #%d\n", ++iCase);
    while (n--) {
      scanf("%s", str);
      printf("%s ", str);
      int len = strlen(str);
      str[len - 1] = ' ';
      fullName = str;
      scanf("%s", str);
      printf("%s: ", str);
      fullName += str;
      pos = name.find(fullName);
      if (pos == name.end()) printf("infinity\n");
      else if (author[name[fullName]] == -1)
        printf("infinity\n");
      else
        printf("%d\n", author[name[fullName]]);
    }
    printf("\n");
  }
  return 0;
}