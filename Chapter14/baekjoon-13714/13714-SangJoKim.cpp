#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;


//에라토스테네스의 체를 이용하여 Prime에 2000이하의 소수를 집어 넣는다. 
//총 소수의 개수는 303개
bool isPrime[2001];
vector<int> Prime;



//2000까지의 수를 소인수 분해하여 각 소수가 몇개로 이루어지는지 저장한다.
//numOfPrimeFactor[i][j] = i를 소인수분해하면 Prime[j]가 몇개?
int numOfPrimeFactor[2001][304];


int nowPrimeFactor[303];

void incresePrimeFactor(int i) {

	for (int idx = 0; idx < 303; idx++) {
		nowPrimeFactor[idx] += numOfPrimeFactor[i][idx];
	}

}

void decreasePrimeFactor(int i) {

	for (int idx = 0; idx < 303; idx++) {
		nowPrimeFactor[idx] -= numOfPrimeFactor[i][idx];
	}

}
int main() {
	

	#pragma region Rrime에 소수의 개수를 집어 넣음
	//Prime에 소수의 개수를 집어 넣는다.
	memset(isPrime, true, sizeof(isPrime));

	isPrime[0] = isPrime[1] = false;

	for (int i = 2; i <= 2000; i++) {
		for (int j = i * i; j <= 2000; j += i) {
			isPrime[j] = false;
		}
	}

	for (int i = 0; i <= 2000; i++) {
		if (isPrime[i])
			Prime.push_back(i);
	}

	#pragma endregion

	//cout << Prime.size() << endl;

	#pragma region numOfPrimeFactor에 소인수의 개수를 넣는다.

	memset(numOfPrimeFactor, 0, sizeof(numOfPrimeFactor));

	for (int i = 2; i <= 2000; i++) {
		int now_I = i;
		for (int j = 0; j < Prime.size(); j++) {
			int count = 0;

			//나누어 떨어지면
			while (now_I % Prime[j] == 0) {
				now_I /= Prime[j];
				count++;
			}

			//다 나누어 떨어졌으면
			numOfPrimeFactor[i][j] = count;
		}
	}


	////test
	//for (int i = 0; i < 10; i++) {
	//	printf("%4d", Prime[i]);
	//}
	//cout << endl << endl;

	//for (int i = 0; i < 10; i++) {
	//	printf("%4d", numOfPrimeFactor[100][i]);
	//}
	//cout << endl;
	


	#pragma endregion


	#pragma region 약수의 개수를 구해 모두 더한다

	int ret = 0;
	freopen("input.txt", "r", stdin);

	int a, b, c; cin >> a >> b >> c;


	

	for (int i = 1; i <= a; i++) {

		incresePrimeFactor(i);

		for (int j = 1; j <= b; j++) {

			incresePrimeFactor(j);

			for (int k = 1; k <= c; k++) {

				incresePrimeFactor(k);

				int nowNumOfFactor = 1;

				for (int index = 0; index < 303; index++) {
					if (nowPrimeFactor[index] > 0) {
						nowNumOfFactor *= nowPrimeFactor[index] + 1;
					}
				}

				ret += nowNumOfFactor;

				decreasePrimeFactor(k);
			}
			decreasePrimeFactor(j);
		}
		decreasePrimeFactor(i);
	}
	#pragma endregion


	cout << ret << endl;


	return 0;
}