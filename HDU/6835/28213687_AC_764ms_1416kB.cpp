#include<bits/stdc++.h>
int main(){
    int T;
    std::cin>>T;
    while(T--){
        long long b,x;
        std::cin>>b>>x;
        std::cout<<(((b-1)%x==0)?"T":"F")<<std::endl;
    }
}