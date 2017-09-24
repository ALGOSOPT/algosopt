//
//  main.cpp
//  2170
//
//  Created by smartgrid_aict on 2017. 9. 24..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

int main(int argc, const char * argv[]) {
    
    freopen("/Users/smartgrid_aict/Desktop/algorithm/2170/2170/input.txt", "r", stdin);
    
    int N;
    cin >> N;
    typedef pair<ll, int> Event;
    vector<Event> event;
    for(int i = 0; i < N; i++) {
        ll a, b;
        cin >> a >> b;
        event.push_back(make_pair(a, 1));
        event.push_back(make_pair(b, -1));
       // lines.push_back(make_pair(a, b));
    }
    
    sort(event.begin(), event.end());
    
    ll ret = 0;
    int count = 1;
    for(int i = 1; i < event.size(); i++) {
        ll x = event[i].first;
        int delta = event[i].second;
        
        if(count > 0) {
            ret += x - event[i-1].first;
        }
        count += delta;
    }
    
    cout << ret << endl;
    return 0;
}
