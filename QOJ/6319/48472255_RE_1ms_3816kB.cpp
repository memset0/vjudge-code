#include <bits/stdc++.h>
using namespace std;
const int N = 2e3 + 9;
struct atom {
    int l, r;
    atom operator+(const atom &rhs) const {
        assert(r + 1 == rhs.l);
        return {l, rhs.r};
    }
} a[N], c[4];
int n;
struct oper {
    int a, b, c;
    bool ok() const { return a && b && c && a <= n && b <= n && c <= n; }
};
vector<array<oper, 4>> ans;
int main() {
#ifdef popteam
    freopen("C.in", "r", stdin);
#endif
    for (int i = 0; i < N; i++)
        a[i].l = a[i].r = i;
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    if (n >= 2)
        ans.push_back({
            oper{1, 2, 2},
            oper{3, 4, 4},
            oper{5, 6, 6},
            oper{7, 8, 8},
        });
    if (n >= 3)
        ans.push_back({
            oper{2, 3, 3}, // 灵活就业 ans[1][0]
            oper{2, 4, 4},
            oper{6, 7, 7},
            oper{6, 8, 8},
        });
    if (n >= 5)
        ans.push_back({
            oper{4, 5, 5}, // 灵活就业 ans[2][0]
            oper{4, 6, 6}, // 灵活就业 ans[2][1]
            oper{4, 7, 7}, // 灵活就业 ans[2][2]
            oper{4, 8, 8},
        });
    if (n >= 9)
        ans.push_back({
            oper{8, 9, 9},
            oper{8, 10, 10},
            oper{8, 11, 11},
            oper{8, 12, 12},
        });
    if (n >= 13)
        ans.push_back({
            oper{8, 13, 13},
            oper{8, 14, 14},
            oper{8, 15, 15},
            oper{8, 16, 16},
        });
    if (n > 9) {
        if (n == 10) {
            ans[3][2] = {9, 10, 10};
            swap(ans[3][2], ans[1][0]);
        } else if (n == 11) {
            ans[3][2] = {9, 10, 10};
            ans[3][3] = {10, 11, 11};
            swap(ans[3][2], ans[1][0]);
            swap(ans[3][3], ans[2][0]);
        } else if (n == 12) {
            ans.insert(ans.begin() + 3, {
                                            oper{9, 10, 10},
                                            oper{10, 11, 11},
                                            oper{11, 12, 12},
                                            oper{10, 12, 12},
                                        });
            swap(ans[1][0], ans[3][0]);
            swap(ans[2][0], ans[3][1]);
            swap(ans[2][1], ans[3][2]);
            // if (n == 13 || n == 14) {
            //     ans.insert(ans.begin() + 4, {
            //                                     oper{12, 13, 13},
            //                                     oper{13, 14, 14},
            //                                 });
            //     swap(ans[2][2], ans[4][0]);
            // }
        } else {
            auto tmp = ans;
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 4; j++) {
                    tmp[i][j].a += 8;
                    tmp[i][j].b += 8;
                    tmp[i][j].c += 8;
                }
            ans.insert(ans.begin() + 3, tmp[0]);
            ans.insert(ans.begin() + 4, tmp[1]);
            ans.insert(ans.begin() + 5, tmp[2]);
        }
    }
    cout << ans.size() << endl;
    for (const auto &op : ans) {
        for (int i = 0; i < 4; i++)
            if (op[i].ok()) {
                cout << op[i].b << " " << op[i].a << " " << op[i].c << endl;
                c[i] = a[op[i].a] + a[op[i].b];
            } else {
                cout << "2000 2000 2000" << endl;
            }
        for (int i = 0; i < 4; i++)
            if (op[i].ok()) a[op[i].c] = c[i];
        cerr << ">> ";
        for (int i = 1; i <= n; i++)
            cerr << a[i].l << "," << a[i].r << "  ";
        cerr << endl;
    }
    for (int i = 1; i <= n; i++) {
        assert(a[i].l == 1 && a[i].r == i);
    }
    cerr << "size = " << ans.size() << endl;
}