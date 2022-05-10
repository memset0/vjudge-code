// luogu-judger-enable-o2
// test

#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<iostream>    
#include<cstdio>
#include<cstring>
using namespace std;
int n,m,tot=0,limit,val;
int trie[27000000][2],latest[27000000];
int s[1000010],root[1000010];
inline int read(){
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        ch=getchar();
    }
    while(ch<='9'&&ch>='0'){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x;
}
void insert(int i,int k,int p,int q){
    if(k<0){
        latest[q]=i;
        return;
    }
    int c=(s[i]>>k)&1;
    if(p)trie[q][c^1]=trie[p][c^1];
    trie[q][c]=++tot;
    insert(i,k-1,trie[p][c],trie[q][c]);
    latest[q]=max(latest[trie[q][0]],latest[trie[q][1]]);
}
int ask(int now,int k){
    if(k<0)return s[latest[now]]^val;
    int c=(val>>k)&1;
    if(latest[trie[now][c^1]]>=limit&&trie[now][c^1])return ask(trie[now][c^1],k-1);
    else return ask(trie[now][c],k-1);
}
int main(){
    memset(root,0,sizeof(root));
    memset(latest,0,sizeof(latest));
    memset(trie,0,sizeof(trie));
    memset(s,0,sizeof(s));
    n=read();
    m=read();
    for(register int i=1;i<=n;i++){
        int x;
        x=read();
        s[i]=s[i-1]^x;
        root[i]=++tot;
        insert(i,23,root[i-1],root[i]);
    }
    for(register int i=1;i<=m;i++){
        char ch;
        int x,l,r;
        cin>>ch;
    //	cout<<ch<<endl;
        if(ch=='A'){
            x=read();
            root[++n]=++tot;
            s[n]=s[n-1]^x;
            insert(n,23,root[n-1],root[n]);
        }
        else{
            l=read();
            r=read();
            x=read();
            val=s[n]^x;
            limit=l-1;
            r--;
            printf("%d\n",ask(root[r],23));
        }
    }
    return 0;
}   