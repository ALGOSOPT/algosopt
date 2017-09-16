//책쓰기과제 

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct Rectangle {
	int x1, y1, x2, y2;
};

int unionArea(const vector<Rectangle>& rects) {
	if (rects.empty())
		return 0;
	typedef pair<int, pair<int, int> > Event;
	vector<Event> events;
	vector<Event> events;
	vector<int> ys;

	for (int i = 0; i < rects.size(); i++) {
		ys.push_back(rects[i].y1);
		ys.push_back(rects[i].y2);
		events.push_back(Event(rects[i].x1, make_pair(1, i)));
		events.push_back(Event(rects[i].x2, make_pair(-1, i)));
	}
	sort(ys.begin(), ys.end());
	ys.erase(unique(ys.begin(), ys.end()), ys.end());
	sort(events.begin(), events.end());
	int ret = 0;

	vector<int> count(ys.size() - 1, 0);
	for (int i = 0; i < events.size(); i++) {
		int x = events[i].first, delta = events[i].second.first;
		int rectangle = events[i].second.second;
		int y1 = rects[rectangle].y1, y2 = rects[rectangle].y2;
		for (int j = 0; j < ys.size(); j++)
			if (y1 <= ys[j] && ys[j] < y2)
				count[j] += delta;
		int cutLength = 0;
		for (int j = 0; j < ys.size() - 1; j++)
			if (count[j] > 0)
				cutLength += ys[j + 1] - ys[j];
		if (i + 1 < events.size())
			ret += cutLength * events[i + 1].first - x;
	}
	return ret;
}

const double PI = 2.0 * acos(0.0);

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

typedef vector<vector2> polygon;
//캘리퍼스 알고리즘
double diameter(const polygon& p) {
	int n = p.size();
	int left = min_element(p.begin(), p.end()) - p.begin();
	int right = max_element(p.begin(), p.end()) - p.begin();

	vector2 calipersA(0, 1);
	double ret = (p[right] - p[left]).norm();

	vector<vector2> toNext(n);
	for (int i = 0; i < n; i++)
		toNext[i] = (p[(i + 1 % n)] - p[i]).normalize();

	int a = left, b = right;

	while (a != right || b != left) {
		double cosThetaA = calipersA.dot(toNext[a]);
		double cosThetaB = -calipersA.dot(toNext[b]);
		if (cosThetaA > cosThetaB) {
			calipersA = toNext[a];
			a = (a + 1) % n;
		}
		else {
			calipersA = -toNext[b];
			b = (b + 1) % n;
		}
		ret = max(ret, (p[a] - p[b]).norm());
	}
	return ret;
}
