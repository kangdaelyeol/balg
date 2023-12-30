#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int i = 0;
size_t maxInd = 0;
int interval = 3;
double tmpd = pow(10, interval);
int valForIndex = static_cast<int>(tmpd);
bool isMinusa = false;
bool isMinusb = false;
void checkVectorRange(vector<int>& a) {
	while (a[static_cast<int>(a.size()) - 1] == 0 && a.size() > 1) {
		a.pop_back();
	};

	// 올려치기 -> size = 1이면서 음수값 주어지면 무한 루프 생기더라
	// 어차피 올려치기 후 size trimming 할 것이기 때문에 미리 올려주고, 최상위 전 까지만 검사
	a.push_back(0);
	for (int t = 0; t <= static_cast<int>(a.size()) - 2; t++) {
		while (a[t] < 0) {
			a[t] += valForIndex;
			a[t + 1]--;
		}

		while (a[t] >= valForIndex) {
			a[t] -= valForIndex;
			a[t + 1]++;
		}
	}

	while (a[static_cast<int>(a.size()) - 1] == 0 && a.size() > 1) {
		a.pop_back();
	};

	if (a[static_cast<int>(a.size()) - 1] < 0 && a.size() > 1) {
		a[a.size() - 1]++;

		for (int k = static_cast<int>(a.size()) - 2; k > 0; k--) {
			a[k] -= (valForIndex - 1);
		}
		a[0] -= valForIndex;
	}

	for (int k = 0; k < static_cast<int>(a.size()) - 1; k++) {
		if (a[k] == -valForIndex) {
			a[k] += valForIndex;
			a[k + 1]--;
		}
	}

	while (a[static_cast<int>(a.size()) - 1] == 0 && a.size() > 1) {
		a.pop_back();
	};
}

void printVector(vector<int>* a, bool isFinal = false) {
	string result;
	for (vector<int>::reverse_iterator rit = a->rbegin(); rit != a->rend(); ++rit) {
		int tmpRit = *rit;
		if (tmpRit < 0) tmpRit = -tmpRit;
		if (rit != a->rbegin() && static_cast<int>(to_string(tmpRit).length()) < interval) {
			for (int k = 0; k < interval - static_cast<int>(to_string(tmpRit).length()); k++) {
				result += "0";
			};
			result += to_string(tmpRit);
		} else if (rit == a->rbegin()) {
			result += to_string(*rit);
		} else {
			result += to_string(tmpRit);
		}
	}
	if (isFinal)
		cout << result;
	else
		cout << result << "\n";
}

int main() {
	string a, b;
	cin >> a >> b;
	vector<int> av, bv, addv, subtrackv, multiplyv;
	if (a.at(0) == '-') {
		isMinusa = true;
		a = a.substr(1, a.length() - 1);
	}
	if (b.at(0) == '-') {
		isMinusb = true;
		b = b.substr(1, b.length() - 1);
	}

	while (a.at(0) == '0' && a.length() > 1) a = a.substr(1, a.length() - 1);
	while (b.at(0) == '0' && b.length() > 1) b = b.substr(1, b.length() - 1);

	int aStringRemain = static_cast<int>(a.length()) % interval;
	int bStringRemain = static_cast<int>(b.length()) % interval;

	for (i = static_cast<int>(a.length()); i >= 0;) {
		int pushVal = 0;
		i -= interval;
		if (i >= 0) {
			pushVal = stoi(a.substr(i, interval));
			if (isMinusa && pushVal > 0) pushVal = -pushVal;
			av.push_back(pushVal);
		} else if (i < 0 && i > -interval) {
			pushVal = stoi(a.substr(0, aStringRemain));
			if (isMinusa && pushVal > 0) pushVal = -pushVal;
			av.push_back(pushVal);
		}
	}

	i = b.length();
	do {
		i -= interval;
		int pushVal = 0;
		if (i >= 0) {
			pushVal = stoi(b.substr(i, interval));
			if (pushVal > 0 && isMinusb) pushVal = -pushVal;
			bv.push_back(pushVal);
		} else if (i < 0 && i > -interval) {
			pushVal = stoi(b.substr(0, bStringRemain));
			if (pushVal > 0 && isMinusb) pushVal = -pushVal;
			bv.push_back(pushVal);
		}
	} while (i >= 0);

	if (av.size() >= bv.size())
		maxInd = av.size();
	else
		maxInd = bv.size();
	// add
	for (size_t u = 0; u < maxInd; u++) {
		if (u > av.size() - 1) {
			addv.push_back(bv[u]);
		} else if (u > bv.size() - 1) {
			addv.push_back(av[u]);
		} else {
			addv.push_back(av[u] + bv[u]);
		}
	}

	for (vector<int>::size_type u = 0; u < maxInd; u++) {
		if (u > av.size() - 1)
			subtrackv.push_back(-bv[u]);
		else if (u > bv.size() - 1)
			subtrackv.push_back(av[u]);
		else
			subtrackv.push_back(av[u] - bv[u]);
	}

	while (multiplyv.size() < av.size() + bv.size())
		multiplyv.push_back(0);

	// av와 bv곱셈
	for (size_t n = 0; n < av.size(); n++)
		for (size_t m = 0; m < bv.size(); m++) {
			multiplyv[n + m] += (av[n] * bv[m]);
		}

	// vector validation check
	checkVectorRange(multiplyv);
	checkVectorRange(subtrackv);
	checkVectorRange(addv);

	printVector(&addv);
	printVector(&subtrackv);
	printVector(&multiplyv, true);
	return 0;
}