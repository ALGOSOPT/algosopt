#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>

using namespace std;

struct SuffixComparator{
    const string& s;
    SuffixComparator(const string& s) : s(s) {}
    bool operator()(int i, int j){
        return strcmp(s.c_str() + i, s.c_str() + j)<0;
    }
};

vector<int> getSuffixArray(const string& s){
    vector<int> perm;
    for(int i=0; i<s.size(); ++i)
        perm.push_back(i);
    sort(perm.begin(), perm.end(), SuffixComparator(s));
    return perm;
}

int main(){
        
        string input;
        cin >> input;
        
        //접미사배열 만듦
        vector<int> suf= getSuffixArray(input);
        for(int i=0; i<input.size(); i++){
        	cout << input.substr(suf[i]);
        	cout << "\n";
		}
        
    return 0;
}

