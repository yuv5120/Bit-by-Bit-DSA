class Solution {
public:
 bool simulate(vector<int> nums, int start, bool goRight) {
        int curr = start;
        while (curr >= 0 && curr < nums.size()) {
            if (nums[curr] == 0) {
                curr += goRight ? 1 : -1;
            } else {
                nums[curr]--;
                goRight = !goRight;
                curr += goRight ? 1 : -1;
            }
        }
        for (int num : nums) {
            if (num != 0) return false;
        }
        return true;
    }
    int countValidSelections(vector<int>& nums) {
        int count = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0) {
                if (simulate(nums, i, true)) count++;
                if (simulate(nums, i, false)) count++;
            }
        }
        return count;
    }
};