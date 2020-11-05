#include<bits/stdc++.h>
typedef long long i64;
typedef double ld;
struct pos{
    int x,y;
    ld abs(){return sqrt(i64(x)*x+i64(y)*y);}
}ps[211];
pos operator-(const pos&a,const pos&b){return (pos){a.x-b.x,a.y-b.y};}
i64 operator*(const pos&a,const pos&b){return i64(a.x)*b.y-i64(a.y)*b.x;}
int sgn(i64 x){return x<0?-1:x>0;}
int n,t[211],kp;
ld ans=0,ks[211];
void maxs(ld&x,ld y){if(x<y)x=y;}
#define F(a) ps[a]*ps[a+1]/ld(p*(ps[a+1]-ps[a]))*pl
void chk(pos p){
    kp=0;
    ld pl=p.abs();
    for(int i=0;i<n+5;++i)t[i]=sgn(p*ps[i]);
    for(int i=0,z;i<n;++i)if(t[i]&&t[i]!=t[i+1]){
        for(z=i+1;!t[z];++z);
        if(t[z]!=t[i]){
            if(z-i<3)ks[kp++]=F(i);
            else{
                ld a0=F(i),a1=F(z-1);
                ks[kp++]=(a0<a1)==(t[i]>0)?a0:a1;
            }
        }else if(z-i==3){
            ld a0=F(i),a1=F(z-1);
            if((a0<a1)==(t[i]>0))maxs(ans,fabs(a1-a0));
        }
    }
    std::sort(ks,ks+kp);
    for(int i=0;i<kp;i+=2)maxs(ans,ks[i+1]-ks[i]);
}
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;++i)scanf("%d%d",&ps[i].x,&ps[i].y);
    for(int i=0;i<n;++i){
        pos o=ps[i];
        for(int j=0;j<n;++j)ps[j]=ps[j]-o;
        for(int j=0;j<5;++j)ps[n+j]=ps[j];
        for(int j=i+1;j<n;++j)chk(ps[j]);
    }
    printf("%.8f",ans);
    return 0;
}