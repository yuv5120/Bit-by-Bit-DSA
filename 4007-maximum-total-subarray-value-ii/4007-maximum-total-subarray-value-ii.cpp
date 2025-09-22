#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct SparseTable {
    int n;
    int LOG;
    vector<int> lg;
    vector<vector<int>> stMin, stMax;

    SparseTable(const vector<int>& a) {
        n = a.size();
        LOG = 32 - __builtin_clz(max(1, n));
        lg.assign(n+1, 0);
        for (int i = 2; i <= n; ++i) lg[i] = lg[i/2] + 1;

        stMin.assign(LOG, vector<int>(n));
        stMax.assign(LOG, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            stMin[0][i] = a[i];
            stMax[0][i] = a[i];
        }
        for (int k = 1; k < LOG; ++k) {
            int len = 1 << k;
            int half = len >> 1;
            for (int i = 0; i + len - 1 < n; ++i) {
                stMin[k][i] = min(stMin[k-1][i], stMin[k-1][i + half]);
                stMax[k][i] = max(stMax[k-1][i], stMax[k-1][i + half]);
            }
        }
    }
    pair<int,int> queryMinMax(int l, int r) {
        int len = r - l + 1;
        int k = lg[len];
        int j = 1 << k;
        int mn = min(stMin[k][l], stMin[k][r - j + 1]);
        int mx = max(stMax[k][l], stMax[k][r - j + 1]);
        return {mn, mx};
    }
};

struct Item {
    ll val;
    int l, r;
    Item(ll v=0,int L=0,int R=0): val(v), l(L), r(R) {}
};
struct Cmp {
    bool operator()(Item const& a, Item const& b) const {
        return a.val < b.val; // max-heap
    }
};
class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        int n = nums.size();
    if (n == 0 || k <= 0) return 0;
    long long total = 1LL * n * (n + 1) / 2;
    if (k > total) k = total;

    SparseTable st(nums);
    priority_queue<Item, vector<Item>, Cmp> pq;
    for (int l = 0; l < n; ++l) {
        auto pr = st.queryMinMax(l, n-1);
        ll val = (ll)pr.second - (ll)pr.first;
        pq.emplace(val, l, n-1);
    }

    ll ans = 0;
    for (long long taken = 0; taken < k && !pq.empty(); ++taken) {
        Item top = pq.top(); pq.pop();
        ans += top.val;
        int l = top.l, r = top.r;
        if (r - 1 >= l) {
            auto pr = st.queryMinMax(l, r-1);
            ll val = (ll)pr.second - (ll)pr.first;
            pq.emplace(val, l, r-1);
        }
    }
    return ans;
    }
};