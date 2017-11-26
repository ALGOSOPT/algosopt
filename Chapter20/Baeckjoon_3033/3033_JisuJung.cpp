//
//  main.cpp
//  3033
//
//  Created by smartgrid_aict on 2017. 11. 26..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//
#include <iostream>
#include<vector>
#include <string>
#include<algorithm>
using namespace std;

#define MAX 500005
vector<int> suff;
vector<int> lcp(MAX);
int N;

struct Comparator {
    const vector<int>& group;
    int t;
    
    Comparator(const vector<int>& _group, int _h) : group(_group), t(_h) { }
    
    bool operator () (int a, int b) {
        if(group[a] != group[b]) return group[a] < group[b];
        return group[a + t] < group[b + t];
    }
};

vector<int> getSuffixArray(const string& s) {
   
    int t = 1;
    vector<int> group(N+1);
    for(int i = 0; i < N; i++) group[i] = s[i];
    group[N] = -1;
    
    vector<int> perm(N);
    for(int i = 0; i < N; i++) perm[i] = i;
    
    while(t < N) {
        Comparator compareUsing2T(group, t);
        sort(perm.begin(), perm.end(), compareUsing2T);
        
        t *= 2;
        if(t >= N) break;
        
        vector<int> newGroup(N+1);
        newGroup[N] = -1;
        newGroup[perm[0]] = 0;
        for(int i = 1; i < N; i++)
            if(compareUsing2T(perm[i-1], perm[i]))
                newGroup[perm[i]] = newGroup[perm[i-1]] + 1;
            else
                newGroup[perm[i]] = newGroup[perm[i-1]];
        group = newGroup;
    }
    return perm;
}

int commonPrefix(const string& s, int i, int j) {
    int k = 0;
    while(i < s.size() && j < s.size() && s[i] == s[j]) { ++i; ++j; ++k; }
    return k;
}

vector<int> countSubstrings(const string& s) {
    vector<int> a = getSuffixArray(s);
    vector<int> ret;
    for(int i = 0; i < a.size(); ++i) {
        int cp = 0;
        if(i > 0) {
            cp = commonPrefix(s, a[i-1], a[i]);
            ret.push_back(cp);
        }
    }
    return ret;
}

void LCP(const string& s) {
    // rank : 접미사 배열의 순서
    int k = 0, j = 0;
    vector <int> rank(N+1,0);
    for (int i = 0 ; i < N ; i++) rank[suff[i]] = i;
    for (int i = 0 ; i < N ; lcp[rank[i++]] = k)
        for (k ? k-- : 0 , j = suff[rank[i]-1] ; s[i+k] == s[j+k] ; k++);
}

void LCP2(const string& s) {
    // rank : 접미사 배열의 순서
    vector <int> rank(N+1,0);
    for (int i = 0 ; i < N ; i++) rank[suff[i]] = i;
    int len = 0;
    
    for (int i = 0; i < N; i++)
    {
        int k = rank[i];
        if (k)
        {
            int j = suff[k - 1];
            
            while (s[j + len] == s[i + len])
                len++;
            
            lcp[k] = len;
            
            if (len)
                len--;
        }
    }
}

int main(int argc, const char * argv[]) {

    string in;
    cin >> N >> in;
    
    suff = getSuffixArray(in);
    LCP2(in);
    int ret = 0;
    for(int i = 1; i < in.size(); i++ ) {
        ret = max(ret, lcp[i]);
    }
    cout << ret << endl;
    
    
    return 0;
}
