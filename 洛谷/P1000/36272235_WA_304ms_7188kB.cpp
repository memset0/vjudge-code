#include <bits/stdc++.h>
const int L = 1024;
int main() {
	char buffer[L];
	for (int i = 0; i <= 100000; i++) {
		std::string s = "C:\\" + std::to_string(i) + ".txt";
		freopen(s.c_str(), "w", stdout);
		fwrite(buffer, 1, L, stdout);
		fclose(stdout);
	}
}