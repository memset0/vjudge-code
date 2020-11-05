#include<cstdio>
#include<cctype>
#define LL long long
using namespace std;
int n,q;
LL c[2][100005];
int read(){
    int ret=0;bool f=1;char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) f^=!(ch^'-');
    for(; isdigit(ch);ch=getchar()) ret=(ret<<3)+(ret<<1)+ch-'0';
    return f?ret:-ret;
}
void Add(int x,LL t){for(int i=x;i<=n;i+=i&-i) c[0][i]+=t,c[1][i]+=t*x;}
LL get(int x){
    LL sum=0;
    for(int i=x;i;i-=i&-i) sum+=((LL)x+1)*c[0][i]-c[1][i];
    return sum;
}
int main(){
//  freopen("prob.in","r",stdin);
//  freopen("prob.out","w",stdout);
    n=read(),q=read();
    for(int i=1;i<=n;i++){
        int x=read();
        Add(i,x);Add(i+1,-x);
    }
    for(int i=1;i<=q;i++){
        int L,R,x;char ch[10];scanf("%s",ch);
        if(ch[0]=='C') L=read(),R=read(),x=read(),Add(L,x),Add(R+1,-x);
        else L=read(),R=read(),printf("%lld\n",get(R)-get(L-1));
    }
    return 0;
}