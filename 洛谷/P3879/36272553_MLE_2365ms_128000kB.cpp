// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
#include <bits/stdc++.h>
#define ll long long

const int maxn = 1010;

int n, m, t;
std::string s;
std::map < std::string, std::set < int > > map;
std::set < int > set;
std::set < int > ::iterator it;

int main() {
	std::ios::sync_with_stdio(false);
	
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> t;
		for (int j = 1; j <= t; j++) {
			std::cin >> s;
			map[s].insert(i);
		}
	}
	std::cin >> m;
	for (int i = 1; i <= m; i++) {
		std::cin >> s;
		set = map.find(s)->second;
		for (it = set.begin(); it != set.end(); it++)
			std::cout << (*it) << " ";
		std::cout << std::endl;
	}

	return 0;
}