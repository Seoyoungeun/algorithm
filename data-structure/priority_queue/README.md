# Priority Queue

## 1. Priority Queue란?

Priority Queue는 일반적인 Queue와 달리  
먼저 들어온 순서가 아니라 **우선순위가 높은 원소부터 꺼내는 자료구조**이다.

C++의 `priority_queue`는 기본적으로 **가장 큰 값이 먼저 나오는 최대 힙(Max Heap)** 으로 동작한다.

---

## 2. 기본 사용법

```cpp
#include <queue>

priority_queue<int> pq;

pq.push(10);
pq.push(30);
pq.push(20);

cout << pq.top();  // 30

pq.pop();

cout << pq.top();  // 20
```

주요 함수는 다음과 같다.

```cpp
pq.push(value);    // 값 삽입
pq.pop();          // 우선순위가 가장 높은 값 삭제
pq.top();          // 우선순위가 가장 높은 값 확인
pq.empty();        // 비어있는지 확인
pq.size();         // 원소 개수 확인
```

---

## 3. 최대 힙

C++의 `priority_queue`는 기본적으로 최대 힙이다.

```cpp
priority_queue<int> pq;

pq.push(3);
pq.push(1);
pq.push(5);
pq.push(2);
```

꺼내는 순서는 다음과 같다.

```text
5
3
2
1
```

즉 가장 큰 값이 먼저 나온다.

---

## 4. 최소 힙

가장 작은 값을 먼저 꺼내고 싶다면 `greater`를 사용한다.

```cpp
priority_queue<
    int,
    vector<int>,
    greater<int>
> pq;
```

한 줄로 작성하면 다음과 같다.

```cpp
priority_queue<int, vector<int>, greater<int>> pq;
```

예를 들어,

```cpp
pq.push(3);
pq.push(1);
pq.push(5);
pq.push(2);
```

꺼내는 순서는 다음과 같다.

```text
1
2
3
5
```

---

## 5. priority_queue 선언 구조

`priority_queue`의 기본 형태는 다음과 같다.

```cpp
priority_queue<
    자료형,
    데이터를 저장할 컨테이너,
    비교 함수
> pq;
```

예를 들어 최소 힙은 다음과 같다.

```cpp
priority_queue<
    int,
    vector<int>,
    greater<int>
> pq;
```

각 부분의 의미는 다음과 같다.

```text
int
```

저장할 자료형

```text
vector<int>
```

Priority Queue 내부에서 사용할 컨테이너

```text
greater<int>
```

작은 값이 먼저 나오도록 하는 비교 방식

---

## 6. pair 사용하기

`priority_queue`에는 `pair`도 저장할 수 있다.

```cpp
priority_queue<pair<int, int>> pq;
```

기본적으로는 최대 힙이므로 `pair`의 값이 큰 순서대로 나온다.

`pair`는 먼저 `first`를 비교하고,  
`first`가 같으면 `second`를 비교한다.

예를 들어,

```cpp
pq.push({3, 10});
pq.push({5, 20});
pq.push({1, 30});
```

가장 먼저 나오는 값은

```text
{5, 20}
```

이다.

---

## 7. pair 최소 힙

`pair`를 작은 값부터 꺼내고 싶다면 다음과 같이 선언한다.

```cpp
priority_queue<
    pair<int, int>,
    vector<pair<int, int>>,
    greater<pair<int, int>>
> pq;
```

한 줄로 작성하면 다음과 같다.

```cpp
priority_queue<pair<int,int>,
               vector<pair<int,int>>,
               greater<pair<int,int>>> pq;
```

예를 들어,

```cpp
pq.push({10, 3});
pq.push({5, 2});
pq.push({7, 1});
pq.push({3, 4});
```

꺼내는 순서는 다음과 같다.

```text
{3, 4}
{5, 2}
{7, 1}
{10, 3}
```

즉 `first`가 작은 순서대로 나온다.

---

## 8. pair 값 꺼내기

```cpp
pair<int, int> cur = pq.top();

int firstValue = cur.first;
int secondValue = cur.second;

pq.pop();
```

또는 다음처럼 바로 사용할 수도 있다.

```cpp
int firstValue = pq.top().first;
int secondValue = pq.top().second;

pq.pop();
```

---

## 9. 시간복잡도

Priority Queue의 주요 연산 시간복잡도는 다음과 같다.

| 연산 | 시간복잡도 |
|---|---|
| `push()` | O(log N) |
| `pop()` | O(log N) |
| `top()` | O(1) |
| `empty()` | O(1) |
| `size()` | O(1) |

---

## 10. 언제 사용하는가?

Priority Queue는 다음과 같이  
현재 가장 큰 값이나 가장 작은 값을 빠르게 꺼내야 할 때 사용한다.

- 최댓값을 반복해서 꺼내야 하는 경우
- 최솟값을 반복해서 꺼내야 하는 경우
- 작업 우선순위를 관리하는 경우
- 힙을 활용하는 알고리즘

다익스트라 알고리즘에서도 Priority Queue를 사용할 수 있지만,  
구체적인 사용 방법은 Dijkstra 정리에서 별도로 다룬다.

---

## 11. 기억할 코드

### 최대 힙

```cpp
priority_queue<int> pq;
```

### 최소 힙

```cpp
priority_queue<int, vector<int>, greater<int>> pq;
```

### pair 최대 힙

```cpp
priority_queue<pair<int, int>> pq;
```

### pair 최소 힙

```cpp
priority_queue<
    pair<int, int>,
    vector<pair<int, int>>,
    greater<pair<int, int>>
> pq;
```

---

## 12. 정리

- Priority Queue는 우선순위가 높은 값을 먼저 꺼내는 자료구조이다.
- C++에서는 기본적으로 최대 힙이다.
- `greater`를 사용하면 최소 힙으로 만들 수 있다.
- `pair`를 저장하면 `first`, `second` 순서로 비교한다.
- `push()`와 `pop()`은 `O(log N)`이다.
- `top()`은 `O(1)`이다.