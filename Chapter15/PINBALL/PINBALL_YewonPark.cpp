#include<iostream>
#include<vector>
#include<cmath>
#include<limits>

using namespace std;

int x, y, dx, dy, N;
double EPSILON = numeric_limits<double>::epsilon();
double INFTY = numeric_limits<double>::infinity();

//2���� ���͸� ǥ���ϴ� vector2 Ŭ����
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

	//������ ���� ��ȯ
	double norm() const { return hypot(x, y); }

	vector2 normalize() const {
		return vector2(x / norm(), y / norm());
	}

	//x���� ���� �������κ��� �� ���ͱ��� �ݽð� �������� �� ����
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

//���� ���� ��ġ���� p, 1�п� d��ŭ �̵�
//��ֹ��� �߽� c, ������ r
double findCrashTime(vector2 p, vector2 d, vector2 center, int r) {
	double a = d.dot(d);
	double b = 2 * (p - center).dot(d);
	double c = center.dot(center) + p.dot(p) - 2 * center.dot(p) - r*r;

	double determinant = b*b - 4 * a*c;
	if (determinant < -EPSILON)
		return INFTY;
	if (determinant < EPSILON)
		return -b / (2 * a);
	vector<double> sols;
	sols.push_back((-b - sqrt(determinant)) / (2 * a));
	sols.push_back((-b + sqrt(determinant)) / (2 * a));

	if (sols.empty() || sols[0] < EPSILON)
		return INFTY;
	return sols[0];
}

vector2 reflect(vector2 dir, vector2 center, vector2 contact) {
	return (dir - dir.project(contact - center) * 2).normalize();
}

vector<vector2> center;
vector<int> radius;

int main() {
	int c;

	cin >> c;

	while (c--) {

		center = vector<vector2>();
		radius = vector<int>();

		cin >> x >> y >> dx >> dy >> N;

		vector2 here = vector2(x, y);
		vector2 dir = vector2(dx, dy);

		for (int i = 0; i < N; i++) {
			int x1, y1, r;
			cin >> x1 >> y1 >> r;
			center.push_back(vector2(x1, y1));
		}

		dir = dir.normalize();
		int hitCount = 0;
		while (hitCount < 10) {
			int circle = -1;
			double time = INFTY*0.5;
			for (int i = 0; i < N; i++) {
				double cand = findCrashTime(here, dir, center[i], radius[i] + 1);
				if (cand < time) {
					time = cand;
					circle = i;
				}
			}
			if (circle == -1) break;
			cout << circle << " ";
			hitCount++;

			vector2 newPosition = here + dir*time;
			dir = reflect(dir, center[circle], newPosition);
			here = newPosition;
		}
		cout << endl;
	}

	return 0;
}