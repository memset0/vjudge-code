#include<bits/stdc++.h>
int main(){
    int n,x;
    while(~scanf("%d",&n)){
        long long s=0;
        while(n--){
            scanf("%d",&x);
            s+=x;
        }
        printf("%lld\n",s);
    }
}