#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main() {
    vector<int> arr = {5, 3, 8, 2, 7};
    int k = 3;

    deque<int> dq;

    for (int i = 0; i < arr.size(); i++) {

        // 슬라이딩 윈도우 범위를 벗어난 인덱스 제거
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }

        // 현재 값보다 큰 값들은 최솟값 후보에서 제거
        while (!dq.empty() && arr[dq.back()] >= arr[i]) {
            dq.pop_back();
        }

        // 현재 인덱스 추가
        dq.push_back(i);

        // 길이 k의 윈도우가 완성됐을 때 최솟값 출력
        if (i >= k - 1) {
            cout << arr[dq.front()] << " ";
        }
    }

    return 0;
}