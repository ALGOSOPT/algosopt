#include<iostream>
#include<vector>
#include<cmath>
#include<limits>
#include<algorithm>

using namespace std;

/*/////////////////////////아이디어/////////////////////////
너드와 너드가 아닌 사람을 구분해야한다.
변수가 A, B 두개이므로 **직선**으로 **구분**지을 수 있어야 한다
=> 직선을 가운데 두고 두 원이 있는 모습을 떠올려봤음
1. 볼록다각형
2. 두 볼록다각형이 겹치지 않아야한다
(볼록다각형을 고려하는 이유는 **직선**으로 구분지어야 하기 때문이다

볼록다각형을 만드는 방법 : 컨벡스홀 알고리즘
*///////////////////////////////////////////////////////////

//2차원 벡터를 표현하는 vector2 클래스
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

double ccw(vector2 p, vector2 a, vector2 b) {
	return (a - p).cross(b - p);
}

//볼록다각형 정의
typedef vector<vector2> polygon;

//점들을 넣으면 그 점들을 포함하는 최소 크기의 볼록다각형 반환
//책을 보고 이해한 코드임!!!!
polygon convexHull(const vector<vector2>& points) {
	int n = points.size();
	
	polygon result;
	//가장 왼쪽 아래 점을 찾는다. 이 점은 껍질에 반드시 포함된다.
	vector2 first = *min_element(points.begin(), points.end());

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
				//cross > 0 : 반시계방향(왼쪽)
				next = point;

		}
		if (next == first)
			break;
		result.push_back(next);
	}
	return result;
}

bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d) {
	double ab = ccw(a, b, c)*ccw(a, b, d);
	double cd = ccw(c, d, a)*ccw(c, d, b);
	//두 선분이 한 직선 위에 있거나 끝점이 겹치는 경우
	if (ab == 0 && cd == 0) {
		if (b < a)
			swap(a, b);
		if (d < c)
			swap(c, d);
		return !(b < c || d < a);
	}
	return ab <= 0 && cd <= 0;
}

//얘 이용해서 볼록다각형이 겹치는 지도 확인할 수 있을 것 같지만 for문 돌리므로(시간문제) 일단 생략
bool isInside(vector2 q, const vector<vector2>& p) {
	int crosses = 0;
	for (int i = 0; i < p.size(); i++) {
		int j = (i + 1) % p.size();
		if ((p[i].y > q.y) != (p[j].y > q.y)) {
			double atX = (p[j].x - p[i].x)*(q.y - p[i].y) / (p[j].y - p[i].y) + p[i].x;
			if (q.x < atX)
				crosses++;
		}
	}
	return crosses % 2 > 0;
}

bool overlap(polygon p1, polygon p2) {
	//**한 볼록다각형이 다른 볼록다각형을 포함하는 경우**
	if (isInside(p1[0], p2) || isInside(p2[0], p1))
		return true;
	//볼록다각형이 겹치면 두 볼록다각형을 이루는 선분이 교차해야 한다
	for (int i = 0; i < p1.size() - 1; i++) {
		vector2 a = p1[i];
		vector2 b = p1[i + 1];
		for (int j = 0; j < p2.size() - 1; j++) {
			vector2 c = p2[j];
			vector2 d = p2[j + 1];
			if (segmentIntersects(a, b, c, d))
				return true;
		}
	}
	return false;
}

int main() {

	int c;
	cin >> c;
	while (c--) {
		int n;
		cin >> n;
		vector<vector2> Nerd_temp = vector<vector2>();
	    vector<vector2> notNerd_temp = vector<vector2>();
		for (int i = 0; i < n; i++) {
			bool isNerd;
			int footSize, typingFast;
			cin >> isNerd >> footSize >> typingFast;
			if (isNerd)
				Nerd_temp.push_back(vector2(footSize, typingFast));
			else
				notNerd_temp.push_back(vector2(footSize, typingFast));
		}

		polygon Nerd = convexHull(Nerd_temp);
		polygon notNerd = convexHull(notNerd_temp);

		if (overlap(Nerd, notNerd))
			cout << "THEORY IS INVALID\n";
		else
			cout << "THEORY HOLDS\n";
	}
	return 0;
}