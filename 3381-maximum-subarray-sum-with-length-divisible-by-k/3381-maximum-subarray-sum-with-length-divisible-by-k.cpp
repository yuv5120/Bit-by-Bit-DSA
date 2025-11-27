class Solution {
public:
    long long maxSubarraySum(vector<int>& a, int k) {
        long long m = LLONG_MIN, s = 0;
    unordered_map<int, long long> mp;
    mp[0] = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        s += a[i];
        int mod = (i + 1) % k;
        if (mp.count(mod)) m = max(m, s - mp[mod]);
        if (!mp.count(mod)) mp[mod] = s;
        else mp[mod] = min(mp[mod], s);
    }
    return m == LLONG_MIN ? -1 : m;
    }
};