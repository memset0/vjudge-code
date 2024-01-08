#include<stdio.h>
int n,ans=-1,cnt=1,x;
int main(){
    scanf("%d", &n);
    while(n--){
        scanf("%d", &x);
        if(x == ans)cnt++;
        else cnt--;
        if(cnt == 0){
            ans = x;
            cnt = 1;
        }
    }
    printf("%d\n", ans);
}