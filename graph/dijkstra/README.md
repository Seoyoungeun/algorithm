# Dijkstra Algorithm

## 1. 다익스트라란?

다익스트라 알고리즘은 하나의 시작점에서 다른 모든 노드까지의 최단거리를 구하는 알고리즘이다.

단, 간선의 가중치는 음수가 없어야 한다.

---

## 2. 핵심 아이디어

현재까지 발견된 경로 중 가장 거리가 짧은 노드를 먼저 선택한다.

그 노드와 연결된 다른 노드들을 확인하면서 더 짧은 경로가 발견되면 거리를 갱신한다.

---

## 3. 동작 과정

1. 시작 노드의 거리를 0으로 설정한다.
2. 나머지 노드의 거리는 INF로 설정한다.
3. Priority Queue에 시작 노드를 넣는다.
4. 현재 거리가 가장 짧은 노드를 꺼낸다.
5. 현재 노드와 연결된 모든 노드를 확인한다.
6. 더 짧은 경로가 발견되면 거리를 갱신한다.
7. 갱신된 노드를 Priority Queue에 넣는다.
8. Priority Queue가 빌 때까지 반복한다.

---

## 4. 그래프 저장

보통 인접 리스트를 사용한다.

```cpp
vector<vector<pair<int, int>>> graph;
```

각 pair는 다음 의미로 사용할 수 있다.

```text
{다음 노드, 비용}
```

예:

```cpp
graph[1].push_back({2, 5});
```

의 의미는

```text
1 -> 2
비용 = 5
```

이다.

양방향 그래프라면 다음과 같이 저장한다.

```cpp
graph[a].push_back({b, cost});
graph[b].push_back({a, cost});
```

---

## 5. 거리 배열

시작점에서 각 노드까지의 최단거리를 저장한다.

```cpp
vector<int> dist(n + 1, INF);
```

시작점의 거리는 0이다.

```cpp
dist[start] = 0;
```

---

## 6. Priority Queue 사용

다익스트라에서는 현재까지 거리가 가장 짧은 노드를 먼저 꺼내야 한다.

따라서 최소 힙 Priority Queue를 사용한다.

```cpp
priority_queue<
    pair<int, int>,
    vector<pair<int, int>>,
    greater<pair<int, int>>
> pq;
```

보통 다음과 같이 저장한다.

```cpp
pq.push({거리, 노드});
```

예:

```cpp
pq.push({0, start});
```

---

## 7. 거리 갱신

현재 노드를 `cur`,
다음 노드를 `nxt`,
현재 노드까지의 거리를 `curDist`,
간선 비용을 `cost`라고 하자.

새로운 경로의 거리는 다음과 같다.

```cpp
int nextDist = curDist + cost;
```

기존 거리보다 더 짧다면 갱신한다.

```cpp
if (dist[nxt] > nextDist) {
    dist[nxt] = nextDist;
    pq.push({nextDist, nxt});
}
```

이 과정을 Relaxation이라고 한다.

---

## 8. 이미 더 짧은 경로가 존재하는 경우

Priority Queue에는 이전에 넣었던 오래된 거리 정보가 남아 있을 수 있다.

예를 들어 어떤 노드가 처음에는 거리 10으로 들어갔다가,
나중에 거리 5인 더 짧은 경로가 발견될 수 있다.

그러면 Priority Queue 안에는

```text
{5, node}
{10, node}
```

두 정보가 모두 존재할 수 있다.

따라서 다음 코드를 사용한다.

```cpp
if (curDist > dist[cur]) {
    continue;
}
```

현재 Priority Queue에서 꺼낸 거리보다 이미 저장된 최단거리가 더 짧다면
이 정보는 오래된 정보이므로 무시한다.

---

## 9. 기본 코드

```cpp
vector<int> dijkstra(int start) {

    vector<int> dist(N + 1, INF);

    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {

        int curDist = pq.top().first;
        int cur = pq.top().second;

        pq.pop();

        if (curDist > dist[cur]) {
            continue;
        }

        for (int i = 0; i < graph[cur].size(); i++) {

            int nxt = graph[cur][i].first;
            int cost = graph[cur][i].second;

            int nextDist = curDist + cost;

            if (dist[nxt] > nextDist) {
                dist[nxt] = nextDist;
                pq.push({nextDist, nxt});
            }
        }
    }

    return dist;
}
```

---

## 10. 시간복잡도

Priority Queue를 사용하는 다익스트라의 시간복잡도는

```text
O(E log V)
```

이다.

- V: 노드 수
- E: 간선 수

---

## 11. 언제 사용하는가?

다익스트라는 다음과 같은 상황에서 사용한다.

- 그래프의 간선에 비용이 존재하는 경우
- 한 시작점에서 다른 노드까지의 최단거리가 필요한 경우
- 간선 비용이 음수가 아닌 경우

---

## 12. 핵심 정리

- 시작점에서 모든 노드까지의 최단거리를 구한다.
- 최소 힙 Priority Queue를 사용한다.
- 더 짧은 경로를 발견하면 거리 값을 갱신한다.
- 오래된 Priority Queue 정보는 무시한다.
- 시간복잡도는 `O(E log V)`이다.