#include <iostream>
#include <cstring>
using  namespace std;
int n, k;
int a[100002];
struct queue1 {//单调增队列 
    int head1, tail1; 
    int q[100002];
    queue1() {
        head1 = 1,tail1 = 0;
        memset(q, 0, sizeof(q));
    }
    void pop() {
        head1++;
    }
    void push(int x) {
        while(x < q[tail1] && head1 <= tail1) {
            tail1--;
            if(tail1 < head1){
            } 
        }
        tail1++;
        q[tail1] = x;
    }
    int front(){
        return q[head1];
    }
};
struct queue2 {//单调减队列 
    int head2 , tail2 ; 
    int q[100002];
    queue2() {
        head2 = 1,tail2 = 0;
        memset(q, 0, sizeof(q));
    }
    void push(int x) {
        while(x > q[tail2] && head2 <= tail2) {
            tail2--;
        }
        tail2++;
        q[tail2] = x;
    }
    void pop() {
        head2++;
    }
    int front(){
        return q[head2];
    }
};
int main() {
    cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    queue1 q1;
    for(int i = 1; i <= k; i++) {
        q1.push(a[i]);
    }
    cout <<q1.front() <<" ";
    for(int i = k + 1; i <= n; i++) {
        q1.push(a[i]);
        if(q1.tail1 - q1.head1 > 2 || (a[i] != q1.front() && a[i - 1] != q1.front() && a[i - 2] != q1.front()))q1.pop();
        cout << q1.front() << " ";
    }
    cout << endl;

    queue2 q2;  
    for(int i = 1; i <= k; i++) {
        q2.push(a[i]);
    }
    cout <<q2.front() <<" ";
    for(int i = k + 1; i <= n; i++) {
        q2.push(a[i]);
        if(q2.tail2 - q2.head2 > 2 || (a[i] != q2.front() && a[i - 1] != q2.front() && a[i - 2] != q2.front()))q2.pop();
        cout << q2.front() << " ";
    }
    cout << endl;

    return 0;
} 