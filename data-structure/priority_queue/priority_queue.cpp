#include <iostream>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

int main() {

    // -------------------------
    // 1. 최대 힙
    // -------------------------

    priority_queue<int> maxHeap;

    maxHeap.push(3);
    maxHeap.push(1);
    maxHeap.push(5);
    maxHeap.push(2);

    cout << "Max Heap: ";

    while (!maxHeap.empty()) {
        cout << maxHeap.top() << " ";
        maxHeap.pop();
    }

    cout << '\n';


    // -------------------------
    // 2. 최소 힙
    // -------------------------

    priority_queue<
        int,
        vector<int>,
        greater<int>
    > minHeap;

    minHeap.push(3);
    minHeap.push(1);
    minHeap.push(5);
    minHeap.push(2);

    cout << "Min Heap: ";

    while (!minHeap.empty()) {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }

    cout << '\n';


    // -------------------------
    // 3. pair 최소 힙
    // -------------------------

    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    // {거리, 노드}
    pq.push({10, 3});
    pq.push({5, 2});
    pq.push({7, 1});
    pq.push({3, 4});

    cout << "Pair Min Heap:" << '\n';

    while (!pq.empty()) {

        int dist = pq.top().first;
        int node = pq.top().second;

        pq.pop();

        cout << "distance: " << dist
             << ", node: " << node << '\n';
    }

    return 0;
}