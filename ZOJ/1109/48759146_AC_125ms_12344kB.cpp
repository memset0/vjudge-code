#include <bits/stdc++.h>
using namespace std;

#define gets my_gets

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

char s[25], a[15], b[15];
map<string, string> m;

int main() {
  while (gets(s), s[0]) sscanf(s, "%s%s", a, b), m[string(b)] = string(a);
  while (gets(s)) puts(m.find(s) != m.end() ? m[s].c_str() : "eh");
}