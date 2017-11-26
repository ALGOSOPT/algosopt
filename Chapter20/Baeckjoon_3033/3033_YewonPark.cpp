#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
struct Comparator{
	const vector<int>& group;
	int t;
	Comparator(const vector<int>& _group, int _t):group(_group), t(_t){
		t = _t;
	}
	bool operator()(int a, int b){
		if(group[a] != group[b])
			return group[a] < group[b];
		return group[a+t] < group[b+t];
	}
};

vector<int> getSuffixArray(const string& s){
	int n = s.size();
	
	int t = 1;
	vector<int> group(n+1);
	for(int i=0; i<n; i++)
		group[i] = s[i];
	group[n] = -1;
	
	vector<int> perm(n);
	for(int i=0; i<n; i++)
		perm[i] = i;
	
	while(t<n){
		Comparator compareUsing2T(group, t);
		sort(perm.begin(), perm.end(), compareUsing2T);
		
		t*=2;
		if(t>=n)
			break;
			
		vector<int> newGroup(n+1);
		newGroup[n] = -1;
		newGroup[perm[0]] = 0;
		for(int i=1; i<n; i++)
			if(compareUsing2T(perm[i-1], perm[i]))
				newGroup[perm[i]] = newGroup[perm[i-1]] + 1;
			else
				newGroup[perm[i]] = newGroup[perm[i-1]];
		group = newGroup;
	}
	return perm;
}
/*
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
}*/
//공통접두사의 최대길이 계산
int commonPrefix(const string& s, int i, int j){
    int k=0; 
    while(i<s.size() && j<s.size() && s[i] == s[j]){
        ++i; ++j; ++k;
    }
    
    return k;
}int main(){
        
        int l;
        cin >> l;
        
        string input;
        cin >> input;
        
        //접미사배열 만듦
        vector<int> suf= getSuffixArray(input);
        int CL[5000]={0, };
        int count = 0;
        int max = 0;
        for(int i=0; i<input.size(); ++i){
            if(i==0)
                continue;
            int result = commonPrefix(input, suf[i-1], suf[i]);
            CL[i] = result;
            if(result == 0){
                count = 0;
                continue;
            }else{
                count++;
                if(count>=1)
                    if(max<CL[i])
                        max = CL[i];
            }
        }
        cout << max;
        
    return 0;
}

