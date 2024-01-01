#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int UDSearchL(int index, vector<int>& BVector) {
	// 왼쪽부분으로 하향식 검사
	vector<vector<int> > LDQueue;

	int now = BVector[index];
	int leftLen = 0;
	// 사이즈가 1 인 경우
	if (BVector.size() == 1) {
		return 0;
	}
	// LDQueue 채우기
	for (int i = index - 1; i >= 0; i--) {
		int leftVal = BVector[i];
		if (leftVal < now) {
			bool isNew = true;
			for (size_t s = 0; s < LDQueue.size(); s++) {
				for (size_t t = LDQueue[s].size() - 1; t > 0; t--) {
					if (LDQueue[s][t] < leftVal && LDQueue[s][t - 1] > leftVal) {
						vector<int> newV;
						copy(LDQueue[s].begin() + 0, LDQueue[s].begin() + t - 1, back_inserter(newV));
						newV.push_back(leftVal);
						LDQueue.push_back(newV);
						isNew = false;
					}
				}
				// 마지막 요소보다 작다면 inQueue
				if (leftVal < LDQueue[s][LDQueue[s].size() - 1]) {
					LDQueue[s].push_back(leftVal);
					isNew = false;
				}
			}
			if (isNew) {
				vector<int> newV;
				newV.push_back(leftVal);
				LDQueue.push_back(newV);
			}
		}
	}
	// LDQueue 최대 사이즈
	for (size_t i = 0; i < LDQueue.size(); i++) {
		if (leftLen < LDQueue[i].size()) leftLen = LDQueue[i].size();
	}

	// 중앙 부분 + 1해서 해당 index기준 최대 수열 길이 반환
	return leftLen;
};

int UDSearchR(int index, vector<int>& BVector) {
	// 왼쪽부분으로 하향식 검사
	vector<vector<int> > RDQueue;

	int now = BVector[index];
	int rightLen = 0;
	// 사이즈가 1 인 경우
	if (BVector.size() == 1) {
		return 0;
	}

	// RDQueue채우기
	for (int i = index + 1; i < BVector.size(); i++) {
		int rightVal = BVector[i];
		if (rightVal < now) {
			bool isNew = true;
			for (size_t s = 0; s < RDQueue.size(); s++) {
				for (size_t t = RDQueue[s].size() - 1; t > 0; t--) {
					if (RDQueue[s][t] < rightVal && RDQueue[s][t - 1] > rightVal) {
						vector<int> newV;
						copy(RDQueue[s].begin() + 0, RDQueue[s].begin() + t - 1, back_inserter(newV));
						newV.push_back(rightVal);
						RDQueue.push_back(newV);
						isNew = false;
					}
				}
				// 마지막 요소보다 작다면 inQueue
				if (rightVal < RDQueue[s][RDQueue[s].size() - 1]) {
					RDQueue[s].push_back(rightVal);
					isNew = false;
				}
			}
			if (isNew) {
				vector<int> newV;
				newV.push_back(rightVal);
				RDQueue.push_back(newV);
			}
		}
	}

	// RDQueue 쵀대 사이즈
	for (size_t i = 0; i < RDQueue.size(); i++) {
		if (rightLen < RDQueue[i].size()) rightLen = RDQueue[i].size();
	}

	// 중앙 부분 + 1해서 해당 index기준 최대 수열 길이 반환
	return rightLen;
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

	for (size_t i = 0; i + 2 < BVector.size(); i++) {
		// 올라가는 부분 집합 push - (첫 지점은 -1)
		if (BVector[i] < BVector[i + 1])
			upVector[i + 1] = BVector[i + 1];
	}

	for (size_t i = 1; i < upVector.size(); i++) {
		if (upVector[i] == -1) {
			lenL = UDSearchL(i - 1, BVector);
			lenR = UDSearchR(i - 1, BVector);
			len = lenL + lenR + 1;
			if (len > maxLen) maxLen = len;
		}
	}
	lenR = UDSearchR(0, BVector) + 1;
	len = lenR;
	if (len > maxLen) maxLen = len;
	len = UDSearchL(upVector.size() - 1, BVector) + 1;
	if (len > maxLen) maxLen = len;
	cout << maxLen;

	return 0;
}