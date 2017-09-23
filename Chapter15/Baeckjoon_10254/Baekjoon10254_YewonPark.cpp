#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<limits>

using namespace std;

const double PI = 2.0 * acos(0.0);
int first_x = numeric_limits<int>::max();
int first_y = numeric_limits<int>::min();

struct vector2 {
	double x, y;
	explicit vector2(double x_ = 0, double y_ = 0) :x(x_), y(y_) {}

	bool operator == (const vector2& rhs) const {
		return x == rhs.x && y == rhs.y;
	}

	bool operator < (const vector2& rhs) const {
		return x != rhs.x ? x < rhs.x : y < rhs.y;
	}

	vector2 operator + (const vector2& rhs) const {
		return vector2(x + rhs.x, y + rhs.y);
	}

	vector2 operator - (const vector2& rhs) const {
		return vector2(x - rhs.x, y - rhs.y);
	}

	vector2 operator * (double rhs) const {
		return vector2(x * rhs, y * rhs);
	}

	//벡터의 길이 반환
	double norm() const { return hypot(x, y); }

	vector2 normalize() const {
		return vector2(x / norm(), y / norm());
	}

	//x축의 양의 방향으로부터 이 벡터까지 반시계 방향으로 잰 각도
	double polar() const { return fmod(atan2(y, x) + 2 * PI, 2 * PI); }

	double dot(const vector2& rhs) const {
		return x * rhs.x + y * rhs.y;
	}

	double cross(const vector2& rhs) const {
		return x * rhs.y - rhs.x * y;
	}

	vector2 project(const vector2& rhs) const {
		vector2 r = rhs.normalize();
		return r * r.dot(*this);
	}
};

double ccw(vector2 p, vector2 a, vector2 b) {
	return (a - p).cross(b - p);
}

//볼록다각형 정의
typedef vector<vector2> polygon;

//점들을 넣으면 그 점들을 포함하는 최소 크기의 볼록다각형 반환
polygon convexHull(const vector<vector2>& points) {

	int n = points.size();
	polygon result;
	//가장 왼쪽 아래 점을 찾는다. 이 점은 껍질에 반드시 포함된다.
	vector2 first = vector2(first_x, first_y);
	//cout << first_x << " " << first_y;
	result.push_back(first);
	while (true) {
		//가장 왼쪽인 점을 찾는다. 외적 이용
		//**점들이 평행인 경우 가장 먼 것을 선택한다
		vector2 now = result.back();
		vector2 next = points[0];
		for (int i = 1; i < n; i++) {
			vector2 point = points[i];
			double cross = ccw(now, next, point);
			double dist = (point - now).norm() - (next - now).norm();
			if ((cross > 0) || (cross == 0 && dist > 0))
				//cross > 0 : 반시계방향(왼쪽)??
				next = point;
		}
		if (next == first)
			break;
		result.push_back(next);
	}
	return result;
}

pair<vector2, vector2> diameter(const polygon& p) {
	
	pair<vector2, vector2> result;
	int n = p.size();

	int left = min_element(p.begin(), p.end()) - p.begin();
	int right = max_element(p.begin(), p.end()) - p.begin();

	vector2 calipersA(0, 1);
	double ret = (p[right] - p[left]).norm();

	vector<vector2> toNext(n);
	for (int i = 0; i < n; i++)
		toNext[i] = (p[(i + 1) % n] - p[i]).normalize();

	int a = left, b = right;

	while (a != right || b != left) {
		double cosThetaA = calipersA.dot(toNext[a]);
		double cosThetaB = -calipersA.dot(toNext[b]);
		if (cosThetaA > cosThetaB) {
			calipersA = toNext[a];
			a = (a + 1) % n;
		}
		else {
			calipersA = toNext[b] * (-1);
			b = (b + 1) % n;
		}
		if(ret < (p[a] - p[b]).norm()){
			ret = (p[a] - p[b]).norm();
			result.first = p[a];
			result.second = p[b];
		}
	}
	return result;
}

int main() {

	int c;
	cin >> c;
	while (c--) {
		vector<vector2> points = vector<vector2>();

		//그냥 이렇게 넣으면 됨
		int n;
		cin >> n;
		for (int i = 0; i < n; i++) {
			int x, y;
			cin >> x >> y;
			if (y > first_y || y == first_y && x < first_x)
				first_x = x, first_y = y;
			points.push_back(vector2(x, y));
		}

		polygon convex = convexHull(points);
		pair<vector2, vector2> result = diameter(convex);
		cout << result.first.x << " " << result.first.y << " " << result.second.x << " " << result.second.y << "\n";
		
		points.clear();
	}

	return 0;
}