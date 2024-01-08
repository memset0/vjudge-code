
#include<bits/stdc++.h>
using namespace std;
const int N=1e3;
int T,n,m,Q,u[N+10][N+10],d[N+10][N+10],l[N+10][N+10],r[N+10][N+10];
int op,p,q,tl,tr,fl;
int ans;
vector<int>ls[N+10],rs[N+10];
set<int>sl,sr;
set<int>::iterator it;
char mp[N+10][N+10];
int Findr(int x){
    it=sr.upper_bound(x);
    if(it==sr.begin())return 0;
    return *--it;
}
int Findl(int x){
    it=sl.lower_bound(x);
    if(it==sl.end())return fl+1;
    return *it;
}
int main(){
    cin.sync_with_stdio(0),cin.tie(0);
    cin>>T;
    for(int fr=1;fr<=T;++fr){
        cin>>n>>m>>Q;
        for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)cin>>mp[i][j];
        for(int i=1;i<=n;++i)for(int j=1;j<=m;++j){
            if(mp[i][j]=='#')u[i][j]=u[i-1][j]+1,l[i][j]=l[i][j-1]+1;
            else u[i][j]=l[i][j]=0;
        }
        for(int i=n;i>=1;--i)for(int j=m;j>=1;--j){
            if(mp[i][j]=='#')d[i][j]=d[i+1][j]+1,r[i][j]=r[i][j+1]+1;
            else d[i][j]=r[i][j]=0;
        }
        cout<<"Case #"<<fr<<":\n";
        while(Q--){
            cin>>op>>p>>q;
            if(op==1){
                if(mp[p][q]=='#')mp[p][q]='.',u[p][q]=d[p][q]=l[p][q]=r[p][q]=0;
                else mp[p][q]='#',u[p][q]=u[p-1][q]+1,d[p][q]=d[p+1][q]+1,l[p][q]=l[p][q-1]+1,r[p][q]=r[p][q+1]+1;
                for(int i=p+1;i<=n&&mp[i][q]=='#';++i)u[i][q]=u[i-1][q]+1;
                for(int i=p-1;i>=1&&mp[i][q]=='#';--i)d[i][q]=d[i+1][q]+1;
                for(int i=q+1;i<=m&&mp[p][i]=='#';++i)l[p][i]=l[p][i-1]+1;
                for(int i=q-1;i>=1&&mp[p][i]=='#';--i)r[p][i]=r[p][i+1]+1;
            }else{
                if(mp[p][q]=='.'){
                    cout<<"0\n";
                    continue;
                }
                ans=1;
                sl.clear(),sr.clear();
                fl=m;
                for(int i=q;i>q-l[p][q];--i)if(mp[p][i]=='#'){
                    ls[p-u[p][i]+1].push_back(i);
                    sl.insert(i);
                }
                for(int i=q;i<q+r[p][q];++i)if(mp[p][i]=='#'){
                    rs[p-u[p][i]+1].push_back(i);
                    sr.insert(i);
                }
                for(int i=p;i>=1;--i){
                    if(sl.empty()||sr.empty())break;
                    ans=max(ans,(p-i+1)*(Findr(q+r[i][q]-1)-Findl(q-l[i][q]+1)+1));
                    for(int j:ls[i])sl.erase(sl.find(j));
                    for(int j:rs[i])sr.erase(sr.find(j));
                }
                vector<int>().swap(ls[p]);
                vector<int>().swap(rs[p]);
                sl.clear(),sr.clear();
                for(int i=q;i>q-l[p][q];--i)if(mp[p][i]=='#'){
                    ls[p+d[p][i]-1].push_back(i);
                    sl.insert(i);
                }
                for(int i=q;i<q+r[p][q];++i)if(mp[p][i]=='#'){
                    rs[p+d[p][i]-1].push_back(i);
                    sr.insert(i);
                }
                for(int i=p;i<=n;++i){
                    if(sl.empty()||sr.empty())break;
                    //cout<<"i="<<i<<" r="<<Findr(q+r[i][q]-1)<<" l="<<Findl(q-l[i][q]+1)<<"\n";
                    ans=max(ans,(i-p+1)*(Findr(q+r[i][q]-1)-Findl(q-l[i][q]+1)+1));
                    for(int j:ls[i])sl.erase(sl.find(j));
                    for(int j:rs[i])sr.erase(sr.find(j));
                }
                for(int i=1;i<=n;++i)vector<int>().swap(ls[i]),vector<int>().swap(rs[i]);
                //////////////////////////////////////////
                fl=n;
                sl.clear(),sr.clear();
                for(int i=p;i>p-u[p][q];--i)if(mp[i][q]=='#'){
                    ls[q-l[i][q]+1].push_back(i);
                    sl.insert(i);
                }
                for(int i=p;i<p+d[p][q];++i)if(mp[i][q]=='#'){
                    rs[q-l[i][q]+1].push_back(i);
                    sr.insert(i);
                }
                for(int i=q;i>=1;--i){
                    if(sl.empty()||sr.empty())break;
                    ans=max(ans,(q-i+1)*(Findr(p+d[p][i]-1)-Findl(p-u[p][i]+1)+1));
                    for(int j:ls[i])sl.erase(sl.find(j));
                    for(int j:rs[i])sr.erase(sr.find(j));
                }
                vector<int>().swap(ls[q]);
                vector<int>().swap(rs[q]);
                sl.clear(),sr.clear();
                for(int i=p;i>p-u[p][q];--i)if(mp[i][q]=='#'){
                    ls[q+r[i][q]-1].push_back(i);
                    sl.insert(i);
                }
                for(int i=p;i<p+d[p][q];++i)if(mp[i][q]=='#'){
                    rs[q+r[i][q]-1].push_back(i);
                    sr.insert(i);
                }
                for(int i=q;i<=m;++i){
                    if(sl.empty()||sr.empty())break;
                    ans=max(ans,(i-q+1)*(Findr(p+d[p][i]-1)-Findl(p-u[p][i]+1)+1));
                    for(int j:ls[i])sl.erase(sl.find(j));
                    for(int j:rs[i])sr.erase(sr.find(j));
                }
                for(int i=1;i<=m;++i)vector<int>().swap(ls[i]),vector<int>().swap(rs[i]);
                cout<<ans<<"\n";
            }
        }
        //cout<<flush;
        for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)u[i][j]=d[i][j]=l[i][j]=r[i][j]=0;
    }
    return 0;
}