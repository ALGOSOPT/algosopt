//
//  main.cpp
//  BRACKETS2
//
//  Created by smartgrid_aict on 2017. 10. 14..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//

#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main(int argc, const char * argv[]) {

    freopen("/Users/smartgrid_aict/Desktop/algorithm/BRACKETS2/BRACKETS2/input.txt", "r", stdin);
    
    int N;
    string str;
    
    cin >> N;
    
    for(int i = 0; i < N; i++) {
        cin >> str;
        
        stack<char> brackets;
        
        bool right = true;
        
        for(int j = 0 ; j < str.size(); j++) {
            char b = str[j];
            if(b == '(' || b == '{' || b == '[')
                brackets.push(b);
            else if (brackets.empty()) {
                right = false;
                break;
            } else {
                char t = brackets.top();
                if((t == '(' && b == ')') || (t == '{' && b == '}') || (t == '[' && b == ']'))
                    brackets.pop();
                else {
                    right = false;
                    break;
                }
            }
        }
        
        if(!right || !brackets.empty()) cout << "NO" << endl;
        else cout << "YES" << endl;
    }
    
    return 0;
}
