#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    int q,op,k,v;
    map<int,int> a;
    cin>>q;
    while(q--){
        cin>>op;
        if(op){
            cin>>k;
            cout<<(map.find(k)==map.end()?0:a[k])<<endl;
        }else{
            cin>>k>>v;
            a[k]=v;
        }
    }
}