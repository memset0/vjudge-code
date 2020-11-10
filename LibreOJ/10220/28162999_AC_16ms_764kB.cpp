#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 110;
int MOD;
typedef long long ll;
struct Matrix {
    ll a[MAXN][MAXN];
    int n, m;
    Matrix(){memset(a, 0, sizeof(a));}
    Matrix operator * (const Matrix &A){
        Matrix res;
        res.n = n;
        res.m = A.m;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                for(int k = 0; k < A.m; k++)
                    res.a[i][k] = (res.a[i][k] + a[i][j] * A.a[j][k] % MOD) % MOD;
        return res;
    }
};
Matrix qpow(Matrix A, int b){
    Matrix res, aa = A;
    res.n = res.m = A.n;
    for(int i = 0; i < res.n; i++)
        res.a[i][i] = 1;
    while(b){
        if(b & 1) res = res * aa;
        aa = aa * aa;
        b >>= 1;
    }
    return res;
}
int main(){
    Matrix C;
    C.n = C.m = 2;
    C.a[0][0] = C.a[0][1] = C.a[1][0] = 1;
    Matrix A;
    A.n = 1;
    A.m = 2;
    A.a[0][0] = 1;
    A.a[1][0] = 1;
    int n;
    scanf("%d%d", &n, &MOD);
    Matrix ans = qpow(C, n - 1) * A;
    printf("%lld\n", ans.a[1][0]);
    return 0;
}