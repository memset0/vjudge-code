namespace MAIN{
    int n,q;
    LL a[N],x;
    int sum[N*120],son[N*120][2],tot,rt[N];
    inline void del(res rt,const RG LL &X){
        res now=rt;
        for(res i=60;~i;i--)sum[now]--,now=son[now][int((X>>i)&1)];
        sum[now]--;
    }
    inline void insert(res &rt,const RG LL &X){
        if(!rt)rt=++tot;
        res now=rt;
        for(res i=60;~i;i--){
            sum[now]++;
            res c=int((X>>i)&1);
            if(!son[now][c])son[now][c]=++tot;
            now=son[now][c];
        }
        sum[now]++;
    }
    int solve(res a,res b,res dep){
        if(!a||!b)return 0;
        if(dep==-1)return 0;
        res a0=son[a][0],a1=son[a][1],b0=son[b][0],b1=son[b][1];
        if((x>>dep)&1)return solve(a0,b1,dep-1)+solve(a1,b0,dep-1);
        if((sum[a0]<sum[b1])==(sum[a1]<sum[b0]))return min(sum[a],sum[b]);
        if(sum[a0]<sum[b1])return min(solve(a1,b1,dep-1),min(sum[b1]-sum[a0],sum[a1]-sum[b0]))+sum[a0]+sum[b0];
        return min(solve(a0,b0,dep-1),min(sum[a0]-sum[b1],sum[b0]-sum[a1]))+sum[a1]+sum[b1];
    }
    LL id[N];
    pair<LL,int> b[N];
    int t,pos[N],Ans[N],num[N];
    multiset<int> ans,an;
    map<LL,int> M;
    inline void del(const res &I){
        auto it=M.find(id[I]);
        it++;
        if(it!=M.end())if((*it).fi^id[I]==1&&Ans[I]!=-1)ans.erase(ans.find(Ans[I])),Ans[I]=-1;
        it--;
        if(it!=M.begin()){it--;if((*it).fi^id[I]==1&&Ans[(*it).se]!=-1)ans.erase(ans.find(Ans[(*it).se])),Ans[(*it).se]=-1;}
    }
    inline void ins(const res &I){
        auto it=M.find(id[I]);
        it++;
        if(it!=M.end())if((*it).fi^id[I]==1)ans.insert(Ans[I]=num[I]+num[(*it).se]-solve(rt[I],rt[(*it).se],60));
        it--;
        if(it!=M.begin()){it--;if((*it).fi^id[I]==1)ans.insert(Ans[(*it).se]=num[I]+num[(*it).se]-solve(rt[(*it).se],rt[I],60));}
    }
    inline void MAIN(){
        n=read(),q=read(),x=Read();
        if(!x){
            for(res i=0;i<=q;i++)puts("1");
            return;
        }
        for(res i=1;i<=n;i++)a[i]=Read(),b[i]=mp(a[i],i);
        sort(b+1,b+n+1);
        RG LL pw=Qpow(2,int(log2(x)));
        for(res i=1;i<=n;){
            res j=i;
            while(b[j].fi/pw==b[i].fi/pw&&j<=n)j++;
            j--,id[++t]=b[i].fi/pw,num[t]=j-i+1,M[id[t]]=t;
            for(res k=i;k<=j;k++)pos[b[k].se]=t,insert(rt[t],b[k].fi);
            i=j+1,an.insert(num[t]);
        }
        for(res i=1;i<t;i++){
            if((id[i]^id[i+1])!=1){Ans[i]=-1;continue;}
            ans.insert(Ans[i]=num[i]+num[i+1]-solve(rt[i],rt[i+1],60));
        }
        if(!ans.size())printf("%d\n",(*--an.end()));
        else printf("%d\n",max((*--ans.end()),(*--an.end())));
        while(q--){
            res p=read();
            RG LL va=Read();
            res po=pos[p];
            del(po),del(rt[po],a[p]);
            if(a[p]/pw==va/pw)a[p]=va,insert(rt[po],a[p]),ins(po);
            else {
                num[po]--,ins(po),a[p]=va,an.erase(an.find(num[po]+1)),an.insert(num[po]);
                if(M.count(a[p]/pw)){
                    res I=M[a[p]/pw];
                    pos[p]=I,del(I),num[I]++,insert(rt[I],a[p]),ins(I),an.erase(an.find(num[I]-1)),an.insert(num[I]);
                }
                else {
                    id[++t]=a[p]/pw,pos[p]=t,M[id[t]]=t,num[t]++,insert(rt[t],a[p]),ins(t),an.insert(1);
                }
            }
            if(!ans.size())printf("%d\n",(*--an.end()));
            else printf("%d\n",max((*--ans.end()),(*--an.end())));
        }
    }
}
int main(){
//    srand(19260817);
    MAIN::MAIN();
//    Ot();
    return 0;
}