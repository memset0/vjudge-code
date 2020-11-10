#include <bits/stdc++.h>

#define For(i, l, r) for(register int i = (l), i##end = (int)(r); i <= i##end; ++i)
#define Fordown(i, r, l) for(register int i = (r), i##end = (int)(l); i >= i##end; --i)
#define Set(a, v) memset(a, v, sizeof(a))
#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define debug(x) cout << #x << ": " << (x) << endl
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)

using namespace std;

typedef unsigned int ui;

template<typename T> inline bool chkmin(T &a, T b) {return b < a ? a = b, 1 : 0;}
template<typename T> inline bool chkmax(T &a, T b) {return b > a ? a = b, 1 : 0;}

namespace pb_ds
{   
    namespace io
    {
        const int MaxBuff = 1 << 22;
        const int Output = 1 << 24;
        char B[MaxBuff], *S = B, *T = B;
        #define getc() ((S == T) && (T = (S = B) + fread(B, 1, MaxBuff, stdin), S == T) ? 0 : *S++)
        char Out[Output], *iter = Out;
        inline void flush()
        {
            fwrite(Out, 1, iter - Out, stdout);
            iter = Out;
        }
    }

    template<class Type> inline Type read()
    {
        using namespace io;
        register char ch; register Type ans = 0; register bool neg = 0;
        while(ch = getc(), (ch < '0' || ch > '9') && ch != '-')     ;
        ch == '-' ? neg = 1 : ans = ch - '0';
        while(ch = getc(), '0' <= ch && ch <= '9') ans = ans * 10 + ch - '0';
        return neg ? -ans : ans;
    }

	inline void ReadString(char *str) {
		using namespace io;
		register char ch = getc();
		while (!isalpha(ch)) ch = getc();
		register int len = 0;
		for (; isalpha(ch); ch = getc()) str[++ len] = ch;
	}

}

using namespace pb_ds;

void File() {
#ifdef zjp_shadow
	freopen ("P2114.in", "r", stdin);
	freopen ("P2114.out", "w", stdout);
#endif
}

int n, m; 
ui val0 = 0, val1 = (1u << 31) - 1;

int main () {

	File();

	n = read<int>(), m = read<int>();

	For (i, 1, n) {
		register char opt[4]; 
		ReadString(opt);
		register int val(read<int>());
		if (opt[1] == 'A') val0 &= val, val1 &= val;
		if (opt[1] == 'X') val0 ^= val, val1 ^= val;
		if (opt[1] == 'O') val0 |= val, val1 |= val;
	}

	ui res = 0, cur = 0;
	for (int i = 1 << 30; i; i >>= 1) {
		if ((val0 & i) < (val1 & i) && cur + i <= (ui)m)
			cur += i, res += val1 & i;
		else res += val0 & i;
	}

	printf ("%u\n", res);

	return 0;

}