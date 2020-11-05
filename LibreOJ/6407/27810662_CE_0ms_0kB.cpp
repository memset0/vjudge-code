
bool verify(double len,double sh,double eh,vector<point> tem){
  vector<point> lim;
  sort(tem.begin(),tem.end());
  for(int i=0;i<tem.size();i++){
    if(i+1!=tem.size()&&tem[i].x==tem[i+1].x)continue;
    tem[i].y-=sh;
    if(tem[i].y<0)continue;
    lim.push_back(tem[i]);
  }
  return true;
}