#include<stdio.h>
int main(){
    int n;  scanf("%d", &n);
    int ans=-1, cnt = 1;
    while(n--){
        int x;  scanf("%d", &x);
        if(x == ans)cnt++;
        else cnt--;
        if(cnt == 0){
            ans = x;
            cnt = 1;
        }
    }
    printf("%d\n", ans);
}