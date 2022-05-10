#include<bits/stdc++.h>

#define ll long long
#define INF 2147483647

int inp(){
    char c = getchar();
    while(c < '0' || c > '9')
        c = getchar();
    int sum = 0;
    while(c >= '0' && c <= '9'){
        sum = sum * 10 + c - '0';
        c = getchar();
    }
    return sum;
}

int u[2000010], v[2000010], fa[1000010];

int find(int x){
    return (fa[x] == x) ? x : (fa[x] = find(fa[x]));
}

int main(){
    int n = inp();
    int m = inp();
    int k = inp();
    for(int i = 1; i <= n; i++)
        fa[i] = i;
    for(int i = 1; i <= m; i++){
        u[i] = inp();
        v[i] = inp();
        if(u[i] > k && v[i] > k)
            fa[find(u[i])] = find(v[i]);
    }
    int ans = 0;
    for(int i = 1; i <= m; i++){
        if(u[i] > k && v[i] > k)
            continue;
        int fu = find(u[i]);
        int fv = find(v[i]);
        if(fu == fv)
            ans++;
        else
            fa[fu] = fv;
    }
    printf("%d\n", ans);
}