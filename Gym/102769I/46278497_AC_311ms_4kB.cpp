#include<bits/stdc++.h>
#define gcd __gcd
using namespace std;
using ll=long long;
using lll=__int128;
int T,Q;
ll ans=0;
void exgcd(lll a,lll b,lll &x,lll &y){
    if(!b){x=1,y=0;return;}
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
struct atom{
    long long x,y;
}dx;
long long dy;
template<class T,class V> V norm(T x,V y){
    x%=y;
    return x<0?x+y:x;
}
void pushy(long long t){
    // fprintf(stderr,"pushy %lld\n",t);
    if(!t)return;
    if(t<0)t=-t;
    if(!dy)dy=t;
    dy=gcd(dy,t);
}
void pushy(const atom &u,const atom &v){
    long long g=gcd(u.x,v.x);
    pushy(v.x/g*u.y-u.x/g*v.y);
}
void pushx(atom it){
    if(it.x==0)return pushy(it.y);
    if(dx.x==0&&dx.y==0){
        dx=it;
        return;
    }
    pushy(it,dx);
    ll g=gcd(it.x,dx.x);
    if(g==dx.x)return;
    lll a=dx.x,b=it.x,x=0,y=0;
    exgcd(a,b,x,y);
    // fprintf(stderr,"a=%lld b=%lld x=%lld y=%lld\n",(ll)a,(ll)b,(ll)x,(ll)y);
    if(dy){
        x=norm(x,dy);
        y=norm(y,dy);
    }
    // fprintf(stderr,"a=%lld b=%lld x=%lld y=%lld\n",(ll)a,(ll)b,(ll)x,(ll)y);
    dx={g,norm(dx.y*x+it.y*y,dy)};
}
bool check(atom it){
    if(dx.x==0&&dx.y==0){
        if(it.x==0&&it.y==0)return true;
        return false;
    }
    if(it.x%dx.x)return false;
    lll y=it.y-(lll)(it.x/dx.x)*dx.y;
    // cerr<<"!! "<<(ll)y<<endl;
    if(dy==0){
        if(y==0)return true;
        return false;
    }
    return y%dy==0;
}
int main(){
#ifdef memset0
    freopen("I.in","r",stdin);
#endif
    ios::sync_with_stdio(0),cin.tie(0);
    cin>>T;
    for(int op,x,y,w,t=1;t<=T;t++){
        dx.x=dx.y=dy=ans=0;
        cin>>Q;
        while(Q--){
            cin>>op>>x>>y;
            if(op==1){
                pushx({x,y});
            }else{
                cin>>w;
                if(check({x,y})){
                    ans+=w;
                }
            }
            // cerr<<op<<" "<<x<<" "<<y<<" => "<<dx.x<<" "<<dx.y<<" : "<<dy<<endl;
        }
        cout<<"Case #"<<t<<": "<<ans<<endl;
    }
}