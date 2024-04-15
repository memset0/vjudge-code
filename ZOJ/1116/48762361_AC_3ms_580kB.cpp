#include <bits/stdc++.h>
using namespace std;

#define gets my_gets
#define stack my_stack
#define end my_end

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

#define sqr(x) ((x) * (x))
#define two(x) (1 << (x))
#define order(x, y, z) ((x) <= (y) && (y) <= (z))

typedef long long LL;
typedef pair<int, int> pii;

const int N = 1;
const int oo = 0x7f7f7f7f;
const double eps = 1e-9;

const char *start = "<?xml version=\"1.0\"?>";
const char *end = "<?end?>";

bool is_name_char(char c) { return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '-'; }
struct Elements {
  int type;
  string name;
  vector<string> attr, value;
  Elements(){};
  Elements(string s) {
    if (s[s.size() - 2] == '/') {
      type = 0;
    } else {
      type = s[1] == '/' ? -1 : 1;
    }
    name.clear();
    attr.clear();
    value.clear();
    for (int i = 1; i < s.size(); ++i) {
      if (i == 1 && s[i] == '/') {
        continue;
      }
      if (is_name_char(s[i])) {
        name = name + s[i];
      } else {
        bool quo = false;
        string ss;
        for (int j = i + 1; j < s.size(); ++j) {
          if (s[j] == '"') {
            if (quo == false) {
              quo = true;
            } else {
              value.push_back(ss);
              quo = false;
            }
            ss.clear();
          } else if (quo || is_name_char(s[j])) {
            ss = ss + s[j];
          } else if (!ss.empty()) {
            attr.push_back(ss);
            ss.clear();
          }
        }
        break;
      }
    }
  }
};

char s[10000];
vector<Elements> all, stack;

bool right_match() {
  stack.clear();
  for (int i = 0; i < all.size(); ++i) {
    if (all[i].name == "") {
      return false;
    }
    if (all[i].type == 0) {
      for (int j = 0; j < stack.size(); ++j) {
        if (stack[j].name == all[i].name) {
          return false;
        }
      }
      if (i && stack.empty()) {
        return false;
      }
      continue;
    }
    if (all[i].type == -1) {
      if (stack.empty()) {
        return false;
      }
      Elements top = stack[stack.size() - 1];
      if (top.type != 1 || top.name != all[i].name) {
        return false;
      }
      stack.pop_back();
    } else {
      for (int j = 0; j < stack.size(); ++j) {
        if (stack[j].name == all[i].name) {
          return false;
        }
      }
      if (i && stack.empty()) {
        return false;
      }
      stack.push_back(all[i]);
    }
  }
  return stack.empty();
}

bool right_attribute() {
  for (int i = 0; i < all.size(); ++i) {
    for (int j = 0; j < all[i].attr.size(); ++j) {
      for (int k = j + 1; k < all[i].attr.size(); ++k) {
        if (all[i].attr[j] == all[i].attr[k]) {
          return false;
        }
      }
    }
    if (all[i].attr.size() != all[i].value.size()) {
      return false;
    }
  }
  return true;
}

int main() {
  gets(s);
  if (strcmp(s, end)) {
    string temp;
    all.clear();
    while (true) {
      gets(s);
      if (strcmp(s, start) == 0 || strcmp(s, end) == 0) {
        bool flag = temp.empty();
        if (!right_match()) {
          flag = false;
        }
        if (!right_attribute()) {
          flag = false;
        }
        if (!flag) {
          printf("non ");
        }
        puts("well-formed");
        all.clear();
        if (strcmp(s, start) == 0) {
          continue;
        } else {
          break;
        }
      } else {
        for (int i = 0; s[i]; ++i) {
          if (s[i] == '<') {
            temp = "<";
          } else if (s[i] == '>') {
            all.push_back(temp + ">");
            temp.clear();
          } else {
            temp = temp + s[i];
          }
        }
      }
    }
  }
  return 0;
}
