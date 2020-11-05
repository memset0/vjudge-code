#include<bits/stdc++.h>
//This code is written by Itst
using namespace std;

inline int read(){
    int a = 0;
    bool f = 0;
    char c = getchar();
    while(c != EOF && !isdigit(c)){
        if(c == '-')
            f = 1;
        c = getchar();
    }
    while(c != EOF && isdigit(c)){
        a = (a << 3) + (a << 1) + (c ^ '0');
        c = getchar();
    }
    return f ? -a : a;
}

const int MAXN = 10010;
struct Edge{
    int end , upEd , w;
}Ed[MAXN << 1];
int head[MAXN] , maxDis , cntEd , maxInd;

inline void addEd(int a , int b , int c){
    Ed[++cntEd].end = b;
    Ed[cntEd].upEd = head[a];
    Ed[cntEd].w = c;
    head[a] = cntEd;
}

void dfs(int now , int pre , int dis){
    if(dis > maxDis){
        maxDis = dis;
        maxInd = now;
    }
    for(int i = head[now] ; i ; i = Ed[i].upEd)
        if(Ed[i].end != pre)
            dfs(Ed[i].end , now , Ed[i].w + dis);
}

int main(){
    string s;
    stringstream ss;//信仰stringstream！！！
    while(getline(cin , s)){
        memset(head , 0 , sizeof(head));
        cntEd = maxDis = 0;
        ss.clear();
        ss.str(s);
        int a , b , c;
        while(ss >> a >> b >> c){//使用stringstream输入
            addEd(a , b , c);
            addEd(b , a , c);
            getline(cin , s);
            ss.clear();
            ss.str(s);
        }
        //求直径
        dfs(1 , 0 , 0);
        dfs(maxInd , 0 , 0);
        printf("%d\n" , maxDis);
    }
    return 0;
}