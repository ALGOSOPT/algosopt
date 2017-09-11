//
//  main.cpp
//  allergy
//
//  Created by smartgrid_aict on 2017. 7. 23..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//


#include<map>
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
#include <bitset>
#include<algorithm>
#include <functional>

using namespace std;

int n, m;
vector<int> food(50);
vector<int> personEatFood(50);
vector<pair<int, int> > forFoodSort;

int best;
// chosen: 지금까지 선택한 음식의 수
// edible: 지금까지 선택한 음식 중 각 인덱스의 친구가 먹을 음식이 있는가?
void search(long long edible, int chosen) {
    // 간단한 가지치기
    if(chosen >= best) return;
    
    // 아직 먹을 음식이 없는 첫 번째 친구를 찾는다
    int first = 0;
    while(first < n && (edible&(1<<first))) ++first;
    
    // 모든 친구가 먹을 음식이 있는 경우 종료한다
    if(first == n) { best = chosen; return; }
    
    // 이 친구가 먹을 수 있는 음식중 가장 많은 사람이 먹을 수 있는 음식을 하나 만든다.
    for(int i = 0; i < m; ++i) {
        int bestFood = forFoodSort[i].second;
        if(personEatFood[first] & (1<<bestFood)) {
            for(int j = 0; j < n; ++j) {
                // bestFood를 먹을 수 있는 친구들의 비트를 켠다.
                if(food[bestFood] & (1<<j)) edible = (1<<j)|edible;
            }
            search(edible, chosen+1);
            for(int j = 0; j < n; ++j) {
                // bestFood를 먹을 수 있는 친구들의 비트를 끈다.
                if(food[bestFood] & (1<<j)) edible = ~(1<<j)&edible;
            }
            
        }
    }
    
}

int solve() {
    long long edible = 0;
    best = m;
    search(edible, 0);
    return best;
}

// edible 인자를 int 비트마스크로 바꾼다.
// 같은 음식을 먹을 수 있는 사람들의 부분집합을 제외한다.
// 많이 먹는 사람 순으로 검사한다.
// 자료 구조를 바꾼다.


int main() {
    
    freopen("/Users/smartgrid_aict/Desktop/algorithm/allergy/allergy/input.txt", "r", stdin);
    
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
        //    친구  음식
        cin >> n >> m;
        
        food.clear();
        personEatFood.clear();
        
    
        // 이름을 인덱스로 저장
        map<string, int> names;
        for(int i = 0; i < n; i++) {
            string name;
            cin >> name;
            names[name] = i;
        }
        
        // 음식을 먹을 수 있는 사람을 비트 자리로 저장
        
        // 하나를 기준으로 부분집합인지 검사
        // 각 음식의 부분집합을 제외한다.
        
        for(int i = 0; i < m; i++) {
            int people;
            cin >> people;
            forFoodSort.push_back(make_pair(-people, i));
            for(int j = 0; j < people; j++) {
                string name;
                cin >> name;
                int eater = names[name];
                // 음식을 먹을 수 있는 사람의 비트를 켬
                food[i] |= (1<<eater);
                // 이 사람이 먹을 수 있는 음식의 비트를 켬
                personEatFood[eater] |= (1<<i);
                // 각 음식을 먹을 수 있는 사람을 번호로 저장 -> food[i]로 대체
                //eaters[i].push_back(eater);
                // 각 사람이 먹을 수 있는 음식을 번호로 저장 -> personEatFood[eater]로 대체
                //canEat[eater].push_back(i);
            }
        }
        
        // 부분집합 삭제
        
        // 기준을 정한다.
        // 이 수를 기준으로 이 수의 부분집합인지 아닌지 판단한다.
        for(int i = 0; i < m ; i++) {
            // 2의 기준 음식을 좋아하는 사람수 승 만큼 검사(부분집합)
            for(int j = 0 ; j < m ; j++) {
                // food[j]가 food[i]의 부분집합 인지 아닌지
                if(j!=i && (food[i]&food[j])==food[j]) {
                    // 부분 집합이면 가장 마지막 원소를 복사해주고 음식 원소 개수 -1 한다.
                    // (원소 삭제)
                    food[j] = 0;
                    // 그 음식 빼주기
                    for(int k = 0 ; k < n ; k++) {
                        personEatFood[k] = personEatFood[k] & ~(1<<j);
                    }
                }
            }
        }
        
        
        // 많은 사람이 좋아하는 순서대로 정렬
        sort(forFoodSort.begin(), forFoodSort.end());
        
        cout << solve() << endl;
    }
    return 0;
}
