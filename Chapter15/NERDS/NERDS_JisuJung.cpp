//
//  main.cpp
//  nerds
//
//  Created by smartgrid_aict on 2017. 9. 16..
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
    explicit vector2(double x_, double y_) : x(x_), y(y_){}
    
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

double ccw(vector2 a, vector2 b) {
    return a.cross(b);
}

// 점 p를 기준으로 b가 a의 반시계 방향이면 양수, 시계 방향이면 음수
double ccw(vector2 p, vector2 a, vector2 b) {
    return ccw(a-p, b-p);
}

typedef vector<vector2> poly;
bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d) {
    double ab = ccw(a,b,c) * ccw(a,b,d);
    double cd = ccw(c,d,a) * ccw(c,d,b);
    if(ab == 0 && cd == 0) {
        if(b<a) swap(a,b);
        if(d<c) swap(c,d);
        return !(b<c || d<a);
    }
    return ab <= 0 && cd <= 0;
}

bool isInside(vector2 q, const poly& p) {
    int crosses = 0;
    for(int i = 0 ; i < p.size(); i++) {
        int j = (i+1)%p.size();
        if((p[i].y > q.y) != (p[j].y > q.y)) {
            double atX = (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y) + p[i].x;
            
            if(q.x < atX)
                crosses++;
        }
    }
    return crosses % 2 > 0;
}

bool polygonIntersects(const poly& p, const poly& q) {
    int n = p.size(), m = q.size();
    
    if(isInside(p[0], q) || isInside(q[0],p)) return true;
    for(int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j < m ; j++) {
            if(segmentIntersects(p[i], p[(i+1)%n], q[j], q[(j+1)%m]))
                return true;
        }
    }
    
    return false;
}

poly giftWrap(const vector<vector2>& points) {
    int n = points.size();
    
    poly hull;
    vector2 pivot = *min_element(points.begin(), points.end());
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
    
    freopen("/Users/smartgrid_aict/Desktop/algorithm/nerds/nerds/input.txt", "r", stdin);
    int T;
    cin >> T;
    while(T--) {
        vector<vector2> inputs[2];
        int n;
        cin >> n;
        for(int i = 0; i < n; i++) {
            int t, x, y;
            cin >> t >> x >> y;
            inputs[t].push_back(vector2(x, y));
        }
        poly hulls[2];
        for(int i = 0; i < 2; i++)
            hulls[i] = giftWrap(inputs[i]);
        if(polygonIntersects(hulls[0], hulls[1]))
            cout << "THEORY IS INVALID" << endl;
        else
            cout << "THEORY HOLDS" << endl;
    }
    return 0;
}
