# 문제 1271 - 큰 수 나눗셈

## C++

- **C++ 에서는 큰 수 처리에 대한 라이브러리가 없다. 그래서 직접 배열을 선언해서 workflow를 구현 해야 했다.**
  <br/><br/>
- 작업순서
  1. [큰 수 String으로 받기](#1-큰-수-string으로-받기)
  2. [일정 간격으로 나눠서 배열로 주기](#2-일정-간격으로-나눠서-배열로-주기)
  3. [나눌 수 있는지 판단하기](#3-나눌-수-있는지-판단하기)
  4. [나누기](#4-나누기)
  5. [배열의 값을 정수에서 String형태로 바꿔 합치기](#5-배열의-값을-정수에서-string형태로-바꿔-합치기)
     <br/><br/>

### 1. 큰 수 String으로 받기

```cpp
  #include<iostream>
  #include<string>
  #include<vector>
  using namespace std;
  string n, m, q, r; // input(n, m) / output(q, r)
  cin >> n, m;
  vector<int> nv, mv, qv;
```

### 2. 일정 간격으로 나눠서 배열로 주기

#### 2-1 어떤 간격으로 나눠줄 지 임의로 정한다

```cpp
#include<cmath>
  int interval = 3; // 임의로 3

  // interval은 각 배열마다 주는 자리수
  // 그 자리수의 최대 값을 구한다
  // 배열을 3자리 수로 한다면 해당 3자리의 최대값은 999(1000) / 10의 3제곱
  double valTemp = pow(10, interval);
  int valForIndex = static_cast<int>(valTemp);

```

<hr />

#### 2-2 배열로 나눠주는데 여기서 낮은 인덱스로 낮은 자리수로 줄 것인지, 큰 인덱스로 낮은 자리 수를 줄 것인지 결정한다<br/>

#### 본문에서는 낮은 인덱스가 낮은 자리수를 주는 것으로 한다.

- 여기서 subStr길이를 맞추기 위해 간격에 따른 나머지 문자열의 길이가 필요함 / nStrRemain

```cpp
  int nStrRemain = n.length() % interval;
  for(int i = n.length(); i < 0; ){
    i -= interval; // 우선 길이를 입력할 interval만큼 i에서 먼저 참
    // 차감 후 i 위치 검사하는 방식

    // case1: 마지막 index -> 음수면서 -interval보다 큰 경우
    if(i < 0 && i > -interval) {
      nv.push_back(stoi(n.substr(0, nStrRemain)));
    // case2: 마지막 index가 아닌경우 -> 0 이상인 경우
    } else if(i >= 0) {
      nv.push_back(stoi(n.substr(i, interval)))
    }
  }
```

<hr />

### 3. 나눌 수 있는지 판단하기

- **나누기: 기존 값에서 나눗셈 값만큼 빼고 몫값 증가 시키기**

#### 3-1 nVector 배열의 크기가 mVector 크기 보다 큰경우

- m을 n의 최상위 위치로 조정해서 차감 할 수 있는지 체크 해야한다. 이렇개 해야 빠르게 연산이 가능

1.  n최상위 값이 m보다 큰 경우 - 무조건 차감이 가능하다
1.  n최상위 값이 m이랑 같은 경우 - 밑에 인덱스 값도 비교해서 값이 mv보다 커야 한다.
1.  n최상위 값이 m보다 작은 경우 - 최상위 위치에 조정해서 차감 불가 -> 최상위 index - 1 위치에서 차감

```cpp
  if(nv.size() > mv.size()){
    // nv가 큰지 판단할 수 있는 bool변수 정의
    bool isNvLarge = true;
    // 배열 index 차이나는 값만큼 moveIndex값 설정
    // 만약 nv의 최상위 위치 값이 mv보다 크면 최상위 뺄셈을 한다.
    if(nv[nv.size() - 1] == mv[mv.size() - 1]){
      for(int i = 0; i < mv.size(); i++){
        // 하위 값을 돌며 nv가 크면 break문으로 더이상 for문으로 체크 하지 않는다.
        if(nv[nv.size() - 1 - i] > mv[mv.size() - 1 - i]) {
          break;
          // 같으면 continue를 통해 다시 for문 체크 한다.
        } else if(nv[nv.size() - 1 - i] == mv[mv.size() - 1 - i]){
          continue;
        }else {
          isNvLarge = false;
        };
      };
    } else if(nv[nv.size() - 1] > mv[mv.size() - 1]){
      isNvLarge = true;
    } else {
      isNvLarge = false;
    };

    // nv 최상위가 mv최상위랑 맞췄을때 뺄 수 있는 경우
    if(isNvLarge == true){
      moveIndex = nv.size() - mv.size();
    } else {
      // Nv가 크지 않으면 하나 밑으로 해서 계산
      moveIndex = nv.size() - mv.size() - 1;
    };
    canDivide = true;
  };
```

#### 3-2 nv크기와 mv크기와 같은 경우

- [3-1](#3-1-nvector-배열의-크기가-mvector-크기-보다-큰경우)과정과 유사한 연산울 하는데, mv의 위치를 조정하는 변수값은 조정 하지 않는다.

<hr />

### 4. 나누기

- 나눌 수 있는지 알려주는 변수를 검사 한 후, mv를 옮길만큼 옮긴 후 차감 후 몫에 값을 더해준다

- 차감 작업을 할때는 오름차순, 내림차순 순서는 관계 없지만, 연산 후 그 자리 값이 음수인 경우를 반드시 체크 해야 한다.

#### 4-1 차감 작업

- 음수값 체크 후 음수이면 해당 자리수에 맞는 10진수 값을 더해주고 상위 요소 값에서 1 값을 빼야 한다.

- 음수값 검사 할 때는 오름차순으로 해야 한다. 하위 값에 의해 상위값이 0에서 -1로 변할 수 있기 때문

```cpp
    // index를 0부터 증가시켜 mv의 낮은 위치 값부터 감소 시킨다
  for (int i = 0; i < mv.size(); i++) {
    // moveIndex가 있다면 해당 위치만큼 이동 시키고
    nv[i + moveIndex] -= mv[i];
    // 만약 해당 자리수가 음수면, 다시 채우고, 다음 자리수 - 1 하기
  };

  // 이후 감소시킨 nv 요소 위에 값이 -1인 경우도 있다 ex [1, -1, 999], 이를 보정해줌
  for (int i = 0; i < nv.size(); i++) {
    if (nv[i] < 0) {
      nv[i] += valForIndex;
      nv[i + 1]--;
    };
  };
```

#### 4-2. vector 사이즈 조정

- 차감 후 최상위 벡터의 값이 0이라면 사이즈를 조정해 줘야 한다.

```cpp
    // 이후 최상위 nv요소가 0이라면 사이즈 줄이기
  while (nv[nv.size() - 1] == 0 && nv.size() > 1) {
    nv.pop_back();
  };
```

#### 4-3 몫 추가

- 몫 벡터 qv에 몫을 추가해준다

- mv차감시 인덱스를 옮겨서, 즉 자리수를 높혀서 차감했다면 몫도 해당 자릿수만큼 위로 올겨서 더해주어야 한다.

- 이 작업 또한 마찬가지로 자릿수의 최대 10진수 값을 넘긴다면 상위 요소에 1을 더해주어야 한다.

```cpp
    // 해당 vector의 index위치에 몫 추가
  qv[moveIndex]++;
  if (qv[moveIndex] >= valForIndex) {
    qv[moveIndex + 1]++;
    qv[moveIndex] -= valForIndex;
  }
```

<hr />

### 5. 배열의 값을 정수에서 String형태로 바꿔 합치기

- 배열(Vector)의 값을출력할 String형태로 바꾸어주고 합쳐야한다.

#### 5-1 Vector값 순서대로 불러오기

- Vector저장된 요소는 최상위 요소(마지막 index 요소)가 String에 첫 번째로 와야 한다.

- Vector<int>::reverse_iterator 형 반복자를 사용해야한다.

#### 5-2 '0'값 padding 추가하기

- Vector 요소의 값이 자릿수보다 작은 자릿수면 0 패딩을 추가해야 String형에서 자릿수가 맞춰진다 Ex) 30(int) -> "0030"(String) // 자릿수(interval)가 4인 경우

- 최상위 요소는 0 padding이 필요하지 않으니 최상위 요소를 제외하고 나머지 요소의 길이와 interval과 비교 후 작으면, 그 개수만큼 0을 추가 한다.

```cpp
  // 모든 계산이 끝난 후 -> vector 요소를 string에 추가해 주어야 함
  for (vector<int>::reverse_iterator rit = qv.rbegin(); rit != qv.rend(); ++rit) {
  // 자릿수가 interval만큼이 아니면 그만큼 뒤로 0 패딩 붙혀줘야함
  // 하지만 첫 요소이면 실행 x
  // rend()는 참조자의 참조 인덱스 위치가 아니고, 시작 이전의 위치를 가리키기 때문에 반복, 조건문의 끝 조건으로 사용됨
   if (rit != qv.rbegin() && to_string(*rit).length() != interval) {
    for (int i = 0; i < interval - to_string(*rit).length(); i++) {
      q += "0";
    };
  };
  q += to_string(*rit);
};
```

<hr />

## Java

### java.math 패키지의 BigInteger클래스를 이용하면 간단히 해결할 수 있더라.

```java
  import java.math.*;
  import java.util.*;

  public static void main(String args[]){
    Scanner sc = new Scanner(System.in);

    // 스캐너에서 BigInteger 인스턴스를 받아오는 메서드도 있다
    BigInteger n = sc.nextBigInteger();
    BigInteger m = sc.nextBigInteger();

    BigInteger quotient = n.devide(m); // n / m과 같음
    BigInteger remainder = n.remainder(m); // n % m 과 같음
  };
```

<hr />

## Python

### 파이썬은 큰 수 상관없이 알아서 처리해 줬음. 제일 간단함.
