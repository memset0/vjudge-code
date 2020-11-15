#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#define re register
using namespace std;

inline int read() {
    int X=0,w=1; char c=getchar();
    while (c<'0'||c>'9') { if (c=='-') w=-1; c=getchar(); }
    while (c>='0'&&c<='9') X=X*10+c-'0',c=getchar();
    return X*w;
}

int main() {
    int k=read(),d=1999-k%1999,x=(k+d)/1999;
    puts("2000");
    for (re int i=1;i<=1998;++i) printf("%d ",0);
    printf("%d %d\n",-d,x+d);
    return 0;
}
//qwq