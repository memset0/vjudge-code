// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
struct SBT{
    struct Node{ int s[2],fa,key,sz; };
    vector<Node> t;
    SBT(){ t.clear(); t.push_back((Node){{0,0},0,0,0}); rt=0; }
    inline int new_node(int fa,int key){
        t.push_back((Node){{0,0},fa,key,1});
        return (int)t.size()-1;
    }
    int rt;
    inline void up(int x){ t[x].sz=1+t[t[x].s[0]].sz+t[t[x].s[1]].sz; }
    inline void rotate(int x){
        int y=t[x].fa,z=t[y].fa,k=t[y].s[1]==x;
        if(rt==y) rt=x;
        else t[z].s[t[z].s[1]==y]=x;
        t[x].fa=z; t[y].fa=x; t[t[x].s[!k]].fa=y;
        t[y].s[k]=t[x].s[!k]; t[x].s[!k]=y; 
        up(y); up(x);
    }
    inline void fixup(int x){
        for(;x;x=t[x].fa){
            up(x);
            bool k=t[t[x].s[1]].sz>t[t[x].s[0]].sz;
            int y=t[x].s[k],z=t[x].s[!k],w=t[y].s[!k];
            if(t[z].sz<t[t[y].s[k]].sz) rotate(y),x=y;
            else if(t[z].sz<t[w].sz) rotate(w),rotate(w),x=w;
        }
    }
    inline void insert(int key){
        if(rt==0) return void(rt=new_node(0,key));
        int x=rt;
        while(t[x].s[key>t[x].key])
            x=t[x].s[key>t[x].key];
        fixup(t[x].s[key>t[x].key]=new_node(x,key));
    }
    inline void erase(int key){
        int x=rt;
        while(key!=t[x].key)
            x=t[x].s[key>t[x].key];
        if(t[x].s[0]&&t[x].s[1]){
            int y=t[x].s[1];
            while(t[y].s[0]) y=t[y].s[0];
            swap(t[x].key,t[y].key); x=y;
        }
        int w=t[x].s[0]+t[x].s[1],y=t[x].fa;
        if(y==0) rt=w;
        else t[y].s[t[y].s[1]==x]=w;
        if(w) t[w].fa=y;
        fixup(y);
    }
    inline int k_th(int k){
        int x=rt,szx;
        while((szx=t[t[x].s[0]].sz+1)!=k){
            x=t[x].s[k>szx];
            if(k>szx) k-=szx;
        }
        return t[x].key;
    }
    inline int gsz(int key){
        int x=rt,ret=0;
        while(x){
            if(key>t[x].key) ret+=t[t[x].s[0]].sz+1;
            x=t[x].s[key>t[x].key];
        }
        return ret;
    }
    inline int pre(int x){ return k_th(gsz(x)); }
    inline int nxt(int x){ return k_th(gsz(x+1)+1); }
}sbt;
int main(){
    int n; scanf("%d",&n);
    while(n--){
        int opt,x; scanf("%d%d",&opt,&x);
        if(opt==1) sbt.insert(x);
        else if(opt==2) sbt.erase(x);
        else if(opt==3) printf("%d\n",sbt.gsz(x)+1);
        else if(opt==4) printf("%d\n",sbt.k_th(x));
        else if(opt==5) printf("%d\n",sbt.pre(x));
        else if(opt==6) printf("%d\n",sbt.nxt(x));
    }
    return 0;
}