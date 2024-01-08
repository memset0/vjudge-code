#include<bits/stdc++.h>
using namespace std;
const double PI=acos(-1);
int T,m;
double R,dis,xi,yi,ri,ans;
double Calc(double d,double r,double R){
    double th=acos((d*d+r*r-R*R)/(2.0*d*r));
    return r*th*2.0;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%lf",&m,&R),ans=2.0*PI*R;
        for(int i=1;i<=m;++i){
            scanf("%lf%lf%lf",&xi,&yi,&ri);
            dis=sqrt(xi*xi+yi*yi);
            if(dis>R+ri||dis<R-ri)continue;
            ans+=Calc(dis,ri,R)-Calc(dis,R,ri);
        }
        printf("%.10lf\n",ans);
    }
    return 0;
}