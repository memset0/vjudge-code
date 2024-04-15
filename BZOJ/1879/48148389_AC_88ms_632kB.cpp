#ifdef APTEST
#include "debug_tools/program.h"
#endif
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
const unsigned int maxn = 15, maxl = 50;
constexpr unsigned long long mod = 1000003;

char str[maxn][maxl + 1], tmp[maxl + 1];
unsigned long long fac[maxn + 1] = { 1 }, ifac[maxn + 1] = { 1 };
unsigned long long w[maxn + 1];
unsigned int n, l;

unsigned long long QuickPow(unsigned long long a, unsigned long long e)
{
    unsigned long long ret = 1;
    for (unsigned long long i = 1; e; i <<= 1)
    {
        if (e & i)
        {
            ret = (ret * a) % mod;
            e ^= i;
        }
        a = (a * a) % mod;
    }
    return ret;
}
void prepFac(const unsigned int l)
{
    for (unsigned long long i = 1; i <= l; ++i)
    {
        fac[i] = (fac[i - 1] * i) % mod;
        ifac[i] = QuickPow(fac[i], mod - 2);
    }
}
inline unsigned long long c(const unsigned int n, const unsigned int m)
{
    return ((fac[n] * ifac[n - m]) % mod * ifac[m]) % mod;
}
unsigned long long fun(const unsigned int l)
{
    unsigned long long ret = 1;
    for (unsigned int i = 0; i < l; ++i)
        ret = (ret * (tmp[i] ? 1 : 26)) % mod;
    return ret;
}
bool apply(const unsigned int p, const unsigned int l)
{
    for (unsigned int i = 0; i < l; ++i)
    {
        if (tmp[i] == str[p][i] || !str[p][i])
            continue;
        else if (!tmp[i])
            tmp[i] = str[p][i];
        else
            return false;
    }
    return true;
}
void fun(const unsigned int p, const unsigned int k, const unsigned int sel = 0)
{
    if (p >= n)
    {
        if (sel >= k)
            w[sel] = (w[sel] + fun(l)) % mod;
        return;
    }
    fun(p + 1, k, sel);
    char old[maxl + 10];
    memcpy(old, tmp, l);
    if (apply(p, l))
        fun(p + 1, k, sel + 1);
    memcpy(tmp, old, l);
}
unsigned long long solve(const unsigned int n, const unsigned int k)
{
    l = strlen(str[0]);
    for (unsigned int i = 0; i < n; ++i)
        replace(str[i], str[i] + l, '?', char(0));
    memset(w, 0, sizeof(w));
    fun(0, k);
    unsigned long long ret = w[k];
    for (unsigned int i = 1; i <= n - k; ++i)
    {
        const unsigned long long t = (c(k + i, k) * w[k + i]) % mod;
        ret = (i & 0x01 ? ret + mod - t : ret + t) % mod;
    }
    return ret;
}
int main()
{
#ifndef APTEST
    ios_base::sync_with_stdio(false);
#endif
    prepFac(maxn);
    unsigned int t;
    cin >> t;
    for (unsigned int i = 0; i < t; ++i)
    {
        unsigned int k;
        cin >> n >> k;
        for (unsigned int i = 0; i < n; ++i)
            cin >> str[i];
        cout << (k > n ? 0 : solve(n, k)) << endl;
    }
    return 0;
}
// why my program get TLE