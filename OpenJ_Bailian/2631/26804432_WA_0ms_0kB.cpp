#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
vector<int> e[10005];
vector<int> w2[10005];
int x[100005],y[100005],w[100005];
int X,Y,W,tot=0,sum=0,ans;
int d[10005],vis[10005];
void add(int xx,int yy,int z){
    x[++sum]=xx; y[sum]=yy; w[sum]=z;
}
void dfs(int c){
    vis[c]=1;
    for(int i=0,a;i<e[c].size();i++){
        if(vis[a=e[c][i]])continue;
        dfs(a);
        ans=max(ans,d[c]+d[a]+w2[c][i]);
        d[c]=max(d[c],d[a]+w2[c][i]);
    }
}//dfs求树的直径
int main(){
    while(1){
        bool sign=false;
        char ch; tot=0; X=0;
        if(scanf("%c",&ch)==EOF)break;
        else if(ch=='\n'){
            tot++;
        }
        while(ch<'0' || ch>'9'){
            if(scanf("%c",&ch)==EOF){
                sign=true; break;
            }
            if(ch=='\n')tot++;
        }
        if(sign==true)break;
        while(ch>='0' && ch<='9'){
            X=10*X+(int)ch-'0';
            if(scanf("%c",&ch)==EOF){
                sign=true; break;
            }
        }
        if(sign==true)break;
        if(tot==2)add(0,0,0);
        scanf("%d %d",&Y,&W);
        add(X,Y,W);
    }//读入
    int i1=1;
    while(i1<=sum){
        for(int i=1;i<=10000;i++)e[i].clear(),w2[i].clear();
        memset(d,0,sizeof(d));
        memset(vis,0,sizeof(vis)); ans=0;
        while(x[i1]!=0){
            e[x[i1]].push_back(y[i1]);
            e[y[i1]].push_back(x[i1]);
            w2[x[i1]].push_back(w[i1]);
            w2[y[i1]].push_back(w[i1]);
            i1++;
        }//加边
        i1++;
        dfs(1);
        printf("%d\n",ans);//输出
    }
}