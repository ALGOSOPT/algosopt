#include<iostream>
#include<vector>
#include<cmath>
#include<limits>
#include<algorithm>

using namespace std;

/*/////////////////////////���̵��/////////////////////////
�ʵ�� �ʵ尡 �ƴ� ����� �����ؾ��Ѵ�.
������ A, B �ΰ��̹Ƿ� **����**���� **����**���� �� �־�� �Ѵ�
=> ������ ��� �ΰ� �� ���� �ִ� ����� ���÷�����
1. ���ϴٰ���
2. �� ���ϴٰ����� ��ġ�� �ʾƾ��Ѵ�
(���ϴٰ����� ����ϴ� ������ **����**���� ��������� �ϱ� �����̴�

���ϴٰ����� ����� ��� : ������Ȧ �˰���
*///////////////////////////////////////////////////////////

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

double ccw(vector2 p, vector2 a, vector2 b) {
	return (a - p).cross(b - p);
}

//���ϴٰ��� ����
typedef vector<vector2> polygon;

//������ ������ �� ������ �����ϴ� �ּ� ũ���� ���ϴٰ��� ��ȯ
//å�� ���� ������ �ڵ���!!!!
polygon convexHull(const vector<vector2>& points) {
	int n = points.size();
	
	polygon result;
	//���� ���� �Ʒ� ���� ã�´�. �� ���� ������ �ݵ�� ���Եȴ�.
	vector2 first = *min_element(points.begin(), points.end());

	result.push_back(first);

	while (true) {

		//���� ������ ���� ã�´�. ���� �̿�
		//**������ ������ ��� ���� �� ���� �����Ѵ�
		vector2 now = result.back();
		vector2 next = points[0];
		for (int i = 1; i < n; i++) {

			vector2 point = points[i];
			double cross = ccw(now, next, point);
			double dist = (point - now).norm() - (next - now).norm();
			if ((cross > 0) || (cross == 0 && dist > 0))
				//cross > 0 : �ݽð����(����)
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
	//�� ������ �� ���� ���� �ְų� ������ ��ġ�� ���
	if (ab == 0 && cd == 0) {
		if (b < a)
			swap(a, b);
		if (d < c)
			swap(c, d);
		return !(b < c || d < a);
	}
	return ab <= 0 && cd <= 0;
}

//�� �̿��ؼ� ���ϴٰ����� ��ġ�� ���� Ȯ���� �� ���� �� ������ for�� �����Ƿ�(�ð�����) �ϴ� ����
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
	//**�� ���ϴٰ����� �ٸ� ���ϴٰ����� �����ϴ� ���**
	if (isInside(p1[0], p2) || isInside(p2[0], p1))
		return true;
	//���ϴٰ����� ��ġ�� �� ���ϴٰ����� �̷�� ������ �����ؾ� �Ѵ�
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