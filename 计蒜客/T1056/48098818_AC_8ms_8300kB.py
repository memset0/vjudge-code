n=int(input())
sa,sb,sc=0,0,0
for _ in range(n):
    a,b,c=map(int,input().split())
    sa+=a
    sb+=b
    sc+=c
print(sa,sb,sc,sa+sb+sc)