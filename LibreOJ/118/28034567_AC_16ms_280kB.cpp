#include <stdio.h>
#include <regex.h>
#include <string.h>
const int N = 110;
char s[N], t[N];
int main() {
	regex_t r;
	regmatch_t m;
	while (~scanf("%s%s", s, t)) {
		regcomp(&r, s, 1);
		puts(regexec(&r, t, 1, &m, 0) || m.rm_eo - m.rm_so < (int)strlen(t) ? "No" : "Yes");
		regfree(&r);
	}
	return 0;
}
