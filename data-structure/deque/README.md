# Deque & Monotonic Deque

## 1. Deque란?

Deque(Double Ended Queue)는 앞과 뒤 양쪽에서 삽입과 삭제가 가능한 자료구조이다.

일반적인 Queue는 뒤에서 삽입하고 앞에서 삭제하지만,  
Deque는 앞과 뒤 모두에서 삽입과 삭제가 가능하다.

---

## 2. Deque 기본 사용법

```cpp
#include <deque>

deque<int> dq;

dq.push_back(1);   // 뒤에 삽입
dq.push_front(2);  // 앞에 삽입

dq.pop_back();     // 뒤에서 삭제
dq.pop_front();    // 앞에서 삭제

dq.front();        // 맨 앞 원소
dq.back();         // 맨 뒤 원소

dq.empty();        // 비어있는지 확인
dq.size();         // 원소 개수
```

예를 들어,

```cpp
deque<int> dq;

dq.push_back(2);
dq.push_back(3);
dq.push_front(1);
```

Deque의 상태는 다음과 같다.

```text
[1, 2, 3]
```

---

# 3. Monotonic Deque란?

Monotonic Deque는 Deque 내부의 값이 계속 증가하거나 감소하는 형태를 유지하도록 관리하는 방법이다.

주로 Sliding Window에서 최솟값이나 최댓값을 빠르게 구할 때 사용한다.

- 최솟값을 구할 때 → 오름차순 유지
- 최댓값을 구할 때 → 내림차순 유지

---

## 4. 최솟값을 구하는 Monotonic Deque

예를 들어 현재 Deque가 다음과 같다고 하자.

```text
[3, 5, 8]
```

여기에 새로운 값 `4`가 들어온다.

`4`보다 큰 값들은 앞으로 최솟값이 될 가능성이 없으므로 뒤에서 제거한다.

```text
8 제거
5 제거
```

결과:

```text
[3, 4]
```

Deque는 계속 오름차순을 유지하게 된다.

따라서 맨 앞에는 현재 구간의 최솟값 후보가 위치한다.

---

## 5. 왜 큰 값을 제거해도 되는가?

현재 상태가 다음과 같다고 하자.

```text
[3, 5, 8]
```

여기에 새로운 값 `4`가 들어온다.

`5`, `8`은

- `4`보다 크고
- `4`보다 먼저 들어왔다.

따라서 앞으로 Sliding Window가 이동하더라도  
`5`, `8`이 `4`보다 먼저 최솟값이 될 수 없다.

즉, 더 작고 더 나중에 들어온 `4`가 존재하기 때문에  
`5`, `8`은 제거해도 된다.

결과:

```text
[3, 4]
```

---

## 6. Sliding Window에서 사용하는 이유

예를 들어 다음 배열이 있다고 하자.

```text
arr = [5, 3, 8, 2, 7]
k = 3
```

길이가 3인 구간의 최솟값을 구하면 다음과 같다.

```text
[5 3 8] -> 3
  [3 8 2] -> 2
    [8 2 7] -> 2
```

결과:

```text
3 2 2
```

각 구간을 직접 탐색하면 매번 `k`개의 값을 확인해야 한다.

```text
O(NK)
```

하지만 Monotonic Deque를 사용하면 각 원소가 최대 한 번 들어가고 한 번 제거되므로

```text
O(N)
```

에 처리할 수 있다.

---

## 7. 구현

실제로는 값 자체보다 인덱스를 Deque에 저장하는 경우가 많다.

```cpp
#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main() {
    vector<int> arr = {5, 3, 8, 2, 7};
    int k = 3;

    deque<int> dq;

    for (int i = 0; i < arr.size(); i++) {

        // 현재 Sliding Window 범위를 벗어난 인덱스 제거
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }

        // 현재 값보다 큰 값들은 최솟값 후보에서 제거
        while (!dq.empty() && arr[dq.back()] >= arr[i]) {
            dq.pop_back();
        }

        // 현재 인덱스 추가
        dq.push_back(i);

        // 길이 k의 Window가 완성되면 최솟값 출력
        if (i >= k - 1) {
            cout << arr[dq.front()] << " ";
        }
    }

    return 0;
}
```

출력:

```text
3 2 2
```

---

## 8. 왜 값이 아니라 인덱스를 저장하는가?

Sliding Window가 이동하면 Deque에 있는 원소가 현재 범위 안에 존재하는지 확인해야 한다.

예를 들어 현재 위치가 `i`이고 Window 크기가 `k`라면,

```cpp
dq.front() <= i - k
```

인 인덱스는 현재 Window 범위를 벗어난 값이다.

따라서 제거한다.

```cpp
dq.pop_front();
```

값 자체만 저장하면 해당 값이 언제 들어왔는지 알 수 없기 때문에  
현재 Window 범위를 벗어났는지 판단하기 어렵다.

그래서 일반적으로 인덱스를 저장한다.

---

## 9. Monotonic Deque 핵심 코드

### 최솟값을 구하는 경우

오름차순을 유지한다.

```cpp
while (!dq.empty() && arr[dq.back()] >= arr[i]) {
    dq.pop_back();
}

dq.push_back(i);
```

현재 구간의 최솟값은 다음과 같다.

```cpp
arr[dq.front()]
```

---

### 최댓값을 구하는 경우

내림차순을 유지한다.

```cpp
while (!dq.empty() && arr[dq.back()] <= arr[i]) {
    dq.pop_back();
}

dq.push_back(i);
```

현재 구간의 최댓값은 다음과 같다.

```cpp
arr[dq.front()]
```

---

## 10. 시간복잡도

Monotonic Deque에서는 각 원소가

- Deque에 최대 한 번 삽입되고
- Deque에서 최대 한 번 제거된다.

따라서 전체 시간복잡도는

```text
O(N)
```

이다.

---

## 11. 정리

### Deque

- 앞과 뒤 모두에서 삽입과 삭제가 가능
- `push_front()`, `push_back()`
- `pop_front()`, `pop_back()`
- `front()`, `back()`

### Monotonic Deque

- Deque 내부를 오름차순 또는 내림차순으로 유지
- Sliding Window의 최솟값 또는 최댓값을 빠르게 구할 때 사용
- 일반적으로 값보다 인덱스를 저장
- 최솟값 → 오름차순 유지
- 최댓값 → 내림차순 유지
- 시간복잡도 `O(N)`