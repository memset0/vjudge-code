#include <cstdio>
#include <iostream>
#include <list>
#include <sstream>

using namespace std;

char optSign[3] = {'+', '*', '^'};

string Operand(int n, string s) {
  int Count;
  int bracket;
  bool found;
  string answer = "";

  for (int i = 0; i < 3; i++) // 三个运算符按优先线划分表达式
  {
    Count = 1;
    bracket = 0;
    found = false;
    answer = "";

    for (int j = 0; j < s.length(); j++) {
      answer += s[j];
      if (s[j] == '(') {
        bracket++;
        continue;
      } else if (s[j] == ')') {
        bracket--;
        continue;
      } else if (bracket) // 还在括号里
        continue;
      else if (s[j] != optSign[i])
        continue;
      else {
        if (Count == n) return answer.substr(0, answer.length() - 1);
        else {
          found = true;
          answer = "";
          Count++;
        }
      }
    }
    if (found) // 此时找到运算浮，但是为空
      return answer;
  }
  if (s[0] == '(') // 外面第一个是括号
    return s.substr(1, s.length() - 2);
  else
    return s; // 没有运算浮
}

int main() {
  // freopen("tmp.txt", "r", stdin);
  int n;
  string src;
  char ename;
  bool lineFlag = true;
  list<int> question;

  while (cin >> src && src != "*") {
    if (lineFlag) lineFlag = false;
    else
      cout << endl;
    ename = src[0];
    src = src.substr(3);
    cout << "Expression " << ename << ":" << endl;
    cin >> n;
    cin.ignore(); // 丢掉换行符
    while (n--) {
      int num;
      string ops = src;
      question.clear();
      while (cin.peek() != '\n') {
        cin >> num;
        question.push_back(num);
        ops = Operand(num, ops);
      }
      cin.ignore();
      int len = question.size();
      while (!question.empty()) {
        int n = question.back();
        question.pop_back();
        cout << "op(" << n << ",";
      }
      cout << ename;
      for (int i = 1; i <= len; i++) cout << ")";
      cout << "=" << ops << endl;
    }
  }

  return 0;
}
