#include <bits/stdc++.h>

const int N = 1e6 + 5, L = 20;

int n, _n, m, k, cnt, sa[N], rk[N], old[N], tmp[N], buc[N];
int lgn, o[N], ht[N], f[L][N], min[N], max[N];
long long ans, now, sum, w[N];
char str[N];
std::set<int> set;

void radixSort() {
    for (int i = 1; i <= m; i++) { buc[i] = 0; }
    for (int i = 1; i <= n; i++) { buc[rk[i]]++; }
    for (int i = 2; i <= m; i++) { buc[i] += buc[i - 1]; }
    for (int i = n; i; i--) { sa[buc[rk[old[i]]]--] = old[i]; }
}
void suffixArray() {
    for (int i = 1; i <= n; i++) { m = std::max(m, str[i] - 'a' + 1); rk[i] = str[i] - 'a' + 1; old[i] = i; }
    radixSort();
    for (int len = 1; ; len <<= 1) {
        int num = 0;
        for (int i = n - len + 1; i <= n; i++) { old[++num] = i; }
        for (int i = 1; i <= n; i++) { if (sa[i] > len) { old[++num] = sa[i] - len; } }
        radixSort();
        memcpy(tmp, rk, sizeof(rk)); rk[sa[1]] = num = 1;
        for (int i = 2; i <= n; i++) {
            if (tmp[sa[i - 1]] == tmp[sa[i]] && tmp[sa[i - 1] + len] == tmp[sa[i] + len]) { rk[sa[i]] = num; }
            else { rk[sa[i]] = ++num; }
        }
        if (num == n) { break; } else { m = num; }
    }
    for (int i = 1, num = 0; i <= n; i++) {
        if (rk[i] == 1) { ht[1] = num = 0; }
        int j = sa[rk[i] - 1]; num = num ? num - 1 : 0;
        while (i + num <= n && j + num <= n && str[i + num] == str[j + num]) { num++; }
        ht[rk[i]] = num;
    }
}

void build() {
    for (int i = 1; i <= n; i++) { f[0][i] = ht[i]; }
    for (int i = 1; i <= n; i++) { o[i] = log(i) / log(2) + 1e-7; }
    lgn = o[n];
    for (int j = 1; j <= lgn; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            f[j][i] = std::min(f[j - 1][i], f[j - 1][i + (1 << j - 1)]);
        }
    }
}
int query(int l, int r) {
    int lgl = o[r - l + 1];
    return std::min(f[lgl][l], f[lgl][r - (1 << lgl) + 1]);
}
int getLcp(int i, int j) {
    if (i > j) { std::swap(i, j); }
    if (i == j) {
        return n - sa[i] + 1;
    } else {
        return query(i + 1, j);
    }
}

void insert(int i) {
    std::set<int>::iterator l, r = set.lower_bound(i);
    if (!set.empty()) {
        if (r == set.end()) {
            l = r; l--;
            now += getLcp(*l, i);
            if (str[sa[*l]] == str[sa[i]]) {
                w[str[sa[i]] - 'a'] -= getLcp(*l, i);
            }
        } else if (r == set.begin()) {
            now += getLcp(i, *r);
            if (str[sa[*r]] == str[sa[i]]) {
                w[str[sa[i]] - 'a'] -= getLcp(i, *r);
            }
        } else {
            l = r; l--;
            now -= getLcp(*l, *r);
            if (str[sa[*l]] == str[sa[*r]]) {
                w[str[sa[*l]] - 'a'] += getLcp(*l, *r);
            }
            now += getLcp(*l, i);
            if (str[sa[*l]] == str[sa[i]]) {
                w[str[sa[i]] - 'a'] -= getLcp(*l, i);
            }
            now += getLcp(i, *r);
            if (str[sa[*r]] == str[sa[i]]) {
                w[str[sa[i]] - 'a'] -= getLcp(i, *r);
            }
        }
    }
    set.insert(i);
    sum += n - sa[i] + 1;
    w[str[sa[i]] - 'a'] += n - sa[i] + 1;
}

int main() {
    scanf("%s", str + 1);
    n = strlen(str + 1);
    suffixArray(); build();
    for (int x = 0; x < 26; x++) { min[x] = 1e7; max[x] = -1e7; }
    ans = 1; now = 0; sum = 1;
    for (int i = n; i >= 1; i--) {
        insert(rk[i]);
        long long tmp = sum - now;
        min[str[i] - 'a'] = std::min(min[str[i] - 'a'], rk[i]);
        max[str[i] - 'a'] = std::max(max[str[i] - 'a'], rk[i]);
        std::set<int>::iterator l, r;
        r = set.lower_bound(max[str[i] - 'a'] + 1);
        l = set.lower_bound(min[str[i] - 'a']);
        if (l != set.begin()) {
            l--;
            if (r != set.end()) {
                tmp += query(*l, *r);
            }
        }
        tmp -= w[str[i] - 'a'];
        ans += tmp;
    }
    printf("%lld\n", ans);
}