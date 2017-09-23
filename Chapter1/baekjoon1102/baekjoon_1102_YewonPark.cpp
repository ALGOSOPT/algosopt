#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<string>

using namespace std;

//n�� 16���� �۰ų� ���� �ڿ������� �ָ�����
//16�ڸ��� ǥ���� �����ؾ���

int n, p;
int cost[16][16];
int cache[1 << 16] = { -1, };

int bitCount(int x) {
	if (x == 0) return 0;
	return x % 2 + bitCount(x / 2);
}

int solve(int on) {//on�� �����ִ� ��
	//������� : ���� on�� ������ �ּ� �����־�� �� ������ �����ϸ� ��
	if (bitCount(on) >= p)
		return 0;

	int& ret = cache[on];
	if (ret != -1)
		return ret;

	ret = 50 * 16;
	
	//���� �����ִ� ���� ���鼭 �ٸ����� �ϳ��� �Ѻ���
	for (int i = 0; i < n; i++) {
		if (on & (1 << i)) {
			//����������
			for (int j = 0; j < n; j++) {//�������� ���� �ٸ� �� �Ѻ�
				if ((on & (1 << j)) == 0)
					ret = min(ret, solve(on | (1 << j)) + cost[i][j]);
			}
		}
	}

	return ret;
}

int main() {
	
	cin >> n;
	memset(cache, -1, sizeof(cache));

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> cost[i][j];

	string input_first;
	cin >> input_first;//ó�� ����
	int first = 0;
	//��Ʈ����ũ�� ǥ���ؾ���
	for (int i = 0; i < input_first.length(); i++) {
		if (input_first[i] == 'Y')
			first |= (1 << i);
	}
	cin >> p;
	//cout << first << "\n";
	//�Ұ����� ���� � ����...?
	if (!first | p>input_first.length())
		cout << -1;
	else
		cout << solve(first);
	
}