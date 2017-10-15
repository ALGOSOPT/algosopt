//
//  main.cpp
//  5397
//
//  Created by smartgrid_aict on 2017. 10. 14..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//

#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main(int argc, const char * argv[]) {
    
    int T;
    cin >> T;
    
    while(T--) {
        string str;
        cin >> str;
        stack<char> pw, temp;
        for(int i = 0 ; i < str.size() ; i++) {
            char c = str[i];
            if(c == '<') {
                if(!pw.empty()) {
                    temp.push(pw.top());
                    pw.pop();
                }
            } else if(c == '>') {
                if(!temp.empty()) {
                    pw.push(temp.top());
                    temp.pop();
                }
                
            } else if(c == '-') {
                if(!pw.empty()) {
                    pw.pop();
                }
            } else {
                pw.push(c);
            }
        }
        
        while(!temp.empty()) {
            pw.push(temp.top());
            temp.pop();
        }
        
        int len = (int)pw.size();
        string ret;
        for(int i = 0 ; i < len; i++) {
            ret += pw.top();
            pw.pop();
        }
        
        for(int i = len-1 ; i >= 0; i--) {
            cout << ret[i];
        }
        
        cout << endl;
    }
    return 0;
}
