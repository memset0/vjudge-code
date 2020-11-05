#include <cstdio>
#include <vector>

int n;
struct point{
    int x,y,c;
};
std::vector<point>vec;
int cnt;
void set(int x,int y,int c){
    ++cnt;
    printf("%d %d %d\n",x,y,c);
}
int main(){
//    freopen("out.txt","w",stdout);
    scanf("%d",&n);
    ++n;
    vec.push_back((point){0,0,0});
    for(int i=1;i<=n;i++){
        for(int j=0;j<vec.size();j++){
            --vec[j].y;
            ++vec[j].c;
            if(n<=50||((vec[j].x<((n-i)<<1))&&vec[j].x>(i-n)<<1))set(vec[j].x,vec[j].y,vec[j].c);
        }
        for(int k=-i,l=(-i)<<1;k<=(i<<1);k+=3,++l)
            vec.push_back((point){k,l,0});
    }
//    fprintf(stderr,"%d\n",cnt);
} //12313213123