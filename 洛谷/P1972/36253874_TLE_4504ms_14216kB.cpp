// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

#include<bits/stdc++.h>

using namespace std;

int Num[500010];
int Cou[1000010];
int Res[500010];
int Ans = 0;
struct Node{
    int l;
    int r;
    int k;
}q[500010];
int qn;

int Inp(){
    char c = getchar();
    while(c < '0' || c > '9')
        c = getchar();
    int Ress = 0;
    while(c >= '0' && c <= '9'){
        Ress *= 10;
        Ress += c - '0';
        c = getchar();
    }
    return Ress;
}

bool cmp(Node a, Node b){
    if(a.l / qn == b.l / qn)
        return a.r < b.r; 
    return a.l < b.l;
} 

void Add(int Cur){
    if(Cou[Num[Cur]] == 0)
        Ans++;
    Cou[Num[Cur]]++;
}

void Del(int Cur ){
    Cou[Num[Cur]]--;
    if(Cou[Num[Cur]] == 0)
        Ans--;
}

int main(){
    memset(Cou, 0, sizeof(Cou));
    int n, m;
    scanf("%d", &n);
    qn = n / sqrt(m * 2.0 / 3);
    for(int i = 1; i <= n; i++){
        Num[i] = Inp();
    }
    scanf("%d", &m);
    q[0].l = 1;
    q[0].r = 0;
    for(int i = 1; i <= m; i++){
        q[i].l = Inp();
        q[i].r = Inp();
        q[i].k = i;
    }
    sort(q+1, q+m+1, cmp);
    int ll = 1;
    int rr = 0;
    for(int i = 1; i <= m; i++){
        while(ll < q[i].l)
            Del(ll++);
        while(ll > q[i].l)
            Add(--ll);
        while(rr < q[i].r)
            Add(++rr);
        while(rr > q[i].r)
            Del(rr--);
        Res[q[i].k] = Ans;
    }
    for(int i = 1; i <= m; i++)
        printf("%d\n", Res[i]);
}