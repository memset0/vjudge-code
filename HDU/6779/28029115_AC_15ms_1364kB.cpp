#include<bits/stdc++.h>
template<class T> inline void read(T &x){
    x=0; register char c=getchar(); register bool f=0;
    while(!isdigit(c))f^=c=='-',c=getchar();
    while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=200,map[6][3]={{0,1,2},{0,2,1},{1,0,2},{1,2,0},{2,0,1},{2,1,0}};
int T,n,a,b,c,s=1,e=2,tot,cnt[6],pre[N],dis[N],hed[N],inq[N],nxt[N],val[N],to[N],cst[N];
inline void add(int u,int v,int w,int c){
    nxt[tot] = hed[u], to[tot] = v, val[tot] = w, cst[tot] =  c, hed[u] = tot++;
    nxt[tot] = hed[v], to[tot] = u, val[tot] = 0, cst[tot] = -c, hed[v] = tot++;
}
bool spfa() {
    static int q[N];
    memset(pre, 0, 12 << 2);
    memset(dis, -0x3f, 12 << 2);
    int l = 0, r = 0, u; q[0] = s, dis[s] = 0;
    while (l <= r) {
        u = q[(l++) % 11], inq[u] = 0;
        // printf("> %d\n", u);
        for (int i = hed[u], v; v = to[i], i; i = nxt[i])
            if (val[i] && dis[u] + cst[i] > dis[v]) {
                dis[v] = dis[u] + cst[i], pre[v] = i;
                if (!inq[v]) inq[q[(++r) % 11] = v] = 1;
            }
    }
    return pre[e];
}
int solve(){
    int ans_flow = 0, ans_cost = 0;
    while (spfa()) {
        int flow = 1e9, cost = 0;
        for (int i = pre[e]; i; i = pre[to[i ^ 1]]) flow = std::min(flow, val[i]);
        for (int i = pre[e]; i; i = pre[to[i ^ 1]]) val[i] -= flow, val[i ^ 1] += flow, cost += flow * cst[i];
        // printf("flow %d : cost %d\n", flow, cost);
        ans_flow += flow, ans_cost += cost;
    }
    return ans_cost;
}
int main(){
#ifdef memset0
    freopen("1.in","r",stdin);
#endif
    read(T);
    while(T--){
        tot=2;
        memset(to,0,sizeof(to));
        memset(pre,0,sizeof(pre));
        memset(dis,0,sizeof(dis));
        memset(hed,0,sizeof(hed));
        memset(inq,0,sizeof(inq));
        memset(nxt,0,sizeof(nxt));
        memset(val,0,sizeof(val));
        memset(cst,0,sizeof(cst));

        read(n),read(a),read(b),read(c);
        for(int i=0;i<6;i++)cnt[i]=0;
        for(int x,i=1;i<=n;i++){
            read(x);
            switch(x){
                case 12:cnt[0]++;break;
                case 21:cnt[1]++;break;
                case 102:cnt[2]++;break;
                case 120:cnt[3]++;break;
                case 201:cnt[4]++;break;
                case 210:cnt[5]++;break;
            }
        }
        // s=1 t=2 abc=345 | 6...11
        add(1,3,a,0);
        add(1,4,b,0);
        add(1,5,c,0);
        for(int i=0;i<6;i++){
            add(6+i,2,cnt[i],0);
        }
        for(int i=0;i<3;i++)
            for(int j=0;j<6;j++){
                add(3+map[j][i],6+j,1e9,3-i);
            }
        printf("%d\n",solve());
    }
}