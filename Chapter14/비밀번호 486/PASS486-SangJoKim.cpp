#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

#define MAX 1000*1000*10

using namespace std;

int n,lo, hi;

//minFactor[i] = i 의 가장 작은 소인수
int minFactor[MAX + 1];

//minFactorPower[i] = i의 소인수 분해에는 minFactor[i]의 몇 승이 포함되어 있는가?
int minFactorPower[MAX + 1];

//factors[i] = i 가 가진 약수의 수
int factors[MAX + 1];

void eratosthenes2() {
	minFactor[0] = minFactor[1] = -1;
	n = MAX;
	for (int i = 2; i <= n; i++) {
		minFactor[i] = i;
	}
	int sqrtn = int(sqrt(n));

	for (int i = 2; i <= sqrtn; i++) {
		//소수인 경우
		if (minFactor[i] == i) {
			for (int j = i * i; j <= n; j += i) {
				//소수의 배수. 즉 합성수 인 경우 가장 작은 소인수를 저장한다.
				if (minFactor[j] == j) {
					minFactor[j] = i;
				}
			}
		}
	}
}


void getFactorsSmart() {
	factors[1] = 1;
	for (int n = 2; n <= MAX; n++) {
		
		if (minFactor[n] == n) {
			minFactorPower[n] = 1;
			factors[n] = 2;
		}
		else {
			int p = minFactor[n];
			int m = n / p;

			if (p != minFactor[m])
				minFactorPower[n] = 1;
			else
				minFactorPower[n] = minFactorPower[m] + 1;
			int a = minFactorPower[n];

			factors[n] = (factors[m] / a) * (a + 1);
		}
	}
}

void getFactorsBrute() {
	memset(factors, 0, sizeof(factors));
	for (int div = 1; div <= MAX; div++)
		for (int multiple = div; multiple <= MAX; multiple += div)
			factors[multiple] ++;
}
int main() {

	freopen("input.txt", "r", stdin);
	int TC; scanf("%d", &TC);
	
	//에라토스테네스의 체를 이용하여 가장 작은 소인수를 저장
	eratosthenes2();


	//약수의 개수를 저장
	//factor(n) = factor(n/p) * ((a+1)/a)
	//getFactorsSmart();
	getFactorsBrute();


	while (TC--) {
		scanf("%d%d%d", &n, &lo, &hi);

		//cout << n << " " << lo << " " << hi << endl;
		int Count = 0;
		
		for (int i = lo; i <= hi; i++) {
			Count += (factors[i] == n);
		}

		printf("%d\n", Count);
	}
	return 0;
}