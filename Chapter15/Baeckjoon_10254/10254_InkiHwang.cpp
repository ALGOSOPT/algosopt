//FAIL

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

struct vector2 {
  int x,y;

  vector2(){}

  vector2(int _x, int _y) : x(_x), y(_y) {}

  bool operator == (vector2& rhs) {
    return x==rhs.x && y==rhs.y;
  }

  bool operator < (const vector2& rhs) const {
    return x!=rhs.x ? x<rhs.x : y<rhs.y;
  }

  vector2 operator + (const vector2& rhs) const {
    return vector2(x+rhs.x, y+rhs.y);
  }

  vector2 operator - (const vector2& rhs) const {
    return vector2(x-rhs.x, y-rhs.y);
  }

  vector2 operator * (const double rhs) const {
    return vector2(rhs*x, rhs*y);
  }

  double norm() {
    return hypot(x,y);
  }

  vector2 normalize() {
    return vector2(x/norm(), y/norm());
  }

  double dot(vector2& rhs) {
    return x*rhs.x + y*rhs.y;
  }

  double cross(vector2& rhs) {
    return x*rhs.y - y*rhs.x;
  }
};

double cw(vector2 a, vector2 b) {
  return a.cross(b);
}

double ccw(vector2 p, vector2 a, vector2 b) {
  return cw(a-p, b-p);
}

vector<vector2> wrapGift(vector<vector2> points) {
  int n = points.size();
  vector2 pivot = *min_element(points.begin(), points.end());
  vector<vector2> hull;
  hull.push_back(pivot);

  while(true) {
    vector2 ph = hull.back();
    vector2 next = points[0];

    for(int i=1; i<n; i++) {
      double cross = ccw(ph, next, points[i]);
      double dist = (next-ph).norm() - (points[i]-ph).norm();
      if(cross > 0 || (cross == 0 && dist > 0)) {
        next = points[i];
      }
    }

    if(next == pivot) break;
    hull.push_back(next);
  }
  return hull;
}

// 시계 반대 방향으로 주어진 블록 다각형에서 가장 먼 꼭지점 쌍 사이의 거리를 반환한다.
pair<vector2, vector2> diameter(vector<vector2> p) {
  pair<vector2, vector2> rett;
  int n = p.size();
  // 우선 가장 왼쪽에 있는 점과 오른쪽에 있는 점을 찾는다.
  int left = min_element(p.begin(), p.end()) - p.begin();
  int right = max_element(p.begin(), p.end()) - p.begin();

  // p[left]와 p[right]에 각각 수직선을 붙인다. 두 수직선은 서로 정반대 방향을 가리키므로,
  // A의 방향만을 표현하면 된다.
  vector2 calipersA(0, 1);
  double ret = (p[right] - p[left]).norm();
  // toNext[i] = p[i]에서 다음 점까지의 방향을 나타내는 단위 벡터
  vector<vector2> toNext(n);
  for(int i=0; i<n; i++) {
    toNext[i] = (p[(i+1)%n]-p[i]).normalize();
  }
  // a와 b는 각각 두 선분이 어디에 붙은 채로 회전하고 있는지를 나타낸다.
  int a = left, b = right;
  // 반 바퀴 돌아서 두 선분이 서로 위치를 바꿀 때까지 계속한다.

  while(a != right || b != left) {
    // a에서 다음 점까지의 각도와 b에서 다음 점까지의 각도 중 어느 쪽이 작은지 확인
    double cosThetaA = calipersA.dot(toNext[a]);
    double cosThetaB = -calipersA.dot(toNext[b]);
    if(cosThetaA > cosThetaB) { // thetaA < thetaB
      calipersA = toNext[a];
      a = (a+1)%n;
    }
    else {
      calipersA = toNext[b]*(-1);
      b = (b+1)%n;
    }
    if(ret < (p[a] - p[b]).norm()) {
      ret = (p[a] - p[b]).norm();
      rett.first = p[a];
      rett.second = p[b];
    }
    // ret = max(ret, (p[a] - p[b]).norm());
  }
  // printf("%d %d %d %d\n", ret1.x, ret1.y, ret2.x, ret2.y);
  return rett;
}

int main()
{
  int testCase;
  scanf("%d", &testCase);
  for(int tc=1; tc<=testCase; tc++) {
    int N;
    scanf("%d", &N);
    vector<vector2> points;
    for(int i=0; i<N; i++) {
      int x,y;
      scanf("%d %d", &x, &y);
      points.push_back(vector2(x,y) );
    }
    vector<vector2> polygon = wrapGift(points);
    // reverse(polygon.begin(), polygon.end());
    // for(int i=0; i<polygon.size(); i++) {
    //   printf("%d %d\n", polygon[i].x, polygon[i].y);
    // }
    pair<vector2, vector2> ret = diameter(polygon);
    printf("%d %d %d %d\n", ret.first.x, ret.first.y, ret.second.x, ret.second.y);
  }
  return 0;
}
