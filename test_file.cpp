#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <ctime>
#include <fstream>
#include <iomanip>

using namespace std;

void isr(vector<int>& v, int l, int r) {
    for (int i = l + 1; i <= r; ++i) {
        int k = v[i];
        int j = i - 1;
        while (j >= l && v[j] > k) {
            v[j + 1] = v[j];
            --j;
        }
        v[j + 1] = k;
    }
}

void mrg(vector<int>& v, int l, int m, int r) {
    vector<int> t(r - l + 1);
    int i = l, j = m + 1, k = 0;
    while (i <= m && j <= r) {
        t[k++] = (v[i] <= v[j]) ? v[i++] : v[j++];
    }
    while (i <= m) t[k++] = v[i++];
    while (j <= r) t[k++] = v[j++];
    copy(t.begin(), t.end(), v.begin() + l);
}

void hmsrt(vector<int>& v, int l, int r, int th) {
    if (r - l + 1 <= th) {
        isr(v, l, r);
    } else {
        int m = l + (r - l) / 2;
        hmsrt(v, l, m, th);
        hmsrt(v, m + 1, r, th);
        mrg(v, l, m, r);
    }
}

class Gen {
public:
    explicit Gen(const int mxs = 10000, const int mns = 0, const int mxx = 6000)
        : mxs_(mxs), mns_(mns), mxx_(mxx) {
        std::srand(std::time(nullptr));
        genBase();
    }

    std::vector<int> genRnd(const int sz) {
        chkSz(sz);
        return {r_arr_.begin(), r_arr_.begin() + sz};
    }

    std::vector<int> genRev(const int sz) {
        chkSz(sz);
        std::vector rev_arr(r_arr_.begin(), r_arr_.begin() + sz);
        std::ranges::sort(rev_arr, std::greater<int>());
        return rev_arr;
    }

    std::vector<int> genAlm(const int sz, const int sc = 10) {
        chkSz(sz);
        std::vector alm_arr(r_arr_.begin(), r_arr_.begin() + sz);
        std::ranges::sort(alm_arr);
        doSwaps(alm_arr, sc);
        return alm_arr;
    }

private:
    int mxs_;
    int mns_;
    int mxx_;
    std::vector<int> r_arr_;

    void genBase() {
        r_arr_.resize(mxs_);
        std::mt19937 rng(std::time(nullptr));
        std::uniform_int_distribution<int> dist(mns_, mxx_);
        for (int& num : r_arr_) {
            num = dist(rng);
        }
    }

    void chkSz(const int sz) const {
        if (sz <= 0 || sz > mxs_) {
            throw std::invalid_argument("Invalid size");
        }
    }

    static void doSwaps(std::vector<int>& arr, const int sc) {
        const int n = static_cast<int>(arr.size());
        for (int i = 0; i < sc; ++i) {
            const int idx1 = std::rand() % n;
            const int idx2 = std::rand() % n;
            std::swap(arr[idx1], arr[idx2]);
        }
    }
};

class Tst {
public:
    static double tmsrt(vector<int>& arr) {
        const auto start = std::chrono::high_resolution_clock::now();
        hmsrt(arr, 0, static_cast<int>(arr.size() - 1), 1); 
        const auto elapsed = std::chrono::high_resolution_clock::now() - start;
        return std::chrono::duration<double>(elapsed).count() * 1000.0;
    }

    static double thmsrt(vector<int>& arr, int th) {
        const auto start = std::chrono::high_resolution_clock::now();
        hmsrt(arr, 0, static_cast<int>(arr.size() - 1), th);
        const auto elapsed = std::chrono::high_resolution_clock::now() - start;
        return std::chrono::duration<double>(elapsed).count() * 1000.0;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Gen gen;
    Tst tst;

    std::ofstream r_file("rnd.csv");
    std::ofstream rev_file("rev.csv");
    std::ofstream swap_file("swp.csv");

    r_file << "Test No., Merge Sort (ms), Hybrid Merge Sort (ms)\n";
    rev_file << "Test No., Merge Sort (ms), Hybrid Merge Sort (ms)\n";
    swap_file << "Test No., Merge Sort (ms), Hybrid Merge Sort (ms)\n";

    int th = 15;

    for (int i = 500; i <= 10000; i += 100) {
        auto rnd_arr = gen.genRnd(i);
        auto rev_arr = gen.genRev(i);
        auto swp_arr = gen.genAlm(i, 5);

        double tms_rnd = tst.tmsrt(rnd_arr);
        double tms_rev = tst.tmsrt(rev_arr);
        double tms_swp = tst.tmsrt(swp_arr);

        double thms_rnd = tst.thmsrt(rnd_arr, th);
        double thms_rev = tst.thmsrt(rev_arr, th);
        double thms_swp = tst.thmsrt(swp_arr, th);

        r_file << i << ", " << tms_rnd << ", " << thms_rnd << "\n";
        rev_file << i << ", " << tms_rev << ", " << thms_rev << "\n";
        swap_file << i << ", " << tms_swp << ", " << thms_swp << "\n";
    }

    r_file.close();
    rev_file.close();
    swap_file.close();

    return 0;
}
