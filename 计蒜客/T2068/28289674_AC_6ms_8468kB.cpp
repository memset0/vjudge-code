// luogu-judger-enable-o2
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define M 10007
#define null NULL
#define caser(c) (c=='*')
int len;
char s[150000];
int match[150000]= {0};    // Match ')' by '('
int stack[150000]= {0};    //Stack [0..n]
void fillmatch(int n) {
    int top=-1;
    for(int i=0; i<n; i++) {
        if(s[i]=='(') {
            stack[++top]=i;
        } else if(s[i]==')') {
            match[stack[top--]]=i;
        }
    }
}
int memory[100100][2]= {0};
struct node {
    bool type;
    // true -> *
    // false -> +
    node *l,*r;
} *root,ex[100100];
int ex_len=0;
node *build(int l,int r) {
    if(l-r==1)return null;
    // l<=r
    int point=-1;
    if(match[l]==r)
        return build(l+1,r-1);
    for(int i=l; i<=r; i++) {
        bool Break=false;
        switch(s[i]) {
            case '(':
                i=match[i];
                break;
            case ')':
                exit(1);
                break;
            case '+':
                point=i,Break=true;
                break;
            case '*':
                point=i;
                break;
        }
        if(Break)break;
    }
    node& res=ex[ex_len++];
    res.type=caser(s[point]);
    res.l=build(l,point-1);
    res.r=build(point+1,r);
    return &res;
}
#define l_0 d(x->l,0)
#define l_1 d(x->l,1)
#define r_0 d(x->r,0)
#define r_1 d(x->r,1)
int d(node *x,int make) {
    if(x==null)return 1;
    int& ans=memory[x-ex][make];
    if(ans)return ans;
    if(make) {
        if(x->type)ans=l_1*r_1;
        else ans=l_0*r_1%M+l_1*r_0%M+l_1*r_1%M;
    } else {
        if(x->type)ans=l_0*r_1%M+l_1*r_0%M+l_0*r_0%M;
        else ans=l_0*r_0;
    }
    ans%=M;
    return ans;
}
int main() {
    memset(match,-1,sizeof match);
    int n;
    scanf("%d%s",&n,s);
    fillmatch(n);
    root=build(0,n-1);
    printf("%d",d(root,0));
    return 0;
}