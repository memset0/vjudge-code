#include <bits/stdc++.h>

using namespace std;

const int SIZE = 100000 + 5;

int bkt[70], chToId[150];
char chs[70];
int cnt;

using pii = pair<char, char>;

string genAns(void) {
    vector<pii> ranges;
    for (int le = 1; le <= cnt;) {
        if (!bkt[le]) {
            ++le;
        } else {
            int ri = le;
            while (ri < cnt && bkt[ri + 1]) {
                ++ri;
            }
            if (ri - le + 1 >= 3) {
                if (chs[le] == '0') {
                    ranges.push_back(make_pair('!', chs[ri]));
                } else if (chs[le] == 'A') {
                    ranges.push_back(make_pair(':', chs[ri]));
                } else if (chs[le] == 'a') {
                    ranges.push_back(make_pair('[', chs[ri]));
                } else {
                    ranges.push_back(make_pair(chs[le], chs[ri]));
                }
            } else {
                for (int i = le; i <= ri; ++i) {
                    ranges.push_back(make_pair(chs[i], chs[i]));
                }
            }
            le = ri + 1;
        }
    }
    string res = "";
    for (auto [le, ri] : ranges) {
        if (le == ri) {
            res.push_back(le);
        } else {
            res.push_back(le);
            res.push_back('-');
            res.push_back(ri);
        }
    }
    return res;
}

int main(void) {
    chs[++cnt] = ' ', chToId[(int)' '] = cnt;
    for (int i = '0'; i <= '9'; ++i) {
        chs[++cnt] = i, chToId[i] = cnt;
    }
    for (int i = 'A'; i <= 'Z'; ++i) {
        chs[++cnt] = i, chToId[i] = cnt;
    }
    for (int i = 'a'; i <= 'z'; ++i) {
        chs[++cnt] = i, chToId[i] = cnt;
    }
    for (char ch = getchar();
         ch == ' ' || isdigit(ch) || isupper(ch) || islower(ch);
         ch = getchar()) {
        bkt[chToId[(int)ch]] = 1;
    }
    string ans1 = genAns();
    for (int i = 1; i <= cnt; ++i) {
        bkt[i] ^= 1;
    }
    string tmpAns = genAns();
    string ans2 = "^" + (tmpAns == "" ? "!" : tmpAns);
    // cout << "ans1 = " << ans1 << endl;
    // cout << "ans2 = " << ans2 << endl;
    if (ans1.length() != ans2.length()) {
        printf("%%[%s]\n",
               ans1.length() < ans2.length() ? ans1.c_str() : ans2.c_str());
    } else {
        printf("%%[%s]\n", ans1 < ans2 ? ans1.c_str() : ans2.c_str());
    }
    return 0;
}