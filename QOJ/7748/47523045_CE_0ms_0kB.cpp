#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 300011;
int n,z[MAXN],nxt[MAXN];
void Z(char* s,int n){
	int mx=1,mi=1;
	z[1]=0;
	for(int i=2;i<=n;++i){
		if(i>mx)z[i]=0;
		else z[i]=min(mx-i+1,z[i-mi+1]);
		while(i+z[i]<=n&&s[i+z[i]]==s[z[i]+1])++z[i];
		if(i+z[i]-1>mx)mx=i+z[i]-1,mi=i;
	}
}
void get_next(char* s,int n)
{
    int j=0;
    for(int i=2;i<=n;++i)
    {
        while(j&&s[j+1]!=s[i])j=nxt[j];
        if(s[j+1]==s[i])++j;
        nxt[i]=j;
    }
}
struct ST
{
    int f[19][MAXN],lg[MAXN];
    void init(int* arr,int n)
    {
        lg[1]=0;
        for(int i=2;i<=n;++i)lg[i]=lg[i>>1]+1;
        for(int i=1;i<=n;++i)f[0][i]=arr[i];
        for(int k=1;k<19;++k)
            for(int i=1;i+(1<<k)-1<=n;++i)
                f[k][i]=max(f[k-1][i],f[k-1][i+(1<<(k-1))]);
    }
    int Qmax(int l,int r)
    {
        int k=lg[r-l];
        return max(f[k][l],f[k][r-(1<<k)+1]);
    }
}T;
char s[MAXN],t[MAXN];
int seq[MAXN],pos[MAXN];
ll f[MAXN],sum[MAXN];
ll sumt[MAXN],sums[MAXN];
int main()
{
    cin.tie(0)->ios::sync_with_stdio(0);
    int n,m;
    cin>>n>>m;
    cin>>(s+1)>>(t+1);
    for(int i=1;i<=n;++i)s[n+i]=t[i];
    Z(s,n*2);
    for(int i=1;i<=n;++i)
    {
        z[i]=min(n,z[n+i]);
        seq[i]=i+z[i]-1;
    }
    T.init(seq,n);
    get_next(s,n);
    for(int i=1;i<=n;++i)
    {
        int w;
        cin>>w;
        f[i]=f[nxt[i]]+w;
        sum[i]=sum[i-1]+w;
        //printf("F[%d]=%d\n",i,f[i]);
    }
    for(int i=1;i<=n;++i)
    {
        sumt[i]=sumt[i-1]+ sum[z[i]];
        sums[i]=sums[i-1]+ f[i];
        //printf("FF[%d]=%d\n",i,sum[z[i]]);
    }
    while(m--)
    {
        int ql,qr;
        cin>>ql>>qr;
        int l=ql,r=qr+1;
        while(l<r)
        {
            int mid=(l+r)>>1;
            if(T.Qmax(ql,mid)>=qr)r=mid;
            else l=mid+1;
        }
        //cout<<"De:l="<<l<<'\n';
        ll ans=sumt[l-1]-sumt[ql-1];
        //cout<<"preans="<<ans<<'\n';
        ans+=sums[qr-l+1];
        cout<<ans<<'\n';
    }
    return 0;
}