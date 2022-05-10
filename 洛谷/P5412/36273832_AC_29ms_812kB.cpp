// luogu-judger-enable-o2
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<vector>
using namespace std;

const int N=10005;
int n;
vector<float> B,G;
pair<int,float> data[N];

signed main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        register int i;
        scanf("%d",&n);
        B.clear(),G.clear();
        for(i=1;i<=n;i++) scanf("%d",&data[i].first);
        for(i=1;i<=n;i++) cin>>data[i].second;
        for(i=1;i<=n;i++)
            if(data[i].first==0 )G.push_back(data[i].second);
            else B.push_back(data[i].second);
        sort(G.begin(),G.end());
        sort(B.begin(),B.end());
        for(i=0;i<G.size();i++) cout<<G[i]<<" ";
        puts("");
        for(i=0;i<B.size();i++) cout<<B[i]<<" ";
        puts("");
    }
    return 0;
}