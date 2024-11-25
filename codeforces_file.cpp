#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void InsSrt(vector<int> &a, const int l, const int r) {
    for (int i = l + 1; i <= r; ++i) {
        const int k = a[i];
        int j = i - 1;
        while (j >= l && a[j] > k) {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = k;
    }
}

void Hfy(vector<int> &a, const int n, const int i, const int o) {
    int lg = i;
    const int l = 2 * i + 1;
    const int r = 2 * i + 2;
    if (l < n && a[o + l] > a[o + lg]) {
        lg = l;
    }
    if (r < n && a[o + r] > a[o + lg]) {
        lg = r;
    }
    if (lg != i) {
        swap(a[o + i], a[o + lg]);
        Hfy(a, n, lg, o);
    }
}

void Hpsrt(vector<int> &a, const int l, const int r) {
    const int n = r - l + 1;
    for (int i = n / 2 - 1; i >= 0; --i) {
        Hfy(a, n, i, l);
    }
    for (int i = n - 1; i > 0; --i) {
        swap(a[l], a[l + i]);
        Hfy(a, i, 0, l);
    }
}

int Part(vector<int> &a, const int l, const int r) {
    const int p = a[r];
    int i = l - 1;
    for (int j = l; j < r; ++j) {
        if (a[j] <= p) {
            ++i;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[r]);
    return i + 1;
}

void Qksrt(vector<int> &a, int l, const int r, const int d) {
    while (l < r) {
        if (r - l + 1 <= 16) {
            InsSrt(a, l, r);
            break;
        }
        if (d == 0) {
            Hpsrt(a, l, r);
            break;
        }
        const int p = Part(a, l, r);
        Qksrt(a, l, p - 1, d - 1);
        l = p + 1;
    }
}

void IntSrt(vector<int> &a, const int l, const int r) {
    const int d = static_cast<int>(2 * log2(r - l + 1));
    Qksrt(a, l, r, d);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n = 0;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    IntSrt(a, 0, n - 1);
    for (const int &v: a) {
        cout << v << ' ';
    }
    return 0;
}

