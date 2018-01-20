#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int main(int argc, const char * argv[]) {
    
    freopen("/Users/smartgrid_aict/Desktop/algorithm/1202/1202/in.txt", "r", stdin);
    
    int n, k;
    cin >> n >> k;
    
    pair<int, int> j[300003];
    int bag[300003];
    
    for(int i = 0 ; i < n ; i++) {
        int w, v;
        cin >> w >> v;
        j[i] = make_pair(w, v);
    }
    
    for(int i = 0 ; i < k ; i++) {
        cin >> bag[i];
    }
    
    sort(j, j+n);
    sort(bag, bag+k);
    
//    for(int i = 0 ; i < n ; i++) {
//        cout << j[i].first << " " << j[i].second << endl;
//    }
//    
//    for(int i = 0 ; i < k ; i++) {
//        cout << bag[i] << " ";
//    }
    
    priority_queue<int> pq;
    long long ret = 0;
    int z = 0;
    for(int i = 0 ; i < k ; i++) {
        while(z < n && j[z].first <= bag[i]) {
            pq.push(j[z].second);
            z++;
        }
        if (!pq.empty()) {
            ret += pq.top();
            pq.pop();
        }
    }
    
    cout << ret << endl;
    
    return 0;
}
