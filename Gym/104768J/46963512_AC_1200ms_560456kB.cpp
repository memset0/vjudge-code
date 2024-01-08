#include<bits/stdc++.h>
#ifndef memset0
    #define endl '\n'
#endif
#define all(x) (x).begin(),(x).end()
using namespace std;
const int N=1e6+9,p1=998244353,p2=1e9+7,base=131131;
int T,n,m,tot,in[N<<2],out[N<<2],fa[N<<2];
bool ins[N<<2],inq[N<<2];
string tmp;
vector<int> q,ans[2];
vector<char> a[N],b[N];
vector<pair<int,int>> G[N<<2];
vector<vector<pair<int,int>>> cir[N<<2];
inline int find(int x){
    if(fa[x]==x)return x;
    return fa[x]=find(fa[x]);
}
struct Hash{
    int x,y;
    Hash push(int c)const{
        return Hash{
            (int)(((long long)x*base+c)%p1),
            (int)(((long long)y*base+c)%p2),
        };
    }
    void from(const Hash &rhs,int c){
        x=((long long)rhs.x*base+c)%p1;
        y=((long long)rhs.y*base+c)%p2;
    }
    bool operator<(const Hash &rhs)const{
        return x==rhs.x?y<rhs.y:x<rhs.x;
    }
    bool operator==(const Hash &rhs)const{
        return x==rhs.x&&y==rhs.y;
    }
    bool operator!=(const Hash &rhs)const{
        return x!=rhs.x||y!=rhs.y;
    }
    friend inline Hash operator+(Hash a,const Hash &b){
        a.x+=b.x;
        a.y+=b.y;
        if(a.x>=p1)a.x-=p1;
        if(a.y>=p2)a.y-=p2;
        return a;
    }
    friend inline Hash operator-(Hash a,const Hash &b){
        a.x-=b.x;
        a.y-=b.y;
        if(a.x<0)a.x+=p1;
        if(a.y<0)a.y+=p2;
        return a;
    }
    friend inline Hash operator*(const Hash &a,const Hash &b){
        return {
            (int)((long long)a.x*b.x%p1),
            (int)((long long)a.y*b.y%p2),
        };
    }
}pw[N],al[N],ar[N],bl[N],br[N];
const Hash zeros={0,0},ones={1,1};
struct HashArray:vector<Hash>{
    Hash query(int l,int r)const{
        if(l==1)return this->operator[](r);
        return this->operator[](r)-this->operator[](l-1)*pw[r-l+1];
    }
}ha[N],hb[N];
void dfs(int u,vector<pair<int,int>> &cir){
    if(!inq[u]){
        q.push_back(u);
        inq[u]=true;
    }
    // cerr<<"dfs "<<cir.size()<<" "<<u<<endl;
    if(G[u].size()){
        cir.push_back(G[u].back());
        int v=G[u].back().first;
        G[u].pop_back();
        dfs(v,cir);
    }
}
void output(int u){
    if(ins[u])return;
    ins[u]=true;
    if(cir[u].empty())return;
    // cerr<<"output "<<u<<endl;
    while(cir[u].size()){
        for(auto [v,w]:cir[u].back()){
            ans[w/n].push_back(w);
            if(v!=u)output(v);
        }
        cir[u].pop_back();
    }
}
int main(){
#ifdef memset0
    freopen("L.in","r",stdin);
#endif
    ios::sync_with_stdio(0),cin.tie(0);
    pw[0]=ones;
    for(int i=1;i<N;i++){
        pw[i]=pw[i-1]*Hash{base,base};
    }
    auto init=[&](int n,vector<char> *a,HashArray *ha){
        vector<pair<Hash,int>> at;
        for(int i=1;i<=n;i++){
            getline(cin,tmp);
            a[i].resize(m+1);
            ha[i].resize(m+1);
            ha[i][0]=zeros;
            for(int j=1;j<=m;j++){
                a[i][j]=tmp[j-1];
                ha[i][j].from(ha[i][j-1],a[i][j]);
                // fprintf(stderr,"i=%d j=%d a=%d hx=%d hy=%d\n",i,j,a[i][j],ha[i][j].x,ha[i][j].y);
            }
            at.emplace_back(ha[i][m],i);
        }
        return at;
    };
    cin>>T;
    while(T--){
        cin>>n>>m;
        getline(cin,tmp);
        auto at=init(n,a,ha);
        auto bt=init(n,b,hb);
        sort(all(at));
        sort(all(bt));
        bool fl=true;
        // for(int i=0;i<n;i++)cerr<<"! "<<at[i].first.x<<" "<<at[i].second<<" :: "<<bt[i].first.x<<" "<<bt[i].second<<endl;
        for(int i=0;i<n;i++)
            if(at[i].first!=bt[i].first){
                fl=false;
                break;
            }
        if(fl){
            //不需要循环移位
            // cerr<<"circle move"<<endl;
            for(int i=0;i<n;i++)cout<<at[i].second<<" \n"[i+1==n];
            for(int i=0;i<n;i++)cout<<bt[i].second<<" \n"[i+1==n];
            goto nxt;
        }
        for(int k=1;k<m;k++){            
            vector<Hash> f,g;
            for(int i=1;i<=n;i++){
                f.push_back(al[i]=ha[i].query(1,k));
                g.push_back(ar[i]=ha[i].query(k+1,m));
                g.push_back(bl[i]=hb[i].query(1,m-k));
                f.push_back(br[i]=hb[i].query(m-k+1,m));
            }
            sort(all(f)),f.erase(unique(all(f)),f.end());
            sort(all(g)),g.erase(unique(all(g)),g.end());
            tot=f.size()+g.size();
            fill_n(in+1,tot,0);
            fill_n(out+1,tot,0);
            fill_n(ins+1,tot,false);
            fill_n(inq+1,tot,false);
            for(int i=1;i<=tot;i++){
                G[i].clear();
                cir[i].clear();
                fa[i]=i;
            }
            auto add_edge=[&](int x,int y,int w){
                // cerr<<"edge "<<x<<" "<<y<<" "<<w<<endl;
                G[x].emplace_back(y,w);
                out[x]++,in[y]++;
                fa[find(x)]=find(y);
            };
            for(int i=1;i<=n;i++){
                int x=lower_bound(all(f),al[i])-f.begin()+1;
                int y=lower_bound(all(g),ar[i])-g.begin()+1+f.size();
                add_edge(x,y,i-1);
            }
            for(int i=1;i<=n;i++){
                int x=lower_bound(all(g),bl[i])-g.begin()+1+f.size();
                int y=lower_bound(all(f),br[i])-f.begin()+1;
                add_edge(x,y,i+n-1);
            }
            bool fl=true;
            for(int i=1;i<=tot;i++)
                if(in[i]!=out[i]||find(i)!=find(1)){
                    fl=false;
                    break;
                }
            if(!fl)continue;
            for(int i=1;i<=tot;i++)random_shuffle(all(G[i]));
            for(int i=1;i<=tot;i++)random_shuffle(all(G[i]));
            for(int i=1;i<=tot;i++)random_shuffle(all(G[i]));
            for(int i=1;i<=tot;i++)random_shuffle(all(G[i]));
            inq[1]=1;
            q.clear();
            q.push_back(1);
            for(int i=0;i<q.size();i++){
                int u=q[i];
                while(G[u].size()){
                    cir[u].push_back({});
                    dfs(u,cir[u].back());
                }
            }
            ans[0].clear();
            ans[1].clear();
            output(1);
            for(int i=0;i<2;i++){
                assert(ans[i].size()==n);
                for(int j=0;j<n;j++){
                    cout<<(ans[i][j]+1-i*n)<<" \n"[j+1==n];
                }
            }
            goto nxt;
        }
        cout<<-1<<endl;
        nxt:continue;
    }
}