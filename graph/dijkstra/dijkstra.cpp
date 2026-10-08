#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;

vector<vector<pair<int, int>>> graph;

// start에서 모든 노드까지의 최단거리 계산
vector<int> dijkstra(int start) {
    vector<int> dist(graph.size(), INF);

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

        // 이미 더 짧은 경로가 발견된 경우
        if (curDist > dist[cur]) {
            continue;
        }

        // 현재 노드와 연결된 모든 노드 확인
        for (int i = 0; i < graph[cur].size(); i++) {
            int nxt = graph[cur][i].first;
            int cost = graph[cur][i].second;

            int nextDist = curDist + cost;

            // 더 짧은 경로 발견
            if (dist[nxt] > nextDist) {
                dist[nxt] = nextDist;
                pq.push({nextDist, nxt});
            }
        }
    }

    return dist;
}

int main() {
    int n = 6;

    graph.resize(n + 1);

    // 양방향 그래프
    graph[1].push_back({2, 2});
    graph[2].push_back({1, 2});

    graph[1].push_back({3, 5});
    graph[3].push_back({1, 5});

    graph[2].push_back({3, 1});
    graph[3].push_back({2, 1});

    graph[2].push_back({4, 2});
    graph[4].push_back({2, 2});

    graph[3].push_back({5, 3});
    graph[5].push_back({3, 3});

    graph[4].push_back({5, 1});
    graph[5].push_back({4, 1});

    graph[5].push_back({6, 2});
    graph[6].push_back({5, 2});

    vector<int> dist = dijkstra(1);

    for (int i = 1; i <= n; i++) {
        cout << "1 -> " << i << " : ";

        if (dist[i] == INF) {
            cout << "INF";
        } else {
            cout << dist[i];
        }

        cout << '\n';
    }

    return 0;
}