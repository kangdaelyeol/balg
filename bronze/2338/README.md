# 문제 2338 - 큰 수 덧셈 / 뺄셈 / 곱셈

## C++

- **큰 값을 처리 하는 라이브러리가 없어서 직접 큰수를 처리하는 로직을 설계해 보았다**
  <br/><br/>
- 작업 순서
  - [1. 큰 수 String으로 받기](#1-큰-수-string으로-받기)
  - [2. Vector로 일정 간격씩 나눠 저장](#2-vector로-일정-간격씩-나눠-저장)
  - [3. Vector연산](#3-vector연산)
  - [4. 배열 요소 값 범위 체크](#4-배열-요소-값-범위-체크)
  - [5. 값 출력](#5-값-출력)

<hr><br/>

### 1. 큰 수 String으로 받기

- 큰 수를 간단히 string으로 받는다.

  ```cpp
    #include<string>

    string a, b;
    cin >> a >> b;
  ```

<hr><br/>

### 2. Vector로 일정 간격씩 나눠 저장

- **vector<int>에 저장되기 때문에 String을 int로 변환 하여 저장해야한다.**
  - [2-1 음수 값이 주어질 때](#2-1-음수-값이-주어질-때)
  - [2-2 앞에 0 값이 주어질 때](#2-2-앞에-0-값이-주어질-때)
  - [2-3 배열에 저장 가능한 최대 초깃 값](#2-3-배열에-저장-가능한-최대-초깃-값)

#### **2-1 음수 값이 주어질 때**

1. 값 체크

   - substr로 String값을 나눠서 int로 변환하여 배열에 저장해야 한다.

   - 일정 간격으로 저장했을때, 최초 요소에 '-'값만 int형으로 저장되는 경우가 있었다. 그래서 '-' 값이 있다면 따로 음수값을 체크하는 flag를 정의했다.

   ```cpp
     bool isMinusa = false;
     bool isMinusb = false;
   ```

   - 받은 String이 음수라면 안전한 배열 저장을 위해 '-'값을 미리 지우고, flag를 바꾼다

   ```cpp
   if(a.at(0) == '-') {
     isMinusa = true;
     a = a.substr(1, a.length() - 1);
   }
   ```

1. 음수 값을 배열로 저장

- 음수값이 배열로 저장 된다면, 모든 배열 요소가 음수가 되어야 한다.
  ```cpp
    string a = "-123456"; // 이런 문자열이 있으면
    vector<int> vectorA = { -12, -34, -56 } // 이렇게 저장이 되어야 한다
  ```
- '-'로 시작하는 String을 배열로 나눠서 음수로 저장한다면 최상위 제외 하위 인덱스는 양수 값이 저장이 되기 때문에 이를 보정, 이를 위해 isMinus 플레그가 필요
  ```cpp
    int length = a.length();
    int interval = 3; // 간격, 배열에 저장될 정수의 자릿수
    int remainIndex = length % 3;
    for(int i = length; i <= 0; ){
      int storeVal;
      i -= interval;
      if(i >= 0) {
        storeVal = stoi(a.substr(i, interval));
        if(isMinusa) storeVal = -storeVal; // 음수 flag인 경우 음수값으로 저장
        vectorA.pushback(storeval);
      } else if(i < 0 && i > -interval) {
        storeVal = stoi(a.substr(0, remainIndex));
        if(isMinusa) storeVal = -storeVal;
        vectorA.push_back(storeVal);
      }
    }
  ```

#### **2-2 앞에 0 값이 주어질 때**

- 맨 앞 갚에 0이 주어지면 String은 이를 그대로 저장함

- 하지만 정수형은 이를 생략하므로 String상에서도 전처리를 해준다

- 이 과정은 Minus Flag 체크 후 배열에 분배 하기 전에 진행

  ```cpp
   /*
     ... minus flag check
   */
   while(a.at(0) == '0' && a.length() > 1) { // 최소 사이즈는 1이 되어야 하므로
     a = a.substr(1, a.length() - 1);
   }
   /*
       배열에 값 분배하기 ...
   */
  ```

#### **2-3 배열에 저장 가능한 최대 초깃 값**

- 각 배열은 n자릿수의 int형 정수를 받는다.

- 한 단위의 계산을 하는데, 2^31(2147483647 / 양수 기준)값을 초과해선 안된다.

  ```cpp
  // 가능한 정수의 최댓값 = 9999...999 (1000자리수)
  // 정수를 저장하는 배열의 최대 길이 = 1000 / interval (나머지가 있는 경우 + 1)
  // 계산된 정수가 저장되는 배열의 최대 길이(곱셈의 경우) = (1000 / interval) * 2
  /*
   배열에 저장 될 수 있는 최댓값 - 곱셈하는 경우
   n길이 배열과 m길이 배열을 곱셈 하려면 n * m횟수 곱셈을 해야함
   배열 곱셈을 하는데 가장 많은 계산 횟수가 저장 되는 배열의 index = (n + m) / 2 (n + m이 홀수면 중앙, 짝수면 중앙 2칸)
   해당 index에 저장되는 계산 횟수 calCount = (n + m) / 2
   index에 저장 될 수 있는 최대값
   maxVal = calCount * (10 ** interval - 1) ** 2
    === ((n + m) / 2) * (10 ** interval - 1) ** 2
    === (((1000/interval * 2) / 2)) * (10 ** interval - 1) ** 2

   --- interval = 4인 경우 ---
   최댓값 = 250 * (9999 ** 2) -> 약 250억 정도 (21억 초과)

   --- interval = 3인 경우
   최댓값 = 334 * (999 ** 2) -> 약 3.34억 정도

   * 결론: 최대 배열에 저장 가능한 자릿수는 3자리
  */
  int interval = 3;
  ```

<hr><br/>

### 3. Vector연산

- **Vector 연산 결과를 각 목적에 맞게 선언된 Vector에 저장**

  - [3-1 덧셈, 뺄셈 연산](#3-1-덧셈-뺄셈-연산)

  - [3-2 곱셈 연산](#3-2-곱셈-연산)

#### **3-1 덧셈 뺄셈 연산**

- Vector의 동일한 index에 맞게 연산을 해줌

- 두 Vector의 size가 다른 경우

  - 두 Vector의 size가 다른 경우 for문을 통한 index참조시 잘못된 위치를 참조할 수 있기 때문에 이를 처리해줌

    ```cpp
      size_t maxSize;
      if(a.size() >= b.size()) maxSize = a.size();
      else maxSize = b.size();

      for(size_t i = 0; i < maxSize; i++) {
        if(maxSize > a.size()){ // vectorA 범위 초과시
          addResult.push_back(b[i]);
          subtrackResult.push_back(-b[i]); // A - B 연산 이기 때문에 -B를 준다
        }
        else if(maxSize > b.size())  { // vectorB 범위 초과시
          addResult.push_back(a[i]);
          subtrackResult.push_back(a[i]);
        }
        else{
          addResult.push_back(a[i] + b[i]);
          subtrackResult.push_back(a[i] - b[i]);
        }
      }
    ```

#### **3-2 곱셈 연산**

- 곱셈의 경우 각 피연산자의 자릿수들이 모두 곱셈이 되어야 한다

- 그래서 2중 for문을 통해 모든 자릿수끼리 곱셈한 후, 그 위치에 값을 더해준다

  ```cpp
   for(size_t i = 0; i < a.size(); i++){
     for(size_t j = 0; j < b.size(); j++){
        multiplyResult[i + j] += a[i] * b[j]; // 큰 수를 일정 간격으로 나눴으므로 건너뛴 index만큼 추가해서 그 위치에 결과 값을 더해준다
     }
   }
  ```

<hr><br/>

### 4. 배열 요소 값 범위 체크

- **계산 결과 값이 저장된 배열 요소값의 범위 검사, 조정**

  - **3자리 간격(interval = 3)으로 저장된 배열의 허용 정수 범위는 (-999 ~ 999) 이므로 초과된 값을 보정해준다**

  - [4-1 양수값 보정](#4-1-양수값-보정)

  - [4-2 양수값 초과 검사](#4-2-양수값-초과-검사)

  - [4-3 음수값 검사](#4-3-음수값-검사)

  - [4-4 음수값 초과 검사](#4-4-음수값-초과-검사)

#### **4-1 양수값 보정**

- 결과 값이 음수라면 양수로 보정해준다

- 최상위 요소가 음수라면 계속 양수값 보정이 일어나기 때문에 최상위 인덱스는 검사하지 않는다

  ```cpp
  double powValue = pow(10, interval);
  int maxValueForInterval = static_cast<int>(powValue);
  for(size_t i = 0; i < resultV.size() - 1; i++) {
    if(resultV[i] < 0){
      resultV[i] += maxValueForInterval;
      resultV[i + 1]--;
    };
  }

  // 이후 최상위 요소값이 0이면 필요 없는 값이므로 보정해줌 - 0값 검사
  while(resultV[resultV.size() - 1] && result.size() > 1)
    resultV.pop_back();
  ```

#### **4-2 양수값 초과 검사**

- 초과한 양수 값에 대한 보정을 해준다

- 최상위 인덱스도 초과하므로 검사를 해준다

- 최상위 인덱스에서 초과가 발생한 경우 동적으로 size를 추가 해준다

- 곱셈 연산 결과의 경우 여러 번 초과가 될 수 있으므로 while문을 사용

  ```cpp
   for(size_t i = 0; t < result.size(); t++) {
    while(result[i] >= maxValueForInterval) {
      result[i] -= maxValueForInterval;
      if(i + 1 > result.size()) result.push_back(0);
      result[i + 1]++;
    }
   }
  // 이후 최상위 요소값이 0이면 필요 없는 값이므로 보정해줌 - 0값 검사
  // ...

  ```

#### **4-3 음수값 검사**

- 최상위 값이 음수라면 모든 index값이 음수값이어야 함

- 현재 단계에서 최상위 제외 모든 값이 양수이므로 이를 검사해준다

- 음수 값이면 최상위 값을 더한 후 나머지 index로 음수값을 주어야 한다

  ```cpp
    if(result[i] < 0 && result.size() > 1) { // size가 2이상인 경우 수행
      result[result.size() - 1]++;
      for(int i = 1; i < result.size() - 1; i++) { // 최상위 제외, 중간 배열 범위
        result[i] -= (maxValueForInterval - 1);
      };
      result[0] -= maxValueForInterval; // 첫 요소는 Max값을 준다 (-1000000 == -999999 + -1)
    }
  ```

#### **4-4 음수값 초과 검사**

- 배열의 첫 index에 Max값을 주었으므로, 기존 값이 0이라면 -Max 값이 되므로 결국 초과하게 된다.

  ```cpp
    //ex
    vector<int> a = {-2, 0, 0, 0, 0}; // 기존 배열
    vector<int> b = {-2, 500, 100, 3, 0}; // 기존 배열

    // ... 음수값 검사 이후

    a = {-1, -999, -999, -999, -1000} // interval = 3 가정
    b = {-1, -499, -899, -996, -1000}
  ```

  - 즉 기존 값이 0 이었는지 검사가 필요함
  <hr>

- 최종적으로 음수값이 초과 하는지 검사해 준다, 만약 기존 값이 0값이라면 원래대로 돌아온다

  ```cpp
    for(int i = 0; i < result.size() - 1; i++){
      if(result[i] == -maxValForInterval) {
        result[i] += maxValForInterval;
        result[i + 1]--;
      }
    }
  ```

<hr><br/>

### 5. 값 출력

- **최종 연산 결과를 string형으로 변환 해야 한다**

  - [5-1 음수값 검사](#5-1-음수값-검사)

  - [5-2 0 padding 추가](#5-2-0-padding-추가)

#### **5-1 음수값 검사**

- 연산 결과가 음수인 경우 모든 index가 - 값이므로 '-'문자 자체도 String에 들어간다

- 최상위 index만 '-'을 String에 주어야 하므로 절대값을 나타내는 변수를 따로 정의 한다

  ```cpp
   string resultString; // 결과 String이 저장될 String
   for(vector<int>::reverse_iterator rit = result.rbegin(); rit != result.rend(); ++rit) {
     int ritVal = *rit;
     if(ritVal < 0) ritVal = -ritVal;
     string insertVal = to_string(ritVal); // String에 삽입될 값
   }
  ```

#### **5-2 0 padding 추가**

- 최상위 제외 모든 index값은 interval자리수를 지켜야 String에 삽입될 수 있다

- interVal = 3인 경우, 최상위 제외 임의index값이 1, 2자리 인경우 뒤에 0은 생략되어버린다. 이를 보정한다

  ```cpp
    if(rit != result.rbegin()){ // 최상위 index가 아닌경우
      for(int k = insertVal.length; k < interval; k++)
        resultString += "0"; // 모자란 수 만큼 '0' padding 추가
      resultString += insertVal; // 이후 값 추가
    } else { // 최상위 index인 경우
      resultString += to_string(*rit);
    }
  ```
