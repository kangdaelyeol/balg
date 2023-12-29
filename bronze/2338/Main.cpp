#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int i = 0;         // for loop를 위함
int maxInd = 0;    // 받은 vector의 큰 수를 가리기 위함
int interval = 4;  // 4라 가정, 10000 * 2는 1억이기 때문에 int 범위 안정함.
double tmpd = pow(10, interval);
int valForIndex = static_cast<int>(tmpd);

void checkVectorRange(vector<int>& a) {
	// vector 상위 0값 다듬기 -> 뺄셈 후 최상위 값이 0인 경우도 있기 때문에
	while (a[a.size() - 1] == 0 && a.size() > 1) {
		a.pop_back();
	};

	// 최종 index 제외 올려치기
	for (int t = 0; t < a.size() - 1; t++) {
		while (a[t] < 0) {
			a[t] += valForIndex;
			if (a.size() <= t + 1) a.push_back(0);
			a[t + 1]--;
		}

		while (a[t] >= valForIndex) {
			a[t] -= valForIndex;
			if (a.size() <= t + 1) a.push_back(0);
			a[t + 1]++;
		}
	}

	// 올려친 후 벡터 사이즈 체크 (올려치기 후 최상위 인덱스 값이 0 인 경우도 있어서)
	while (a[a.size() - 1] == 0 && a.size() > 1) {
		a.pop_back();
	};

	// 최종 인덱스 빼고 나머지는 양수이기 때문에, 마지막 인덱스로 양수값인지 음수 값인지 판단
	if (a[a.size() - 1] < 0 && a.size() > 1) {  // 음수인 경우 // 사이즈가 2이상 이어야 함
		a[a.size() - 1]++;                      // 최상위값을 1 더해줘야 나머지 - 할 수 있음

		for (int k = a.size() - 2; k > 0; k--) {  // 사이즈가 3 이상이면 실행
			a[k] -= (valForIndex - 1);            // 중간 값을 -999 해주고
		}
		a[0] -= valForIndex;  // 마지막 값에 1000 해줌, 사이즈가 1이면 실행 X
	}

	// 이후 기존 요소값이 0이었다면 요소에 -valForIndex값이 올 수 있기 때문에 이를 보정(마지막 인덱스 제외)
	for (int k = 0; k < a.size() - 1; k++) {
		if (a[k] == -valForIndex) {
			a[k] += valForIndex;
			a[k + 1]--;
		}
	}

	// Vector Size 다듬기 -> 최상위 요소가 0 인 경우도 있어서
	while (a[a.size() - 1] == 0 && a.size() > 1) {
		a.pop_back();
	};

	// for (int t = 0; t < a.size(); t++) {
	// 	// 각 요소들이 설정한 간격을 초과 하지 않도록 조정

	// 	// case 1 요소 값이 미만인 경우
	// 	for (int j = valForIndex * valForIndex / 10; j >= valForIndex; j /= 10) {
	// 		// 해당 자릿수가 -라면 + 될 때까지 앞의 요소에서 땡겨온다

	// 		int valForSubt = -valForIndex;
	// 		int tempj = j;
	// 		int valForAdd = -1;

	// 		while (tempj > valForIndex) {
	// 			tempj /= 10;
	// 			valForAdd *= 10;
	// 			valForSubt *= 10;
	// 		}

	// 		while (a[t] <= valForSubt) {
	// 			a[t] -= valForSubt;
	// 			if (t + 1 < a.size()) a.push_back(0);
	// 			a[t + 1] += valForAdd;
	// 		};
	// 	}

	// 	// case 2 요소 값이 초과 한 경우
	// 	for (int j = valForIndex * valForIndex / 10; j >= valForIndex; j /= 10) {
	// 		// 각 요소가 범위의 10제곱을 넘어 초과하면 loop 자원 소모가 크기 때문에 큰 자릿 수부터 체크 한다
	// 		// 가장 클 수 있는 범위 -> 10 * interval * (interval - 1)
	// 		// 해당 자릿수에 해당하는 만큼 빼주고 상위 요소에 그만큼 더해 주어야함
	// 		int valForSubt = valForIndex;
	// 		int tempj = j;
	// 		int valForAdd = 1;

	// 		// tempj(j) 현재 자릿수 검사 값이 크다면 moveIndex를 증가 해야 함
	// 		while (tempj > valForIndex) {
	// 			valForSubt *= 10;
	// 			valForAdd *= 10;
	// 			tempj /= 10;
	// 		};

	// 		while (a[t] >= valForSubt) {
	// 			a[t] -= valForSubt;
	// 			if (t + 1 > a.size()) a.push_back(0);  // 사이즈 업이 필요 한 경우, 조절해준다
	// 			a[t + 1] += valForAdd;                 // 10제곱한 만큼의 값을 더해준 만큼 10 곱해준 만큼의 값을 더해줌
	// 			cout << a[t];
	// 		}
	// 	}
	// }

	// 최종 조정 -> 양수값 조정에 에 의해 양수값이 MaxVal 초과 할 수도 있고 음수값이 중간 중간 남아 있기 때문에 이를 다 조정 해야함
	// 주의할 점은 최종 결과가 음수 일 수도 있기 때문에 마지막 요소는 검사하지 않는다, 따라서 배열 사이즈의 조정이 필요하지 않음.
	// for (int t = 0; t < a.size() - 1; t++) {
	// 	// 여기부턴 각 요소마다 가능한 범위는 얼마안되기 때문에 잘 조절하면 된다.

	// 	// 음수, 또는 valForIndex초과 검사 후 상위 index보정
	// 	if (a[t] < 0) {
	// 		a[t] += valForIndex;
	// 		a[t + 1]--;
	// 	} else if (a[t] >= valForIndex) {
	// 		a[t] -= valForIndex;
	// 		a[t + 1]++;
	// 	}
	// }

	// 1차 vector 상위 0값 다듬기 -> 만약 최종 결과, 최상위 값이 0인 경우도 있기 때문에
	// 최상위 결과 값이 0 이라면, 그 하위요소는 반드시 양수기 때문에 결과 값은 양수가 된다.

	// 최상위 값이 음수인 경우 -> 다른 값도 음수로 바꿔줘야 함
	// if (a[a.size() - 1] < 0) {
	// 	// 이 경우 최상위 값부터 내려가는것이 좋음
	// 	// 상위 1 -> 하위 1000 === 하위 999 + 하하위 1
	// 	// 즉 최하위index는 -1000값 주고 나머지 index에선 -999를 주어야 함.
	// 	a[a.size() - 1]++;
	// 	for (int q = a.size() - 1; q > 0; q--) {  // 2번째 상위 index 부터 2번째 하위 index까지
	// 		a[q] -= (valForIndex - 1);
	// 	}
	// 	a[0] -= valForIndex;

	// 	// 마지막 요소가 이미 0이었다면 또는 상위 요소들이 -(valforIndex - 1)이라면 하위값 에의해
	// 	// -valForIndex가 되기 때문에 이를 조정 (2번째 상위까지 계산)
	// 	for (int q = 0; q < a.size() - 1; q++) {
	// 		if (a[q] == -valForIndex) {
	// 			a[q] += valForIndex;
	// 			a[q + 1]--;
	// 		};
	// 	}
	// }

	// // 2차 vector 상위 0값 다듬기 -> 만약 최종 결과, 최상위 값이 0인 경우도 있기 때문에
	// while (a[a.size() - 1] == 0 && a.size() > 1) {
	// 	a.pop_back();
	// };
}

