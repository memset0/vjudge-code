#include<bits/stdc++.h>
int main(){
    int T,n,x;
    scanf("%d",&T);
    while(T--){
        long long s=0;
        scanf("%d",&n);
        while(n--){
            scanf("%d",&x);
            s+=x;
        }
        printf("%lld\n",s);
    }
}