/*
문제
갑부 최백준 조교는 동전을 최소로 바꾸는데 성공했으나 김재홍 조교가 그 돈을 발견해서 최백준 조교에게 그 돈을 나누자고 따진다.

그 사실이 전 우주로 알려지자 우주에 있던 많은 생명체들이 자신들에게 돈을 분배해 달라고 당장 달려오기 시작했다.

프로토스 중앙 우주 정부의 정책인, ‘모든 지적 생명체는 동등하다’라는 규칙에 입각해서 돈을 똑같이 분배하고자 한다.

한 생명체에게 얼마씩 돈을 줄 수 있는가?

또, 생명체들에게 동일하게 분배한 후 남는 돈은 얼마인가?

입력
첫째 줄에는 최백준 조교가 가진 돈 n과 돈을 받으러 온 생명체의 수 m이 주어진다. (1 ≤ m ≤ n ≤ 101000, m과 n은 10진수 정수)

출력
첫째 줄에 생명체 하나에게 돌아가는 돈의 양을 출력한다. 그리고 두 번째 줄에는 1원씩 분배할 수 없는 남는 돈을 출력한다.
 */

#include<iostream>
#include<string>
#include<vector>
#include<typeinfo>
#include<cmath>

using namespace std;
int main() {
  int interval = 3;
  bool isFinish = false;
  string n, m, q, r;
  vector<int> nv, mv, qv;
  cin >> n >> m;
  // vector 입력
  // 초기 vector 길이
  int nStrRemain = n.length() % interval;
  int mStrRemain = m.length() % interval;
  double valForIndexD = pow(10, interval);
  int valForIndex = static_cast<int>(valForIndexD);

  for(int i = n.length(); i >= 0; ) {
    i -= interval;
    if(i < 0 && i > -interval) {
        nv.push_back(stoi(n.substr(0, nStrRemain)));
    } else if(i >= 0){
        nv.push_back(stoi(n.substr(i, interval)));
    };
  };

  for(int i = m.length(); i >= 0; ) {
    i -= interval;
    if(i < 0 && i > -interval) {
      mv.push_back(stoi(m.substr(0, mStrRemain)));
    } else if(i >= 0){
      mv.push_back(stoi(m.substr(i, interval)));
    };
  }

    while(qv.size() <= nv.size() - mv.size()){ // 자리수 갱신 -> 초기에만 한 번 호출
    qv.push_back(0);
  };



  while(!isFinish){
    // 나눌 수 있을 때 -> 차감할 수 있을 때
    bool canDivide = false;
    int moveIndex = 0;


    // 나눗셈 체크
    // case 1 -> nv 크기보다 mv 크기가 큰 경우
    // case 2 -> nv랑 mv 크기 같은 경우

    // case 1 -> nv 크기보다 mv 크기가 큰 경우
    if(nv.size() > mv.size()){
      bool isNvLarge = true;
      // 배열 index 차이나는 값만큼 moveIndex값 설정
      // 만약 nv의 최상위 위치 값이 mv보다 크면 최상위 뺄셈을 한다.
      if(nv[nv.size() - 1] == mv[mv.size() - 1]){
        for(int i = 0; i < mv.size(); i++){
          // 한 자리 수라도 mv가 크다면 
          if(nv[nv.size() - 1 - i] < mv[mv.size() - 1 - i]) {
            isNvLarge = false;
          };
        };
      } else if(nv[nv.size() - 1] > mv[mv.size() - 1]){
        isNvLarge = true;
      } else {
        isNvLarge = false;
      }

      // nv 최상위가 mv최상위랑 맞췄을때 뺄 수 있는 경우
      if(isNvLarge == true){
        moveIndex = nv.size() - mv.size();
      } else {
        // Nv가 크지 않으면 하나 밑으로 해서 계산
        moveIndex = nv.size() - mv.size() - 1;
      };
      canDivide = true;
    };

   // case 2 -> nv랑 mv 크기 같은 경우
   // 이 경우도 모든 index값에 대해 계산 해야함
   // 최상위가 같아도 하위가 mv가 크다면 에러가 뜨기 때문
    if(nv.size() == mv.size()) {
      bool isNvLarge = true;

      if(nv[nv.size() - 1] == mv[mv.size() - 1]){
        for(int i = 0; i < mv.size(); i++){
          if(nv[i] < mv[i]){
            isNvLarge = false;  
          };
        };
      } else if(nv[nv.size() - 1] < mv[mv.size() - 1]){
        isNvLarge = false;
      };

      if(isNvLarge == true) {
        canDivide = true;
      } else{ 
        canDivide = false;
      };
    };

    // 나누기
    if(canDivide == true) {
      // index를 0부터 증가시켜 mv의 낮은 위치 값부터 감소 시켜야 한다.
      for(int i = 0; i < mv.size(); i++) {
        // moveIndex가 있다면 해당 위치만큼 이동 시키고
        nv[i + moveIndex] -= mv[i];
        // 만약 해당 자리수가 음수면, 다시 채우고, 다음 자리수 - 1 하기
      };
    
    
      // 이후 감소시킨 nv 요소 위에 값이 -1인 경우도 있다 ex [1, -1, 999], 이를 보정해줌
      // 다 검사 한다
      for(int i = 0; i < nv.size(); i++) {
        if(nv[i] < 0) {
          nv[i] += valForIndex;
          nv[i + 1]--;
        };
      };

     
      // 이후 최상위 nv요소가 0이라면 사이즈 줄이기
      while(nv[nv.size() - 1] == 0 && nv.size() > 1) {
        nv.pop_back();
      };

  
      // 해당 vector의 index위치에 몫 추가
      qv[moveIndex]++;
      if(qv[moveIndex] >= valForIndex) {
        qv[moveIndex + 1]++;
        qv[moveIndex] -= valForIndex;
      }

      // 배열 nv.size() 갱신 - 기존 배열 값이 0인 경우 의미 없기 때문
      // 조건1: nv size는 1이상 -> 2이상 일떄만 가능
      // 조건2: 최상위 위치 배열 값이 0인경우
    } else {
      isFinish = true;
    };
      canDivide = false;
  };


    // 마무리 단계, 모든 나누기 과정이 끝난 후 벡터 다듬기 (최상위 0들 지우기)
    while(nv[nv.size() - 1] == 0 && nv.size() > 1) {
      nv.pop_back();
    };

    while(qv[qv.size() - 1] == 0 && qv.size() > 1){
      qv.pop_back();
    };

  // 모든 계산이 끝난 후 -> vector 요소를 string에 추가해 주어야 함
  for(vector<int>::reverse_iterator rit = qv.rbegin(); rit != qv.rend(); ++rit){
    // 자릿수가 interval만큼이 아니면 그만큼 뒤로 0 패딩 붙혀줘야함
    // 하지만 첫 요소이면 실행 x
    if(rit != qv.rbegin() && to_string(*rit).length() != interval) {
      for(int i = 0; i < interval - to_string(*rit).length(); i++) {
        q += "0";
      };
    };
      q += to_string(*rit);
  };
  // rend()는 참조자의 참조 인덱스 위치가 아니고, 시작 이전의 위치를 가리키기 때문에 반복, 조건문의 끝 조건으로 사용됨
  for(vector<int>::reverse_iterator rit = nv.rbegin(); rit != nv.rend(); ++rit){
    if(rit != nv.rbegin() && interval > to_string(*rit).length()) {
      for(int i = 0; i < interval - to_string(*rit).length(); i++){
        r += "0";
      };
    };
    r += to_string(*rit);
  };

  cout << q << "\n" << r;
  return 0;
}