#include <cstdio>
#include <cstring>
#define MOD 98765431
typedef long long lint;
struct matrix
{
    int x , y;
    lint num[3][3];
    matrix operator*(const matrix a) const
    {
        matrix t;
        int i , j , k;
        memset(t.num , 0 , sizeof(t.num));
        t.x = x , t.y = a.y;
        for(i = 1 ; i <= t.x ; i ++ )
            for(j = 1 ; j <= t.y ; j ++ )
                for(k = 1 ; k <= y ; k ++ )
                    t.num[i][j] = (t.num[i][j] + num[i][k] * a.num[k][j]) % MOD;
        return t;
    }
}a , b;
lint c[50010];
matrix qpow(matrix a , int b)
{
    matrix t;
    int i;
    t.x = a.x , t.y = a.y;
    memset(t.num , 0 , sizeof(t.num));
    for(i = 1 ; i <= t.x ; i ++ )
        t.num[i][i] = 1;
    while(b)
    {
        if(b & 1)
            t = t * a;
        a = a * a;
        b >>= 1;
    }
    return t;
}
int main()
{
    int n , t , i;
    lint sum = 0;
    scanf("%d%d" , &n , &t);
    for(i = 1 ; i <= n ; i ++ )
        scanf("%lld" , &c[i]) , sum = (sum + c[i]) % MOD;
    b.x = b.y = 2;
    b.num[1][1] = 0 , b.num[1][2] = n - 1 , b.num[2][1] = 1 , b.num[2][2] = n - 2;
    b = qpow(b , t);
    a.x = 1 , a.y = 2;
    for(i = 1 ; i <= n ; i ++ )
    {
        a.num[1][1] = c[i] , a.num[1][2] = (sum - c[i] + MOD) % MOD;
        printf("%lld\n" , (a * b).num[1][1]);
    }
    return 0;
}