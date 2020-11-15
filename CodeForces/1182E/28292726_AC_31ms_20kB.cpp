#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#define re register
using namespace std;
typedef long long ll;

inline ll read() {
    ll X=0,w=1; char c=getchar();
    while (c<'0'||c>'9') { if (c=='-') w=-1; c=getchar(); }
    while (c>='0'&&c<='9') X=X*10+c-'0',c=getchar();
    return X*w;
}

const int P=1e9+7,mod=1e9+6;

struct Matrix {
    int s[6][6];
    Matrix() { memset(s,0,sizeof(s)); }
    int* operator [](int i) { return s[i]; }
} A,B,C,D,X,Y;

Matrix operator *(Matrix a,Matrix b) {
    Matrix c;
    for (re int i=1;i<=5;++i)
        for (re int k=1;k<=5;++k)
            for (re int j=1;j<=5;++j)
                c[i][j]=(c[i][j]+1ll*a[i][k]*b[k][j])%mod;
    return c;
}

inline Matrix qpow(Matrix a,ll b) {
    Matrix c;
    for (re int i=1;i<=5;++i) c[i][i]=1;
    for (;b;b>>=1,a=a*a) if (b&1) c=a*c;
    return c;
}

inline int qpow(int a,ll b) {
    int c=1;
    for (;b;b>>=1,a=1ll*a*a%P) if (b&1) c=1ll*c*a%P;
    return c;
}

int main() {
    ll n=read(); int f1=read(),f2=read(),f3=read(),c=read();
    
    A[1][3]=B[1][2]=C[1][1]=1,D[1][4]=8,D[1][5]=1;
    X[1][1]=X[1][2]=X[2][1]=X[2][3]=X[3][1]=1;
    Y[1][1]=Y[1][2]=Y[2][1]=Y[2][3]=Y[3][1]=Y[4][1]=Y[4][4]=Y[5][5]=1,Y[5][1]=-6,Y[5][4]=2;

    A=A*qpow(X,n-3),B=B*qpow(X,n-3),C=C*qpow(X,n-3),D=D*qpow(Y,n-3);
    printf("%d\n",1ll*qpow(f1,A[1][1])*qpow(f2,B[1][1])%P*qpow(f3,C[1][1])%P*qpow(c,D[1][1])%P);
    return 0;
}