// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
int n,m,a[50010],p,lenm=0,lena=0,x,y;
int num[1000010],rans=0,ans[50010];
char c;
struct Modi
{
    int t,x,val;
}mod[50010];
struct P
{
    int id,x,y,type;
}ask[50010];
int now=0,l=1,r=0;

inline int read()
{
    register int tmp=0;register char c=getchar();
    while(c<'0'||c>'9')	c=getchar();
    while(c>='0'&&c<='9')	tmp=(tmp<<1)+(tmp<<3)+(c^48),c=getchar();
    return tmp;
}

inline bool cmp(const P &x,const P &y)
{
    if(x.x/p!=y.x/p)	return x.x/p<y.x/p;
    if(x.y!=y.y)	return x.y<y.y;
    return x.type<y.type;
}

inline void add(int val)
{
    if(!num[val])	rans++;
    num[val]++;
}

inline void del(int val)
{
    num[val]--;
    if(!num[val])	rans--;
}

inline void update(int nw)
{
    if(mod[nw].x<=r&&mod[nw].x>=l)	del(a[mod[nw].x]),add(mod[nw].val);
    swap(a[mod[nw].x],mod[nw].val);
}

int main()
{
    n=read(),m=read();p=pow(n,2.0/3);
    for(int i=1;i<=n;i++)	a[i]=read();
    for(int i=1;i<=m;i++)
    {
        c=getchar();
        while(c!='R'&&c!='Q')	c=getchar();
        x=read(),y=read();
        if(c=='R')	mod[++lenm].x=x,mod[lenm].val=y,mod[lenm].t=i;
        else	ask[++lena].x=x,ask[lena].y=y,ask[lena].id=lena,ask[lena].type=lenm;
    }
    sort(ask+1,ask+lena+1,cmp);
    for(int i=1;i<=lena;i++)
    {
        while(r<ask[i].y)	add(a[++r]);while(r>ask[i].y)	del(a[r--]);
        while(l>ask[i].x)	add(a[--l]);while(l<ask[i].x)	del(a[l++]);
        while(now<ask[i].type)	update(++now);
        while(now>ask[i].type)	update(now--);
        ans[ask[i].id]=rans;
    }
    for(int i=1;i<=lena;i++)	printf("%d\n",ans[i]);
    return 0;
}