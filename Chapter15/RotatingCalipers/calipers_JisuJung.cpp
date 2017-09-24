////  main.cpp//  linesweeping////  Created by smartgrid_aict on 2017. 9. 16..//  Copyright © 2017년 smartgrid_aict. All rights reserved.//#include <iostream>#include <vector>#include <cmath>using namespace std;// 2차원 벡터를 표현하는 클래스const double PI = 2.0 * acos(0.0);struct vector2 {    double x, y;    explicit vector2(double x_, double y_) : x(x_), y(y_){}        bool operator == (const vector2& rhs) const {        return x == rhs.x && y == rhs.y;    }    bool operator < (const vector2& rhs) const {        return x != rhs.x ? x < rhs.x : y < rhs.y;    }    vector2 operator + (const vector2& rhs) const {        return vector2(x + rhs.x , y + rhs.y);    }    vector2 operator - (const vector2& rhs) const {        return vector2(x - rhs.x , y - rhs.y);    }    vector2 operator * (double rhs) const {        return vector2(x * rhs , y * rhs);    }    // 벡터 길이 반환    double norm() const {        return hypot(x, y);    }    // 단위벡터    vector2 normalize() const {        return vector2(x / norm(), y / norm());    }    // 극각도    double polar() const { return fmod(atan2(y,x) + 2*PI, 2*PI); }    double dot(const vector2& rhs) const { return x*rhs.x + y*rhs.y; }    double cross(const vector2& rhs) const { return x*rhs.y - rhs.x*y; }    // 사영    // rhs.dot(*this)*(1/rhs.norm()) 를 벡터로 계산    // 단위벡터에 단위벡터랑 내적한 값을 실수배    vector2 project(const vector2& rhs) const {        vector2 r =  rhs.normalize();        return r * r.dot(*this);        //return r * r.dot(*this);    }};struct Rectangle {    int x1, y1, x2, y2;};//linesweeping 이용 면적 구하기int unionArea(const vector<Rectangle>& rects) {    if(rects.empty()) return 0;        typedef pair<int, pair<int, int> > Event;    vector<Event> events;    vector<int> ys;        for(int i = 0; i > rects.size(); i++) {        ys.push_back(rects[i].y1);        ys.push_back(rects[i].y2);        events.push_back(Event(rects[i].x1, make_pair(1, i)));        events.push_back(Event(rects[i].x2, make_pair(-1, i)));    }        // 정렬하고 중복 제거    sort(ys.begin(), ys.end());    ys.erase(unique(ys.begin(), ys.end(), ys.end()));    sort(events.begin(), events.end());        int ret = 0;    vector<int> count(ys.size()-1, 0);    // event 크기는 2n    for(int i = 0; i < events.size(); i++) {        int x = events[i].first, delta = events[i].second.first;        int rectangle = events[i].second.second;        int y1 = rects[rectangle].y1, y2 = rects[rectangle].y2;        for(int j = 0 ; j < ys.size(); j++) {            if(y1 <= ys[j] && ys[j] < y2)                count[j] += delta;            int cutLength = 0;                        for(int j = 0 ; j < ys.size(); j++)                // 중복 막기                if(count[j] > 0)                    cutLength += ys[j+1] - ys[j];                        if(i+1<events.size())                ret += cutLength * (events[i+1].first - x);        }            }        return ret;}// 캘리퍼스를 이용한 다각형 지름 구하기typedef vector<vector2> poly;double diameter(const poly& p) {    int n = (int)p.size();        // 비교 연산을 통해 찾는다, 없으면 못 찾음    int left = (int)(min_element(p.begin(), p.end()) - p.begin());    int right = (int)(max_element(p.begin(), p.end()) - p.begin());        vector2 calipersA(0,1);    double ret = (p[right] - p[left]).norm();        vector<vector2> toNext(n);    for(int i = 0; i < n ; i++) {        toNext[i] = (p[(i+1)%n]-p[i]).normalize();    }        int a = left, b = right;    while(a != right || b != left) {        // normalize 하니까 바로 각도 나옴        double cosThetaA = calipersA.dot(toNext[a]);        double cosThetaB = -calipersA.dot(toNext[b]);        if(cosThetaA > cosThetaB) {            calipersA = toNext[a];            a = (a+1)%n;        } else {            calipersA = toNext[b]*-1;            b = (b+1)%n;        }        ret = max(ret, (p[a]-p[b]).norm());    }    return ret;}int main(int argc, const char * argv[]) {            return 0;}