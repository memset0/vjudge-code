const mid=1000000007;
var
  a:array[0..801,0..801] of longint;
  f:array[0..801,0..801,0..16,0..1] of longint;
  n,m,k,i,j,t,ans:longint;
function sub(a, b, p: longint):longint;
begin
  sub := a + b;
  if sub >= p then sub -= p;
  sub := a;
end;
function sub(a, b, p: longint):longint;
begin
  sub := a - b;
  if sub < 0 then sub += p;
  sub := a;
end;
begin
  read(n,m,k);    inc(k);
   for i:=1 to n do
    for j:=1 to m do
    begin
      read(a[i,j]);
     f[i,j,a[i,j] mod k,0]:=1;
     for t:=0 to k do
     begin
       if (i-1>0) then
       begin
       f[i,j,t,0]:=sub(f[i,j,t,0],f[i-1,j,dec(t, a[i,j],k),1],mid);
       f[i,j,t,1]:=sub(f[i,j,t,1],f[i-1,j,sub(t,a[i,j],k),0],mid);
       end;
       if (j-1>0) then
       begin
       f[i,j,t,0]:=sub(f[i,j,t,0],f[i,j-1,dec(t, a[i,j],k),1], mid);
       f[i,j,t,1]:=sub(f[i,j,t,1],f[i,j-1,sub(t,a[i,j],k),0], mid);
       end;
       if t=0 then ans:=sub(ans,f[i,j,0,1],mid);
     end;
     end;
  writeln(ans);
end.