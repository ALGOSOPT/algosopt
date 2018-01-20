#include <iostream>
#include <queue>
using namespace std;

int main(int argc, const char * argv[]) {
    
    //freopen("/Users/smartgrid_aict/Desktop/algorithm/1715/1715/input.txt", "r", stdin);
    
    int n;
    cin >> n;
    priority_queue<int> pq;
    
    for(int i = 0 ; i < n ; i++) {
        int t = 0;
        cin >> t;
        if(n == 1) {
            cout << 0 << endl;
            return 0;
        }
        pq.push(-t);
    }
    
    int ret = 0;
    
    while(pq.size() > 1) {
        int temp = 0;
        int t1 = pq.top(); pq.pop();
        int t2 = pq.top(); pq.pop();
        temp = t1 + t2;
        ret += temp;
        pq.push(temp);
    }
    
    cout << -ret << endl;
    return 0;
}
