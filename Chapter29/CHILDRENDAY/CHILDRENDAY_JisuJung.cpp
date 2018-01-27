//
//  main.cpp
//  childrenday
//
//  Created by smartgrid_aict on 2018. 1. 26..
//  Copyright © 2018년 smartgrid_aict. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
using namespace std;
int n, m;
string d;
int append(int here, int edge, int mod) {
    int there = here * 10 + edge;
    if (there >= mod)
        return mod + there % mod;
    return there % mod;
}

string gifts(string digits, int n, int m) {
    sort(digits.begin(), digits.end());
    vector<int> parent(2 * n, -1);
    vector<int> choice(2 * n, -1);
    queue<int> q;
    parent[0] = 0;
    q.push(0);
    while (!q.empty()) {
        int here = q.front();
        q.pop();
        for (int i = 0; i < digits.size(); i++) {
            int there = append(here, digits[i] - '0', n);
            if (parent[there] == -1) {
                parent[there] = here;
                choice[there] = digits[i] - '0';
                q.push(there);
            }
        }
    }
    
    if (parent[n + m] == -1)
        return "IMPOSSIBLE";
    string ret;
    int here = n + m;
    while (parent[here] != here) {
        ret += char('0' + choice[here]);
        here = parent[here];
    }
    
    reverse(ret.begin(), ret.end());
    return ret;
}

int main() {
    
    freopen("/Users/smartgrid_aict/Desktop/algorithm/childrenday/childrenday/input.txt", "r", stdin);
    int T;
    cin >> T;
    while(T--) {
        cin >> d >> n >> m;
        cout << gifts(d, n, m) << endl;
    }
    return 0;
}
