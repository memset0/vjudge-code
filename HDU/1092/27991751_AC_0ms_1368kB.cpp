#include<bits/stdc++.h>
int main(){
    int n,x;
    while(true){
        long long s=0;
        scanf("%d",&n);
        if(!n)break;
        while(n--){
            scanf("%d",&x);
            s+=x;
        }
        printf("%lld\n",s);
    }
}