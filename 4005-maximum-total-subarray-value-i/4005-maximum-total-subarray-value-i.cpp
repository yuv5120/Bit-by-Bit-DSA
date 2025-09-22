#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        if (nums.empty()) return 0;
        int mn = nums[0], mx = nums[0];
        for (int x : nums) {
            if (x < mn) mn = x;
            if (x > mx) mx = x;
        }
        long long range = (long long)mx - (long long)mn;
        return range * (long long)k;
    }
};
