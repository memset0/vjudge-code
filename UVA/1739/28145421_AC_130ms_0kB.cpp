#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
struct _2{
string _3[7];
_2(string a="",string b="",string c="",string d="",string e="",string f="",string g=""){
_3[0]=a,_3[1]=b,_3[2]=c,_3[3]=d,_3[4]=e,_3[5]=f,_3[6]=g;
}
_2 operator+(const _2 &o) const{
_2 ret;
for(int i=0;i<7;++i)
ret._3[i]=_3[i]+o._3[i];
return ret;
}
bool operator==(const _2 &o) const{
for(int i=0;i<7;++i)
if(_3[i]!=o._3[i])return false;
return true;
}
_2 piece(int from,int _size){
_2 ret;
for(int i=0;i<7;++i)
ret._3[i]=_3[i].substr(from,_size);
return ret;
}
void read(){
for(int i=0;i<7;++i)
cin>>_3[i];
}
void print(){
for(int i=0;i<7;++i)cout<<_3[i]<<endl;
}
};
_2 _4[12],Colon,Space;
inline void buildPiece(){
_4[0]=_2(".XX.","X..X","X..X","....","X..X","X..X",".XX.");
_4[1]=_2("....","...X","...X","....","...X","...X","....");
_4[2]=_2(".XX.","...X","...X",".XX.","X...","X...",".XX.");
_4[3]=_2(".XX.","...X","...X",".XX.","...X","...X",".XX.");
_4[4]=_2("....","X..X","X..X",".XX.","...X","...X","....");
_4[5]=_2(".XX.","X...","X...",".XX.","...X","...X",".XX.");
_4[6]=_2(".XX.","X...","X...",".XX.","X..X","X..X",".XX.");
_4[7]=_2(".XX.","...X","...X","....","...X","...X","....");
_4[8]=_2(".XX.","X..X","X..X",".XX.","X..X","X..X",".XX.");
_4[9]=_2(".XX.","X..X","X..X",".XX.","...X","...X",".XX.");
_4[10]=_2("....","....","....","....","....","....","....");
Colon=_2(".",".","X",".","X",".",".");
Space=_2(".",".",".",".",".",".",".");
}
int n;
_2 a[110];
_2 timetable[1550];
inline void _5(int timeline,_2 &s){//0到1439
timeline%=1440;
int h=timeline/60,m=timeline%60;
int t1=h/10?h/10:10,t2=h%10,t3=m/10,t4=m%10;
s=_4[t1]+Space+_4[t2]+Space+Colon+Space+_4[t3]+Space+_4[t4];
}
inline void initTimeTable(){
for(int i=0;i<=1540;++i)
_5(i,timetable[i]);
}
enum result{unknown,_7,normal,breakdown_1,breakdown_0};
struct _9{
result _6[8][22];
_9(){
memset(_6,0,sizeof(_6));
_6[0][0]=_6[0][3]=_6[0][4]=_6[0][5]=_6[0][8]=_6[0][9]=_6[0][10]=_6[0][11]=_6[0][12]=_6[0][15]=_6[0][16]=_6[0][17]=_6[0][20]=_7;
_6[1][1]=_6[1][2]=_6[1][4]=_6[1][6]=_6[1][7]=_6[1][9]=_6[1][10]=_6[1][11]=_6[1][13]=_6[1][14]=_6[1][16]=_6[1][18]=_6[1][19]=_7;
_6[2][1]=_6[2][2]=_6[2][4]=_6[2][6]=_6[2][7]=_6[2][9]=_6[2][11]=_6[2][13]=_6[2][14]=_6[2][16]=_6[2][18]=_6[2][19]=_7;
_6[3][0]=_6[3][3]=_6[3][4]=_6[3][5]=_6[3][8]=_6[3][9]=_6[3][10]=_6[3][11]=_6[3][12]=_6[3][15]=_6[3][16]=_6[3][17]=_6[3][20]=_7;
_6[4][1]=_6[4][2]=_6[4][4]=_6[4][6]=_6[4][7]=_6[4][9]=_6[4][11]=_6[4][13]=_6[4][14]=_6[4][16]=_6[4][18]=_6[4][19]=_7;
_6[5][1]=_6[5][2]=_6[5][4]=_6[5][6]=_6[5][7]=_6[5][9]=_6[5][10]=_6[5][11]=_6[5][13]=_6[5][14]=_6[5][16]=_6[5][18]=_6[5][19]=_7;
_6[6][0]=_6[6][3]=_6[6][4]=_6[6][5]=_6[6][8]=_6[6][9]=_6[6][10]=_6[6][11]=_6[6][12]=_6[6][15]=_6[6][16]=_6[6][17]=_6[6][20]=_7;
}
_9 operator^(const _9 &o) const{
_9 ret=_9();
for(int i=0;i<7;++i)
for(int j=0;j<21;++j)
ret._6[i][j]=(this->_6[i][j]==o._6[i][j])?this->_6[i][j]:unknown;
return ret;
}
inline void print(){
for(int i=0;i<7;++i){
for(int j=0;j<21;++j){
switch(_6[i][j]){
case unknown:putchar('?');
break;
case _7:putchar('.');
break;
case normal:putchar('W');
break;
case breakdown_0:putchar('0');
break;
case breakdown_1:putchar('1');
break;
default:break;
}
}
putchar('\n');
}
}
};
_9 _1[1450];
int legal_size;
bool _8[8][22],occur[2][8][22];
inline void buildOccur(){
for(int k=0;k<n;++k){
for(int i=0;i<7;++i){
for(int j=0;j<21;++j){
int num=a[k]._3[i][j]=='X';
occur[num][i][j]=true;
}
}
}
}
inline bool parse(int s){
memset(_8,0,sizeof(_8));
for(int k=0;k<n;++k){
for(int i=0;i<7;++i){
for(int j=0;j<21;++j){
if(timetable[k+s]._3[i][j]!=a[k]._3[i][j]){
_8[i][j]=true;
if(occur[0][i][j]&&occur[1][i][j]&&_8[i][j])
return false;
}
}
}
}
return true;
}
_9 get_ans(){
_9 ret=_9();
for(int i=0;i<7;++i){
for(int j=0;j<21;++j){
if(ret._6[i][j]==_7)continue;
if(_8[i][j])
ret._6[i][j]=occur[0][i][j]?breakdown_0:breakdown_1;
else if(occur[0][i][j]&&occur[1][i][j])
ret._6[i][j]=normal;
else ret._6[i][j]=unknown;
}
}
return ret;
}
inline void init(){
for(int i=0;i<=100;++i) a[i]=_2();
memset(_1,0,sizeof(_1));
memset(occur,0,sizeof(occur));
legal_size=0;
}
int main(){
ios::sync_with_stdio(false);
cin.tie(0),cout.tie(0);
buildPiece();
initTimeTable();
while(cin>>n){
init();
for(int i=0;i<n;++i)
a[i].read();
buildOccur();
for(int i=0;i<1440;++i)
if(parse(i))
_1[++legal_size]=get_ans();
if(legal_size==0)puts("impossible");
else{
for(int i=2;i<=legal_size;++i)
_1[1]=_1[1]^_1[i];
_1[1].print();
}
}
}