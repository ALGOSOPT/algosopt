//
//  main.cpp
//  pinball
//
//  Created by smartgrid_aict on 2017. 9. 9..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// 2차원 벡터를 표현하는 클래스
const double PI = 2.0 * acos(0.0);

struct vector2 {
    double x, y;
    explicit vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}

    bool operator == (const vector2& rhs) const {
        return x == rhs.x && y == rhs.y;
    }
    bool operator < (const vector2& rhs) const {
        return x != rhs.x ? x < rhs.x : y < rhs.y;
    }
    vector2 operator + (const vector2& rhs) const {
        return vector2(x + rhs.x , y + rhs.y);
    }
    vector2 operator - (const vector2& rhs) const {
        return vector2(x - rhs.x , y - rhs.y);
    }
    vector2 operator * (double rhs) const {
        return vector2(x * rhs , y * rhs);
    }
    
    // 벡터 길이 반환
    double norm() const {
        return hypot(x, y);
    }
    
    // 단위벡터
    vector2 normalize() const {
        return vector2(x / norm(), y / norm());
    }
    
    // 극각도
    double polar() const { return fmod(atan2(y,x) + 2*PI, 2*PI); }
   
    double dot(const vector2& rhs) const { return x*rhs.x + y*rhs.y; }
    
    double cross(const vector2& rhs) const { return x*rhs.y - rhs.x*y; }
    
    // 사영
    // rhs.dot(*this)*(1/rhs.norm()) 를 벡터로 계산
    // 단위벡터에 단위벡터랑 내적한 값을 실수배
    vector2 project(const vector2& rhs) const {
        vector2 r =  rhs.normalize();
        return r * r.dot(*this);
        //return r * r.dot(*this);
    }
    
};

int N;
vector<vector2> center(51, vector2(0,0));
vector<int> radius(51);
const double INF = 1e200;
const double EPSILON = 1e-9;

/*
 1단계 : 공과 장애물의 충돌 시점을 찾는다. -> 2차 방정식 풀이
 2단계 : 공이 장애물과 닿았을때 반사되는 벡터를 찾는다.
 */

// 1단계 : 공과 장애물의 충돌 시점을 찾는다. -> 2차 방정식 풀이
// 근의 공식을 이용한 방정식 풀이
vector<double> calcEquation(double a, double b, double c) {
    double sub = b*b -4*a*c;
    
    if(sub < -EPSILON) return vector<double>();
    
    if(sub == EPSILON) return vector<double>(1,-b/(2*a));
    
    vector<double> ret;
    // 작은 순서로 넣음
    ret.push_back((-b - sqrt(sub)) / 2*a);
    ret.push_back((-b + sqrt(sub)) / 2*a);
    
    return ret;
}

// 각 장애물에 부딪히는 시점 반환
// 시간에 대한 방정식 풀기
double hitCircle(vector2 now, vector2 dir, vector2 center, int radius) {
    double a = dir.dot(dir);
    double b = 2*dir.dot(now-center);
    double c = center.dot(center) + now.dot(now) - 2*now.dot(center) - radius*radius;
    
    vector<double> ret = calcEquation(a, b, c);
    // 근이 없거나 음수이면 INF 반환
    if(ret.empty() || ret[0] < EPSILON) return INF;
    return ret[0];
}


// 2단계 : 공이 장애물과 닿았을때 반사되는 벡터를 찾는다.
// 벡터의 반사를 이용한 반사각 계산

// center를 중심으로 하는 장애물과 pos 위치에서 충돌했을때, 공이 반사되는 방향 반환
vector2 reflect(vector2 dir, vector2 center, vector2 pos) {
    
    // n은 법선벡터
    vector2 n = pos-center;
    vector2 projectToN = dir.project(n);
    
    // 방향이니까 정규화해서 리턴
    return (dir - projectToN * 2).normalize();
}

void simulation(vector2 now, vector2 dir) {
    dir = dir.normalize();
    int cnt = 0;
    while(cnt < 100) {
        int obs = -1;
        double time = INF;
        for(int i = 0; i < N; i++) {
            // 가장 빨리 만나는 장애물 찾기
            double cand = hitCircle(now, dir, center[i], radius[i]+1);
            if(cand < time) {
                time = cand;
                obs = i;
            }
        }
        if(obs == -1) break;
        cout << obs << " ";
        // 위치와 방향 갱신
        vector2 newNow = now + dir*time;
        dir = reflect(dir, center[obs], newNow);
        now = newNow;
        cnt++;
    }
    cout << endl;
}
int main(int argc, const char * argv[]) {
    
    freopen("/Users/smartgrid_aict/Desktop/algorithm/pinball/pinball/input.txt", "r", stdin);
    
    int T;
    cin >> T;
    
    while(T--) {
        double x, y, dirx, diry;
        cin >> x >> y >> dirx >> diry >> N;
        vector2 now = vector2(x,y);
        vector2 dir = vector2(dirx, diry);
        for(int i = 0 ; i < N; i++) {
            double xx, yy;
            cin >> xx >> yy >> radius[i];
            center[i] = vector2(xx, yy);
        }
        
//        cout << now.x << now.y << dir.x << dir.y << endl;
//        
//        for(int i = 0 ; i < N; i++) {
//            cout << center[i].x << center[i].y << endl;
//        }
//        
        simulation(now, dir);
        
    }
    return 0;
}
















