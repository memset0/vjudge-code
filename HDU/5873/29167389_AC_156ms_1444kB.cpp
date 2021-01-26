#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXN = 20010;
int a[MAXN];
int main(){
    int t;
    while(scanf("%d",&t) != EOF){
        while(t--){
            memset(a,0,sizeof(a));
            int n,i,sum = 0;
            bool flag = true;
            scanf("%d",&n);
            for(int i = 0; i < n; i++){
                scanf("%d",&a[i]);
                sum += a[i];
            }
            if(sum != n*(n-1)){
                flag = false;
                puts("F");
                continue;
            }
            sort(a,a+n);
            sum = 0;
            for(int i = 0; i < n-1; i++){
                sum += a[i];
                if(sum >= (i + 1) * i) continue;
                else{
                    flag = false;
                    puts("F");
                    break;
                }
            }
            if(flag) puts("T");
        }
    }
    return 0;
}