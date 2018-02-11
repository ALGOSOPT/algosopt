//
//  main.cpp
//  dictionary
//
//  Created by jeongji su on 2018. 2. 10..
//  Copyright © 2018년 jeongji su. All rights reserved.
//

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

vector<int> seen,order;
vector<vector<int>> adj;

void makegraph(vector<string>& words) {
    adj = vector<vector<int> >(26, vector<int>(26,0));
    
    for(int j = 1; j < words.size(); j++) {
        int i = j-1;
        int len = min(words[i].size(), words[j].size());
        for(int k = 0; k < len; k++) {
            if(words[i][k] != words[j][k]) {
                int a = words[i][k]-'a';
                int b = words[j][k]-'a';
                adj[a][b] = 1;
                break;
                
            }
        }
    }
}

void dfs(int here) {
    seen[here] = 1;
    for(int there = 0; there < adj.size(); there++) {
        if(adj[here][there] && !seen[there]) dfs(there);
    }
    order.push_back(here);
    
}

vector<int> topologicalsort() {
    
    int n = adj.size();
    seen = vector<int>(n, 0);
    order.clear();
    for(int i = 0; i < n; i++)
        if(!seen[i]) dfs(i);
    
    reverse(order.begin(), order.end());
    
    for(int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++)
            if(adj[order[j]][order[i]])
                return vector<int>();
    return order;
}


int main(int argc, const char * argv[]) {
    

    freopen("/Users/JUNGJISU/Desktop/C++/dictionary/dictionary/in.txt", "r", stdin);

    int T;
    cin >> T;
    while(T--) {
        vector<string> words;
        int n;
        cin >> n;
        vector<int> ts;
        
        for(int i = 0; i < n; i++) {
            string t;
            cin >> t;
            words.push_back(t);
            
        }
        
        makegraph(words);
        ts = topologicalsort();
        
        if(ts.empty())
            cout << "INVALID HYPOTHESIS" ;
        else {
            for(int n = 0; n < adj.size(); n++) {
                char c = ts[n]+'a';
                cout << c ;
            }
        }
        cout << endl;
        
    }
}
