#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    long long ans=0;
    for(int i=0;i<n;i++){
        ans+=1+2+3+4+5+6;
        ans-=a[i]&1?a[i]+1:a[i]-1;
    }
    cout<<ans<<endl;
}