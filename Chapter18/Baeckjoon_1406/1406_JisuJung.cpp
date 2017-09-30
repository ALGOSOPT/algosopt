//
//  main.cpp
//  1406
//
//  Created by smartgrid_aict on 2017. 9. 30..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//

#include <iostream>
#include <string>
#include <list>
using namespace std;

int main(int argc, const char * argv[]) {

    freopen("/Users/smartgrid_aict/Desktop/algorithm/1406/1406/input.txt", "r", stdin);

    string str;
    cin >> str;
    
    list<char> str_list;
    list<char>::iterator itr;
    for(int i = 0 ; i < str.size(); i++) {
        str_list.push_back(str[i]);
    }
    
    itr = str_list.end();
    
    int n;
    cin >> n;
    for(int i = 0 ; i < n ; i++) {
        char c;
        cin >> c;
        if(itr != str_list.begin() && c == 'L') {
            itr--;
        } else if(itr != str_list.end() && c == 'D') {
            itr++;
        } else if(itr != str_list.begin() && c == 'B') {
            itr = str_list.erase(--itr);
        } else if(c == 'P') {
            char temp;
            cin >> temp;
            // 새롭게 insert된 문자열의 첫번째 인덱스 리턴
            str_list.insert(itr, temp);
        }
    }
    
    for(itr = str_list.begin(); itr != str_list.end(); itr++) {
        cout << *itr ;
    }
    return 0;
}
