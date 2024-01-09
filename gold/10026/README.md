# 10026 적록색약

### n x n / RGB 세값으로 이루어진 그리드에서 구역 나누기

- 적록색약을 가진 사람은 R, G를 구분할 수 없어서 같은 색상이라 취급

- 일반인 / 적록색약이 보았을때 나눌 수 있는 구역의 수 구하기

## Python

- 작업 순서
  - [1. 입력 받기](#1-입력-받기)
  - [2. 탐색 하기](#2-탐색하기)

<hr /><br />

### 1. 입력 받기

**가로 세로 길이가 될 n값과 n개의 줄을 입력 받아 저장**

- RGB값을 저장할 list와 탐색 완료를 구분하는 flag를 위한 list를 생성
- list를 재사용 하려 했는데, python에서도 변수가 같은 주소값을 참조하도록 되어 있어서(shallow copy) 따로 list를 만들어야함

  ```python
    n = int(input())
    color_array = []
    color_rarray = []
    trav_array = []
    for i in range (0, n, 1):
      color = input()
      color_line = []
      trav_line = []
      for c in range(color):
        color_line.append(c)
        trav_line.append(False)
      color_array.append(color_line)
      trav_array.append(trav_line)
  ```

- 적록색약은 R과 G를 구분하지 못해서 같은 색으로 통합 하여 새로 생성

  ```python
    for(i in range(len(color_array))):
      color_rarray[i] = color_array[i].replace("R", "G") # R과 G를 같은 색상 취급
  ```

<hr /><br />

### 2. 탐색하기

**그리드 요소를 순차적으로 탐색해서 영역을 구분**

- [2.1 list 생성](#21-list-생성)

- [2.2 첫 위치 탐색](#22-첫-위치-탐색)

- [2.3 주변 위치 탐색](#23-주변-위치-탐색)

#### **2.1 list 생성**

- 탐색 위치(x, y)가 저장될 `stack`을 생성함, 탐색 지점에서 탐색 가능한 위치를 저장 해서 DFS빙식으로 탐색 하기 위함

  ```python
    location_list = []
  ```

#### **2.2 첫 위치 탐색**

- 모든 위치를 순차적으로 탐색 하는데, 기준점 위치 탐색 후 list의 size값을 검사하는 방식으로 종료를 구분한다.

- 기준 위치 탐색 후 while문을 사용하는 방식(do-while)

  ```python
    for i in range(n):
      for j in range(n):
        # 기준 위치는 [i][j]
        # 탐색 가능하면 탐색 후 순회(traversal)
        if(not trav_list[i][j]):
          location_list.append([i, j]) # 탐색 가능한 위치 정보 저장
          color = color_list[i][j] # 현재 색 정보
          while(len(location_list) != 0):
            next_location = location_list.pop() # 다음 탐색 위치 pop
            next_y = next_location[0]
            next_x = next_location[1]
            traversal(next_y, next_x) # 다음 탐색할 위치를 탐색한다
  ```

#### **2.3 주변 위치 탐색**

- 현재 위치에서 주변을 탐색하는데, 탐색이 가능한 위치이고, 색이 같으면 탐색 stack에 push한다

  ```python
    def traversal(y, x):
      trav_list[y][x] = True
      now_color = color_list[x][y]
      # 동서남북 으로 조건 탐색 후 location_list에 push
      for a in range(1, -2 , -2):
        for b in range(1, -2, -2): # 동 서 남 북 총 4 위치 탐색
          if(0 <= y + a < len(list) and 0 <= x + b < len(list) and not trav_list[y + a][x + b] and now_color == color_list[y + a][x + b]):
            location_list.append([y + a, x + b]) # 위치값을 stack에 push
  ```
