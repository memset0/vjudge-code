#include<bits/stdc++.h>
using namespace std;
const int N=1e5+7,SSS=1000;
vector<int>v[N];
unordered_map<int,long long>F[N];
vector<pair<int,int>>S[N];
int C[N<<4],R[N<<4],P[N<<4];
struct query{
    int L,R;
}T[N*100];
struct node{
    int l,r;
};
int n,k,m,a[N],ans[N],p[SSS][SSS];
long long getx(int l,int r){
    return 1ll*l*1000000000ll+r;
}
int getl(int u,int c){
    if(v[u].size()==0) return -12345678;
    if(v[u][0]>c) return -12345678;
    int l=0,r=v[u].size()-1,pos=0;
    while(l<=r){
        int d=(l+r)>>1;
        if(v[u][d]<c) pos=v[u][d],l=d+1; else r=d-1;
    }
    return pos;
}
int getr(int u,int c){
    if(v[u].size()==0) return 12345678;
    if(v[u][v[u].size()-1]<c) return 12345678;
    int l=0,r=v[u].size()-1,pos=0;
    while(l<=r){
        int d=(l+r)>>1;
        if(v[u][d]>c) pos=v[u][d],r=d-1; else l=d+1;
    }
    return pos;
}
void upd(int x,int l,int r){
//	if(x>1) return;
    if(F[x][getx(l,r)]) return;
    F[x][getx(l,r)]=1;
    int A=getr(x,l);
    if(A<=r){
        upd(x+1,l,r); return;
    }
    
    A=getl(x,l);
    int xx=max(A+1,1);
    if(A>=1) upd(x+1,A,r);
    A=getr(x,r);
    if(A<=n) upd(x+1,l,A);
    int yy=min(n,A-1);
    S[x].push_back(make_pair(r-l+1,yy-xx+1));
//	cout<<x<<":"<<r-l+1<<","<<yy-xx+1<<endl; 
}
void clr(int t){
    if(C[t]){
        C[t]=0;
        P[t]=0;
        clr(t<<1);
        clr(t<<1|1);
    }
}
void add(int l,int r,int t,int ql,int qr){
//	if(t==1) cout<<ql<<","<<qr<<","<<k<<endl;
    if(R[t]){
        R[t<<1]=1;
        R[t<<1|1]=1;
        return;
    }
//	if(k==3) cout<<"query"<<ans[1]<<","<<ql<<","<<qr<<","<<R[t]<<endl; 
    if(l==ql&&r==qr){
        if(l==r){
            ans[l]=k,R[t]=1; return;
        }
        if(!R[t]){
            int d=(l+r)>>1;
            if(!R[t<<1]) add(l,d,t<<1,l,d);
            if(!R[t<<1|1]) add(d+1,r,t<<1|1,d+1,r);
            R[t]=1;
        }
        return;
    }
    if(R[t<<1]&&R[t<<1|1]) R[t]=1;
    int d=(l+r)>>1;
    if(ql<=d) add(l,d,t<<1,ql,min(d,qr));
    if(d+1<=qr) add(d+1,r,t<<1|1,max(d+1,ql),qr);
}
void add2(int l,int r,int t,int ql,int qr){
//	if(t==1) cout<<"add"<<ql<<","<<qr<<endl;
    C[t]=1;
    if(l==ql&&r==qr){
        P[t]=1;
        return;
    }
    int d=(l+r)>>1;
    if(ql<=d) add2(l,d,t<<1,ql,min(d,qr));
    if(d+1<=qr) add2(d+1,r,t<<1|1,max(d+1,ql),qr);
    if(P[t<<1]&&P[t<<1|1]) P[t]=1;
}
void Find(int l,int r,int u){
    if(P[u]) return;
    if(l>r) return;
    if(!C[u]){
        add(1,n,1,l,r); return;
    }
    int d=(l+r)>>1;
    Find(l,d,u<<1),Find(d+1,r,u<<1|1);
}
int g1[N<<4];
void getmin(int l,int r,int t,int ql,int qr,int c){
    if(l==ql&&r==qr){
        g1[t]=min(g1[t],c);
        return;
    }
    int d=(l+r)>>1;
    if(ql<=d) getmin(l,d,t<<1,ql,min(d,qr),c);
    if(d+1<=qr) getmin(d+1,r,t<<1|1,max(d+1,ql),qr,c);
}
int getpos(int l,int r,int t,int x){
    if(l==r){
        return g1[t];
    }
    int d=(l+r)>>1;
    if(x<=d) return min(getpos(l,d,t<<1,x),g1[t]);
    else return min(getpos(d+1,r,t<<1|1,x),g1[t]);
}
void upd2(int i,int l,int r){
    if(l>r||l==0) return;
    m++,T[m].L=l,T[m].R=r;
}
void upd3(int i,int l,int r){
    int A=getl(i+1,l);
    int xx=max(A+1,1);
    A=getr(i+1,r);
    int yy=min(n,A-1);
    S[i+1].push_back(make_pair(r-l+1,yy-xx+1));
}
namespace ppp{
const int maxTreeNode=1000000, maxn=2000001;
class segmentTree{
public:
    segmentTree(const int limit):
        limit(limit), root(build(1, limit)){}
    int min()
    {
        return mi[root];
    }
    int ask(int x)
    {
        return ask(root, 1, limit, x);
    }
    void update(int d, int v)
    {
        update(root, 1, limit, d, v);
        return;
    }
private:
    int mi[maxTreeNode], son[2][maxTreeNode], totPoint;
    const int limit, root;
    int build(int l, int r)
    {
        int cur=++totPoint;
        if(l==r) return cur;
        int mid=l+r>>1;
        son[0][cur]=build(l, mid);
        son[1][cur]=build(mid+1, r);
        return cur;
    }
    void update(int k, int l, int r, int d, int v)
    {
        if(l==r){
            mi[k]=v;
            return;
        }
        int mid=l+r>>1;
        if(d<=mid) update(son[0][k], l, mid, d, v);
        else update(son[1][k], mid+1, r, d, v);
        mi[k]=std::min(mi[son[0][k]], mi[son[1][k]]);
        return;
    }
    int ask(int k, int l, int r, int x)
    {
        if(l==r) return l;
        int mid=l+r>>1;
        if(mi[son[0][k]]<x) return ask(son[0][k], l, mid, x);
        else return ask(son[1][k], mid+1, r, x);
    }
}; //线段树

struct query{
    int l, r, id;
    bool operator<(const query& another)const {
        return r==another.r ? l<another.l : r<another.r;
    }
}q[maxn]; //离线

int  ans[maxn], cpy[maxn<<1], cnt;
int getRnk(int x)
{
    return lower_bound(cpy+1, cpy+cnt+1, x)-cpy;
}
int getNum(int k)
{
    return cpy[k];
}
void main2()
{
    //freopen("test.in", "r", stdin);
    
    int l;
    cpy[++cnt]=1; //放入1，作为下界
    for(int i=1;i<=n;i++) a[i]++;
    for(int i=1; i<=n; i++)
        cpy[++cnt]=a[i], cpy[++cnt]=a[i]+1;
    for(int i=1; i<=m; i++)
        q[i].l=T[i].L,q[i].r=T[i].R,q[i].id=i;
    
    sort(q+1, q+m+1);
    sort(cpy+1, cpy+cnt+1);
    cnt = unique(cpy+1, cpy+cnt+1)-cpy; //去重

    for(int i=1; i<=n; i++)
        a[i]=getRnk(a[i]); //离散化，用排名代替数据
    segmentTree* Tree=new segmentTree(cnt);

    int cur=0;
    for(int i=1; i<=m; i++){
        while(cur<q[i].r)
            Tree->update(a[cur], ++cur);
        ans[q[i].id]=Tree->ask(q[i].l);
    }
//    for(int i=1;i<=m;i++) cout<<T[i].L<<","<<T[i].R<<","<<ans[i]<<endl;
    for(int i=1; i<=m; i++)
        upd3(ans[i]-2,T[i].L,T[i].R);
    for(int i=1;i<=n;i++) a[i]--;
}
}
signed main(){
    cin>>n; int Ss=0,Tt=0;
    for(int i=1;i<=16*n;i++) g1[i]=n+1;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),v[a[i]].push_back(i);
    for(int i=1;i<=n;i++){
        if(a[i]==0) Ss=0;
        else Ss++;
        Tt=max(Tt,Ss);
    }
    for(int i=0;i<n;i++){
        if(v[i].size()==0) break;
        if(v[i][0]>1) getmin(1,n,1,1,v[i][0]-1,0);
        v[i].push_back(n+1);
        for(int j=1;j<v[i].size();j++){
//    		cout<<j<<" "<<endl;
            int l=v[i][j-1],r=v[i][j]-1,pos=v[i][j];
            while(l<=r){
                int d=(l+r)>>1;
                if(getpos(1,n,1,d)>v[i][j-1]) pos=d,r=d-1;
                else l=d+1; 
            }
            upd2(i,getpos(1,n,1,v[i][j-1]),v[i][j-1]);
            if(pos==v[i][j]) continue;
            
            getmin(1,n,1,v[i][j-1],v[i][j]-1,v[i][j-1]);
            l=v[i][j-1],r=pos;
            
//			cout<<i<<","<<v[i][j-1]<<","<<v[i][j]-1<<","<<pos<<endl;
            upd2(i,l,r);
            
        }
    }
    for(int i=1;i<=16*n;i++) g1[i]=n+1;
    ppp::main2();
    if(Tt+1<=n) k=0,add(1,n,1,Tt+1,n);
    clr(1);
    for(int i=1;i<=n;i++){
        k=i;
        clr(1);
        for(int j=0;j<S[i].size();j++) add2(1,n,1,S[i][j].first,S[i][j].second);
        Find(1,n,1);
    }
//    for(int i=1;i<=n;i++){
//        k=i;
//        clr(1);
//        for(int j=0;j<S[i].size();j++){
//			for(int k=S[i][j].first;k<=S[i][j].second;k++) p[i][k]=1;
//		}
//    }
//    for(int i=1;i<=n;i++){
//    	for(int j=1;j<=n;j++) cout<<p[j][i]<<" ";
//    	cout<<endl;
//    }
    for(int i=1;i<=n;i++) printf("%d ",ans[i]);
    return 0;
}
//8
//0 1 2 3 0 1 0 2
