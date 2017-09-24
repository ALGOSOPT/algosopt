//
//  main.cpp
//  2699
//
//  Created by smartgrid_aict on 2017. 9. 24..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// 2차원 벡터를 표현하는 클래스
const double PI = 2.0 * acos(0.0);

struct vector2 {
    double x, y;
    explicit vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_){}
    
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

typedef vector<vector2> poly;

double ccw(vector2 a, vector2 b) {
    return a.cross(b);
}

// 점 p를 기준으로 b가 a의 반시계 방향이면 양수, 시계 방향이면 음수
double ccw(vector2 p, vector2 a, vector2 b) {
    return ccw(a-p, b-p);
}

poly giftWrap(const vector<vector2>& points) {
    int n = points.size();
    
    poly hull;
    vector2 pivot = points[0];
    for(int i = 1; i < points.size() ; i++) {
        if(points[i].y > pivot.y) {
            pivot = points[i];
        } else if(points[i].y == pivot.y && points[i].x < pivot.x) {
            pivot = points[i];
        }
    }
    
    hull.push_back(pivot);
    
    while(true) {
        vector2 ph = hull.back(), next = points[0];
        for(int i = 1; i < n  ; i++) {
            double cross = ccw(ph, next, points[i]);
            double dist = (next-ph).norm() - (points[i] - ph).norm();
            // 일직선이면 더 멀리 있는점 , 반시계
            if(cross > 0 || (cross == 0 && dist < 0 ))
                next = points[i];
        }
        if(next == pivot) break;
        hull.push_back(next);
    }
    return hull;
}

int main(int argc, const char * argv[]) {
    
    
    freopen("/Users/smartgrid_aict/Desktop/algorithm/2699/2699/input.txt", "r", stdin);
    int T;
    cin >> T;
    while(T--) {
        int N;
        cin >> N;
        poly points;
        for(int i = 0; i < N; i++) {
            int xx, yy;
            cin >> xx >> yy;
            //input.push_back(make_pair(yy, xx));
            points.push_back(vector2(xx, yy));
        }
        
        //        sort(input.begin(), input.end());
        //
        //        for(int i = 0; i < input.size(); i++) {
        //            cout << input[i].first << " " << input[i].second << endl;
        //        }
//        for(int i = 0; i < points.size(); i++) {
//            cout << points.size() << endl;
//            cout << points[i].x << " " << points[i].y << endl;
//        }
        poly ret = giftWrap(points);
        
        cout << ret.size() << endl;
        for(int i = 0; i < ret.size(); i++) {
            cout << ret[i].x << " " << ret[i].y << endl;
        }
    }
    
    return 0;
}
