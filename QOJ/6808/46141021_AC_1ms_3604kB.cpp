#include<bits/stdc++.h>
using namespace std;
const int N=1e3+9;
int n;
char a[N];
string str;
int main(){
#ifdef memset0
    freopen("A.in","r",stdin);
#endif
    ios::sync_with_stdio(0),cin.tie(0);
    cin>>n;
    getline(cin,str);
    getline(cin,str);
    for(int i=1;i<=n;i++)a[i]=str[i-1];
    for(int i=1;i<=n;i++)
        if(a[i]!='L'&&a[i-1]!='L'&&a[i+1]!='L'){
            a[i]='C';
        }
    for(int i=1;i<=n;i++)cout<<a[i];
    cout<<endl;
}