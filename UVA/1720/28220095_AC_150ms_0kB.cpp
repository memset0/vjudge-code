#include<bits/stdc++.h>
using namespace std;
typedef double ld;
typedef long long LL;
map<double,int>cnt;
ld p[4][25];
LL C[25][25];
struct node{
    LL cnt;
    ld p;   
    bool operator<(const node &a)const{
        return p>a.p;    
    }
};
priority_queue<node>hp;
int main(){
    int n;
    while(scanf("%d",&n)==1){
        memset(C,0,sizeof C);
        memset(p,0,sizeof p);
        for(int i=0;i<4;++i){
            p[i][0]=1;  
            scanf("%lf",&p[i][1]);
            for(int j=2;j<=n;++j)
                p[i][j]=p[i][j-1]*p[i][1];
        }
        C[0][0]=1;
        for(int i=1;i<=n;++i){
            C[i][0]=1;
            for(int j=1;j<=i;++j)
                C[i][j]=C[i-1][j-1]+C[i-1][j];
        }
        for(int i=0;i<=n;++i)
            for(int j=0;j<=n;++j)
                for(int k=0;k<=n;++k){
                    if(i+j+k>n) continue;
                    LL cnt=C[n][i]*C[n-i][j]*C[n-i-j][k];
                    ld r=p[0][i]*p[1][j]*p[2][k]*p[3][n-i-j-k];
                    hp.push((node)<%cnt,r%>);
                }
        ld ans=0;
        while(!hp.empty()){
            node A=hp.top();
            hp.pop();
            if(A.cnt>1){
                if(A.cnt&1) hp.push((node)<%1,A.p%>);
                A.cnt>>=1,A.p*=2;
                if(A.cnt)hp.push((node)<%A.cnt,A.p%>);
                ans+=A.cnt*A.p;
            }else{
                if(hp.empty()) break;
                node B=hp.top();
                hp.pop();
                hp.push((node)<%1,A.p+B.p%>);
                B.cnt--;
                ans+=A.p+B.p;
                if(B.cnt) hp.push(B);   
            }
        }
        printf("%lf\n",ans);
    }
    return 0;
}