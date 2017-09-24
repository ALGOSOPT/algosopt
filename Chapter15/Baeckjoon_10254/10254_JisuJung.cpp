//
//  main.cpp
//  10254
//
//  Created by smartgrid_aict on 2017. 9. 23..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct vector2 {
    double x, y;
    vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_){}
    
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
    
    double dot(const vector2& rhs) const { return x*rhs.x + y*rhs.y; }
    double cross(const vector2& rhs) const { return x*rhs.y - rhs.x*y; }
    
};

double ccw(vector2 a, vector2 b) {
    return a.cross(b);
}

double ccw(vector2 p, vector2 a, vector2 b) {
    return ccw(a-p, b-p);
}

#define poly vector<vector2>

poly convex(poly& points) {
    
    int n = points.size();
    
    // 시작점 정하기
    vector2 pivot = *min_element(points.begin(), points.end());
    poly ret;
    ret.push_back(pivot);
    while(true) {
        // 마지막에 ret에 추가된 점이 now가 됨
        vector2 now = ret.back(), next = points[0];
        for(int i = 1; i < n; i++) {
            double cross = ccw(now, next, points[i]);
            double dist = (next-now).norm() - (points[i]-now).norm();
            // 반시계 방향에 있거나, 일직선 위에 있을때는 더 먼 것
            if(cross > 0 || (cross == 0 && dist < 0))
                next = points[i];
        }
        if(next == pivot) break;
        ret.push_back(next);
    }
    
    return ret;
}

poly diameter(const poly& p) {
    int nn = (int)p.size();
    
    // 비교 연산을 통해 찾는다, 없으면 못 찾음
    int left = (int)(min_element(p.begin(), p.end()) - p.begin());
    int right = (int)(max_element(p.begin(), p.end()) - p.begin());
    
    vector2 calipersA(0, 1);
    double ret = (p[right] - p[left]).norm();
    
    poly result(2);
    vector<vector2> toNext(nn);
    for(int i = 0; i < nn ; i++) {
        toNext[i] = (p[(i+1)%nn]-p[i]).normalize();
    }
    
    int a = left, b = right;
    result[0] = p[a];
    result[1] = p[b];
    while(a != right || b != left) {
        // normalize 하니까 바로 각도 나옴
        double cosThetaA = calipersA.dot(toNext[a]);
        double cosThetaB = -calipersA.dot(toNext[b]);
        if(cosThetaA > cosThetaB) {
            calipersA = toNext[a];
            a = (a+1)%nn;
        } else {
            calipersA = toNext[b]*-1;
            b = (b+1)%nn;
        }
        if(ret < (p[a]-p[b]).norm()) {
            result[0] = p[a];
            result[1] = p[b];
            ret = (p[a]-p[b]).norm();
        }
    }
    return result;
}

int main(int argc, const char * argv[]) {
    
    freopen("/Users/smartgrid_aict/Desktop/algorithm/10254/10254/input.txt", "r", stdin);
    
    int T;
    cin >> T;
    while(T--) {
        poly points;
        int n;
        cin >> n;
        for(int i = 0; i < n; i++) {
            int xx, yy;
            cin >> xx >> yy;
            points.push_back(vector2(xx, yy));
        }
        
        poly cond = convex(points);
        poly ret = diameter(cond);
        
        for(int i = 0 ; i < 2; i++) {
            cout << ret[i].x << " " << ret[i].y << " ";
        }
        cout << endl;
    }
    return 0;
}
