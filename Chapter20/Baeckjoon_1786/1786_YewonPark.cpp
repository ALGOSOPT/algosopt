#include<iostream>
#include<vector>

using namespace std;

vector<int> getPartial(string p) {

	int m = p.size();
	vector<int> pi(m, 0);
	
	int matched = 0;

	for (int i = 1; i < m; i++) {
		while (matched > 0 && p[i] != p[matched])
			matched = pi[matched - 1];

		if (p[i] == p[matched]) {
			matched++;
			pi[i] = matched;
		}
	}
	return pi;
}

vector<int> kmp(string H, string N) {
	int m = H.size(); int n = N.size();
	vector<int> pi = getPartial(N);

	vector<int> ret;

	int matched = 0;
	for (int i = 0; i < m; i++) {
		while (matched > 0 && H[i] != N[matched])
			matched = pi[matched - 1];

		if (H[i] == N[matched]) {
			matched++;
			if (matched == n) {
				ret.push_back(i - n + 1);
				matched = pi[matched - 1];
			}
		}
	}
	return ret;
}

int main() {

	string T = "";
	string P = "";

	char input[1000000];
	
	cin.getline(input, 1000000);

	for (int i = 0; input[i] != NULL; i++) {
		T += input[i];
	}

	cin.getline(input, 1000000);
	
	for (int i = 0; input[i] != NULL; i++) {
		P += input[i];
	}

	vector<int> result = kmp(T, P);

	cout << result.size() << "\n";
	for (int i = 0; i < result.size(); i++)
		cout << result[i] + 1 << " ";
}
