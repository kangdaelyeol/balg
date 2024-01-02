#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int UDSearchL(size_t index, vector<int>& BVector) {
	if (BVector.size() == 1)
		return 0;
	// 왼쪽부분으로 하향식 검사
	vector<int> Vlen(index, 0);
	int maxLen = 0;

	int now = BVector[index];
	for (int i = 0; i < index; i++) {
		if (BVector[i] < now) {
			int maxD = 0;
			Vlen[i]++;
			for (int j = 0; j < i; j++) {
				if (BVector[i] > BVector[j]) {
					if (maxD < Vlen[j]) maxD = Vlen[j];
				}
			}
			Vlen[i] += maxD;
		}
	};
	for (int i = 0; i < Vlen.size(); i++) {
		if (maxLen < Vlen[i]) maxLen = Vlen[i];
	}
	return maxLen;
}

int UDSearchR(int index, vector<int>& BVector) {
	if (BVector.size() == 1)
		return 0;
	vector<int> Vlen(BVector.size(), 0);
	int maxLen = 0;

	int now = BVector[index];
	for (int i = BVector.size() - 1; i > index; i--) {
		if (BVector[i] < now) {
			int maxD = 0;
			Vlen[i]++;
			for (int j = BVector.size() - 1; j > i; j--) {
				if (BVector[i] > BVector[j]) {
					if (maxD < Vlen[j]) maxD = Vlen[j];
				}
			}
			Vlen[i] += maxD;
		}
	};
	for (int i = 0; i < Vlen.size(); i++) {
		if (maxLen < Vlen[i]) maxLen = Vlen[i];
	}
	return maxLen;
};

int main() {
	int arrLen;
	int maxLen;
	int lenL;
	int lenR;
	int len;
	vector<int> BVector, upVector;

	cin >> arrLen;

	for (int i = 0; i < arrLen; i++) {
		int num;
		cin >> num;
		BVector.push_back(num);
		upVector.push_back(-1);
	}
	if (BVector.size() == 1) {
		cout << 1;
		return 0;
	}
	for (size_t i = 0; i + 2 < BVector.size(); i++) {
		// 올라가는 부분 집합 push - (첫 지점은 -1)
		if (BVector[i] < BVector[i + 1])
			upVector[i + 1] = BVector[i + 1];
	}

	for (size_t i = 1; i < upVector.size(); i++) {
		if (upVector[i] == -1) {
			len = UDSearchL(i - 1, BVector) + 1 + UDSearchR(i - 1, BVector);
			if (len > maxLen) maxLen = len;
		}
	}
	if (len > maxLen) maxLen = len;
	len = UDSearchL(upVector.size() - 1, BVector) + 1;
	if (len > maxLen) maxLen = len;
	len = UDSearchR(0, BVector) + 1;
	if (len > maxLen) maxLen = len;
	cout << maxLen;

	return 0;
}