#include <iostream>
using namespace std;

bool flagA, flagB;

void dfs(int a, int b, int max) {
    if (flagA)
        return;
    if (a == 1 && b == 1) {
        flagA = true;
        return;
    }
    if (b == 1)
        flagB = true;
    for (int i = max; i >= 2; i --) {
        if (a % i == 0) {
            dfs(a/i, b, i - 1);
        }
        if (b % i == 0) {
            dfs(a, b/i, i - 1);
        }    
    }
}

int main()
{
    int a, b;
    while(cin >> a >> b) {
        if (a < b) {
            int tmp = a;
            a = b;
            b = tmp;
        }
        flagA = flagB = false;
        dfs(a, b, 100);
        if (flagA || !flagB)
            cout << a << endl;
        else cout << b << endl;
    }
    return 0;
}