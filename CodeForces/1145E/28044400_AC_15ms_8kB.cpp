#include <bits/stdc++.h>

int main() {
    for (int id = 21; id <= 50; id++)
        std::cout << (((std::min(id, 25) + id) % (2 + id % 3)) > 0) << std::endl;
    return 0;
}