void printVector(vector<int>* a) {
	string result;

	// 해당 벡터 요소들을 String변환 한 후 interval에 맞게 0 padding 적용 시키기
	for (vector<int>::reverse_iterator rit = a->rbegin(); rit != a->rend(); ++rit) {
		// 첫 번째 요소는 padding이 필요 없기 때문에 실행 하지 않는다.
		int tmpRit = *rit;
		if (tmpRit < 0) tmpRit = -tmpRit;
		if (rit != a->rbegin() && to_string(tmpRit).length() < interval) {
			for (int k = 0; k < interval - to_string(tmpRit).length(); k++) {
				result += "0";
			}
			result += to_string(tmpRit);
		} else if (rit == a->rbegin()) {
			result += to_string(*rit);
		} else {
			result += to_string(tmpRit);
		}
	}

	cout << result << "\n";
}

int main() {
	string a, b, add, subtrack, multiply;
	cin >> a >> b;
	vector<int> av, bv, addv, subtrackv, multiplyv;
	int aStringRemain = a.length() % interval;
	int bStringRemain = b.length() % interval;
	// Vector에 정수 형태로 주는 작업
	// 이 것도 오름차순으로 자릿수 주기
	for (i = a.length(); i >= 0;) {
		i -= interval;
		if (i >= 0)
			av.push_back(stoi(a.substr(i, interval)));
		else if (i < 0 && i > -interval)
			av.push_back(stoi(a.substr(0, aStringRemain)));
	}

	// 이번엔 do - while을 사용해서 b값을 주어보겠다
	i = b.length();
	do {
		i -= interval;
		if (i >= 0)
			bv.push_back(stoi(b.substr(i, interval)));
		else if (i < 0 && i > -interval)
			bv.push_back(stoi(b.substr(0, bStringRemain)));
	} while (i >= 0);

	// 큰 vector size 계산
	if (av.size() >= bv.size())
		maxInd = av.size();
	else
		maxInd = bv.size();

	// 뺄셈(add 계산)
	for (int i = 0; i < maxInd; i++) {
		if (i > av.size() - 1)
			addv.push_back(-bv[i]);
		else if (i > bv.size() - 1)
			addv.push_back(av[i]);
		else
			addv.push_back(av[i] - bv[i]);
	}
	// vector validation check
	checkVectorRange(addv);

	printVector(&addv);

	// 출력부계산
	return 0;
}