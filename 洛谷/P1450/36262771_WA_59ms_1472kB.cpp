#include<bits/stdc++.h>

const int N=1e5+10;
int c[5],d[5],s,t,p,tot;
long long ans,f[N];

int main(){
    std::cin>>c[1]>>c[2]>>c[3]>>c[4]>>tot;
    f[0]=1;
    for(int i=1;i<=4;i++)
        for(int j=0;j+i<N;j++)
            f[j+i]+=f[j];
    for(int i=0;i<tot;i++){
        ans=0;
        std::cin>>d[1]>>d[2]>>d[3]>>d[4]>>s;
        for(int x=0;x<(1<<4);x++){
            t=s,p=1;
            for(int i=1;i<=4;i++)if((x>>(i-1))&1){
                p*=-1;
                t-=(d[i]+1)*c[i];
            }
            if(t>=0)ans+=p*f[t];
            // printf("x=%d t=%d p=%d ans=%lld\n",x,t,p,ans);
        }
        std::cout<<ans<<std::endl;
    }
}