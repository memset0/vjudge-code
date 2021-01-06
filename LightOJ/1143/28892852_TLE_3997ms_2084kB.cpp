// my code got TLE

#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <cstdio>
#include <stack>
#include <queue>
using namespace std;

int Fin[5][5] = {//保存最后的结果
    {1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1},
    {0, 0, -1, 1, 1},
    {0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0},
};
int dir[8][2] = {//方向数组
    {-2, -1},
    {-2, 1},
    {-1, 2},
    {1, 2},
    {2, 1},
    {2, -1},
    {1, -2},
    {-1, -2}
};
int G[5][5]; //保存输入的位置
char ch;
int t, ans;
struct Point {//坐标结构体
    int x;
    int y;
};

//判断是否到最后的位置
int judge(){
    for(int i = 0 ; i < 5 ; i++){
        for(int j = 0 ; j < 5 ; j++){
            if(G[i][j] != Fin[i][j])//只要有不像同的就return 0
                return 0;
        }
    }
    return 1;
}

//深搜回溯
void dfs(int x , int y , int Tans){//传入三个参数坐标以及步数
    if(Tans > 10) return;//大于10步的都不用搜索
    if(judge()){//如果这时候满足了，那么判断ans是否大于Tans
        if(ans > Tans) ans = Tans;
        return;
    }
    for (int i = 0; i < 8; i++) {//8个方向搜索
        if (dir[i][0]+x < 0 || dir[i][0]+x >= 5) continue;//越界就继续下一个方向 
        if (dir[i][1]+y < 0 || dir[i][1]+y >= 5) continue;//越界就继续下一个方向   
        swap(G[x][y] , G[dir[i][0]+x][dir[i][1]+y]);//将空格位置交换
        dfs(x+dir[i][0] , y+dir[i][1] , Tans+1);//递归继续搜索
        swap(G[x][y] , G[dir[i][0]+x][dir[i][1]+y]);//空格从新移回
    }
}

//主函数
int main() {
    scanf("%d%*c", &t);
    while (t--) {
        Point p;
        //处理输入
        for(int i = 0 ; i < 5 ; i++){
            for(int j = 0 ; j < 5 ; j++){
                if(j == 4) scanf("%c%*c" , &ch);
                if(j < 4)  scanf("%c" , &ch);
                if(ch == ' '){
                    G[i][j] = -1;
                    p.x = i ; p.y = j;
                }
                else G[i][j] = ch-'0';
            }
        }
        ans = 999999999; 
        dfs(p.x , p.y , 0);
        if (ans > 10)  printf("Unsolvable in less than 11 move(s).\n");
        else  printf("Solvable in %d move(s).\n", ans);
    }
    return 0;
}