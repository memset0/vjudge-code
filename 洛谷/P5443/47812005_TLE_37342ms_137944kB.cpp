#include<bits/stdc++.h>
const int Buf=1<<21; char ibuf[Buf],*iS,*iT,obuf[Buf],*oS=obuf,*oT=oS+Buf-1;
#define flush() (fwrite(obuf,1,oS-obuf,stdout),oS=obuf,void())
#define getchar() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,Buf,stdin),(iS==iT?EOF:*iS++)):*iS++)
#define putchar(x) (*oS++=(x),oS==oT?flush():void())
struct Flusher_{~Flusher_(){flush();}}flusher_;
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=1e5+10,M=5e5+10;
int n,m,q,S,ans[N],mrk[N],vis[N],anc[N],tmp[M],siz[M],_anc[N],_siz[N];
std::vector<int> ext,sta,lnk[M],vec[N],qry[M];
struct tuple{
	int a,b,c;
}edg[N],opt[N];
int find(int x){return anc[x]==x?x:anc[x]=find(anc[x]);}
int _find(int x){return _anc[x]==x?x:_anc[x]=_find(_anc[x]);}
inline void upd(int x){
	_anc[x]=find(x);
	_anc[_anc[x]]=_anc[x],_siz[_anc[x]]=siz[_anc[x]];
}
int main(){
#ifdef memset0
	freopen("2.in","r",stdin);
	freopen("2.out","w",stdout);
#endif
	read(n),read(m);
	for(int u,v,w,i=1;i<=m;i++){
		read(u),read(v),read(w);
		edg[i]={u,v,w};
	}
	read(q);
	for(int o,x,y,i=1;i<=q;i++){
		read(o),read(x),read(y);
		opt[i]={o,x,y};
		tmp[++*tmp]=y;
	}
	std::sort(tmp+1,tmp+*tmp+1);
	*tmp=std::unique(tmp+1,tmp+*tmp+1)-tmp-1;
	for(int i=1;i<=m;i++)edg[i].c=std::upper_bound(tmp+1,tmp+*tmp+1,edg[i].c)-tmp-1;
	for(int i=1;i<=q;i++)opt[i].c=std::upper_bound(tmp+1,tmp+*tmp+1,opt[i].c)-tmp-1;
	S=std::max(1,std::min(q,(int)(sqrt(q)*3)));
	for(int l=1,r=S;l<=q;l=r+1,r=std::min(q,r+S)){
		for(int i=l;i<=r;i++)if(opt[i].a==1)mrk[opt[i].b]=true;
		for(int i=1;i<=m;i++)(mrk[i]?ext:sta).push_back(i);
		for(int i=l;i<=r;i++)if(opt[i].a==1){
			edg[opt[i].b].c=opt[i].c;
		}else{
			for(int e:ext)if(edg[e].c>=opt[i].c)vec[i].push_back(e);
			qry[opt[i].c].push_back(i);
		}
		for(int e:sta)lnk[edg[e].c].push_back(e);
		for(int i=1;i<=n;i++)anc[i]=i,siz[i]=1;
		for(int i=*tmp;i>=1;i--){
			for(int e:lnk[i]){
				int a=find(edg[e].a),b=find(edg[e].b);
				if(a!=b){
					anc[a]=b;
					siz[b]+=siz[a];
				}
			}
			for(int o:qry[i]){
				upd(opt[o].b);
				for(int e:ext)upd(edg[e].a),upd(edg[e].b);
				for(int e:vec[o]){
					int a=_find(edg[e].a),b=_find(edg[e].b);
					if(a!=b){
						_anc[a]=b;
						_siz[b]+=_siz[a];
					}
				}
				ans[o]=_siz[_find(opt[o].b)];
			}
		}
		for(int e:sta)lnk[edg[e].c].clear();
		for(int i=l;i<=r;i++)if(opt[i].a==1)mrk[opt[i].b]=false;
		for(int i=l;i<=r;i++)if(opt[i].a==2)qry[opt[i].c].clear(),vec[i].clear();
		ext.clear(),sta.clear();
	}
	for(int i=1;i<=q;i++)if(opt[i].a==2)print(ans[i],'\n');
	fprintf(stderr,"clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
}