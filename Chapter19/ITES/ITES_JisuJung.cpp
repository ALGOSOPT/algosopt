//
//  main.cpp
//  ITES
//
//  Created by smartgrid_aict on 2017. 10. 14..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <queue>
using namespace std;
// N 은 개수
#define ll long long
int N, K;

ll makeNext(ll pre) {
    ll now = 0;
    now = ((pre * 214013 + 2531011) % (ll)pow(2,32));
    return now;
}

int main(int argc, const char * argv[]) {
    
    freopen("/Users/smartgrid_aict/Desktop/algorithm/ITES/ITES/input.txt", "r", stdin);
    int T;
    cin >> T;
    while(T--) {
        cin >> K >> N;
        queue<int> q;
        int ret = 0, sum = 0; ll num = 1983;
        for(int i = 0 ; i < N ; i++) {
            int signal = num % 10000+1;
            sum += signal;
            q.push(signal);
            while(sum > K) {
                sum -= q.front();
                q.pop();
            }
            
            if(sum == K) ret++;
            
            num = makeNext(num);
        }
        
        cout << ret << endl;
    }
    return 0;
}
