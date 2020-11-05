#include <bits/stdc++.h>

std::string a;
int map[300];
int main() {
    std::cin >> a;
    int n = a.size();
    for (int i = 'A'; i <= 'Z'; i++) map[i] = 1;
    map['Q'] = map['R'] = map['U'] = map['O'] = map['P'] = map['S'] = map['D'] = map['G'] = map['J'] = map['C'] = map['B'] = 2;
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum |= map[a[i]]; 
    if (sum == 1 || sum == 2)
        std::cout << "YES" << std::endl;
    else
	    std::cout << "NO" << std::endl;
    return 0;
}