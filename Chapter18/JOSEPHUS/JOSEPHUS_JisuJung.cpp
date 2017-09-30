//
//  main.cpp
//  josephus
//
//  Created by smartgrid_aict on 2017. 9. 30..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//

#include <iostream>
#include <list>
using namespace std;

int main(int argc, const char * argv[]) {
    
    freopen("/Users/smartgrid_aict/Desktop/algorithm/josephus/josephus/input.txt", "r", stdin);
    
    int T;
    cin >> T;
    
    while(T--) {
        int n, k;
        cin >> n >> k;
        
        list<int> soldier;
        for(int i = 1 ; i <= n ; i++) soldier.push_back(i);
        
        list<int>::iterator kill = soldier.begin();
        
        while(soldier.size() > 2) {
            
            kill = soldier.erase(kill);
            // mod 역할
            if(kill == soldier.end()) {
                kill = soldier.begin();
            }
            
            for(int i = 0; i < (k-1)%n; i++) {
                kill++;
                if(kill == soldier.end()) {
                    kill = soldier.begin();
                }
            }
        }
        
        
        cout << soldier.front() << " " << soldier.back() << endl;
        //        for(kill = soilder.begin() ;kill != soilder.end(); kill++)
        //        {
        //            cout<< *kill << endl;
        //        }
        
    }
    
    return 0;
}
