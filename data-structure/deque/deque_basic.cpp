    // 1 2 3
    for (int x : dq) {
        cout << x << " ";
    }

    cout << '\n';

    cout << "front: " << dq.front() << '\n';
    cout << "back: " << dq.back() << '\n';

    dq.pop_front();
    dq.pop_back();

    // 2
    for (int x : dq) {
        cout << x << " ";
    }

    return 0;
}