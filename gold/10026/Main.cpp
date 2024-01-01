#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#define R 1;
#define G 2;
#define B 3;

using namespace std;
void searchArray(vector<vector<int> >& mIn, vector<vector<int> >& mS, vector<int>& sX, vector<int>& sY, int x, int y, int len) {
	int nowVal = mIn[y][x];
	if (x != 0) {
		int leftVal = mIn[y][x - 1];
		int searchedVal = mS[y][x - 1];
		if (leftVal == nowVal && searchedVal == 0) {
			sX.push_back(x - 1);
			sY.push_back(y);
			mS[y][x - 1] = 1;
		}
	}
	// 서
	if (x < len - 1) {
		int rightVal = mIn[y][x + 1];
		int searchedVal = mS[y][x + 1];
		if (rightVal == nowVal && searchedVal == 0) {
			sX.push_back(x + 1);
			sY.push_back(y);
			mS[y][x + 1] = 1;
		}
	}

	// 남
	if (y < len - 1) {
		int downVal = mIn[y + 1][x];
		int searchedVal = mS[y + 1][x];
		if (downVal == nowVal && searchedVal == 0) {
			sX.push_back(x);
			sY.push_back(y + 1);
			mS[y + 1][x] = 1;
		}
	}
	// 북
	if (y > 0) {
		int upVal = mIn[y - 1][x];
		int searchedVal = mS[y - 1][x];
		if (upVal == nowVal && searchedVal == 0) {
			sX.push_back(x);
			sY.push_back(y - 1);
			mS[y - 1][x] = 1;
		}
	}
}

int main() {
	int len;
	int ncnt = 0;
	int rcnt = 0;
	cin >> len;
	vector<vector<int> > matIn(len, vector<int>(len, 0));
	vector<vector<int> > matInr(len, vector<int>(len, 0));
	vector<vector<int> > matSr(len, vector<int>(len, 0));
	vector<vector<int> > matS(len, vector<int>(len, 0));
	vector<int> stackX, stackY;

	// RGB 값 받기
	for (int i = 0; i < len; i++) {
		string s;
		cin >> s;
		for (int l = 0; l < s.length(); l++) {
			switch (s.at(l)) {
			case 'R':
				matIn[i][l] = R;
				matInr[i][l] = R;
				break;
			case 'G':
				matIn[i][l] = G;
				matInr[i][l] = R;
				break;
			case 'B':
				matIn[i][l] = B;
				matInr[i][l] = B;
				break;
			}
		}
	}

	// 탐색하기 -- normal
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			bool isSearched;
			int nowVal = matIn[i][j];
			//  해당 위치 탐색 -> 이미 탐색 되면 false
			if (matS[i][j] == 1)
				isSearched = true;
			else {
				matS[i][j] = 1;
				// 해당 요소 주변 같은글자인지 탐색 -> 같으면 Push
				// 동
				if (j > 0) {
					int leftVal = matIn[i][j - 1];
					int searchedVal = matS[i][j - 1];
					if (leftVal == nowVal && searchedVal == 0) {
						stackX.push_back(j - 1);
						stackY.push_back(i);
						matS[i][j - 1] = 1;
					}
				}
				// 서
				if (j < len - 1) {
					int rightVal = matIn[i][j + 1];
					int searchedVal = matS[i][j + 1];
					if (rightVal == nowVal && searchedVal == 0) {
						stackX.push_back(j + 1);
						stackY.push_back(i);
						matS[i][j + 1] = 1;
					}
				}

				// 남
				if (i < len - 1) {
					int downVal = matIn[i + 1][j];
					int searchedVal = matS[i + 1][j];
					if (downVal == nowVal && searchedVal == 0) {
						stackX.push_back(j);
						stackY.push_back(i + 1);
						matS[i + 1][j] = 1;
					}
				}
				// 북
				if (i > 0) {
					int upVal = matIn[i - 1][j];
					int searchedVal = matS[i - 1][j];
					if (upVal == nowVal && searchedVal == 0) {
						stackX.push_back(j);
						stackY.push_back(i - 1);
						matS[i - 1][j] = 1;
					}
				}
				isSearched = false;
				while (!isSearched) {
					size_t stackSize = stackX.size();
					if (stackSize == 0) {
						isSearched = true;
					} else {
						int searchX = stackX.back();
						int searchY = stackY.back();
						stackX.pop_back();
						stackY.pop_back();
						searchArray(matIn, matS, stackX, stackY, searchX, searchY, len);
					}
				}
				ncnt++;
			}
		}
	}

	// 탐색하기 -- rdisability
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			bool isSearched;
			int nowVal = matInr[i][j];
			//  해당 위치 탐색 -> 이미 탐색 되면 false
			if (matSr[i][j] == 1)
				isSearched = true;
			else {
				matSr[i][j] = 1;
				// 해당 요소 주변 같은글자인지 탐색 -> 같으면 Push
				// 동
				if (j > 0) {
					int leftVal = matInr[i][j - 1];
					int searchedVal = matSr[i][j - 1];
					if (leftVal == nowVal && searchedVal == 0) {
						stackX.push_back(j - 1);
						stackY.push_back(i);
						matSr[i][j - 1] = 1;
					}
				}
				// 서
				if (j < len - 1) {
					int rightVal = matInr[i][j + 1];
					int searchedVal = matSr[i][j + 1];
					if (rightVal == nowVal && searchedVal == 0) {
						stackX.push_back(j + 1);
						stackY.push_back(i);
						matSr[i][j + 1] = 1;
					}
				}

				// 남
				if (i < len - 1) {
					int downVal = matInr[i + 1][j];
					int searchedVal = matSr[i + 1][j];
					if (downVal == nowVal && searchedVal == 0) {
						stackX.push_back(j);
						stackY.push_back(i + 1);
						matSr[i + 1][j] = 1;
					}
				}
				// 북
				if (i > 0) {
					int upVal = matInr[i - 1][j];
					int searchedVal = matSr[i - 1][j];
					if (upVal == nowVal && searchedVal == 0) {
						stackX.push_back(j);
						stackY.push_back(i - 1);
						matSr[i - 1][j] = 1;
					}
				}
				isSearched = false;
				while (!isSearched) {
					size_t stackSize = stackX.size();
					if (stackSize == 0) {
						isSearched = true;
					} else {
						int searchX = stackX.back();
						int searchY = stackY.back();
						stackX.pop_back();
						stackY.pop_back();
						searchArray(matInr, matSr, stackX, stackY, searchX, searchY, len);
					}
				}
				rcnt++;
			}
		}
	}

	cout << ncnt << " " << rcnt;
	return 0;
}