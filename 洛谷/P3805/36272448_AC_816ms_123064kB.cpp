#include<cstdio>
#include<cstring>
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)
char s[32000005],st[32000005];
int p[32000005];
int change()
{
    int len=strlen(st);
    int j=2;
    s[0]='^';
    s[1]='$';
    for (int i=0;i<len;i++)
    {
        s[j++]=st[i];
        s[j++]='$';
    }
    s[j]='&';
    return j;
}
int Manacher()
{
    int len=change(),mid=1,mx=1,ans=-1;
    for (int i=1;i<len;i++)
    {
        if (i<mx)
            p[i]=min(mx-i,p[mid*2-i]);
        else
            p[i]=1;
        while (s[i-p[i]]==s[i+p[i]])
            p[i]++;
        if (mx<i+p[i])
        {
            mid=i;
            mx=i+p[i];
        }
        ans=max(ans,p[i]-1);
    }
    return ans;
}
int main()
{
    scanf("%s",st);
    printf("%d",Manacher());
}