#include<bits/stdc++.h>
using namespace std;
int T,r,b,p,q;
int main(){
    cin.sync_with_stdio(0),cin.tie(0);
    cin>>T;
    for(int fr=1;fr<=T;++fr){
        cin>>r>>b;
        q=(r+b)*(r+b-1)/2;
        p=r*(r-1)/2;
        int g=__gcd(p,q);
        cout<<"Case #"<<fr<<": "<<p/g<<"/"<<q/g<<"\n";
    }
    return 0;
}