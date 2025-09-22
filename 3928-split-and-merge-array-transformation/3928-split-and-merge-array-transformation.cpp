#include <bits/stdc++.h>
using namespace std;

static string vecToKey(const vector<int>& v) {
    // join with comma; faster than ostringstream
    string s;
    s.reserve(v.size()*4);
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) s.push_back(',');
        s += to_string(v[i]);
    }
    return s;
}

static vector<int> keyToVec(const string &s) {
    vector<int> out;
    int num = 0; bool inNum = false; bool neg = false;
    for (char c : s) {
        if (c == '-') { neg = true; inNum = true; continue; }
        if (c == ',') {
            if (inNum) {
                out.push_back(neg ? -num : num);
                num = 0; inNum = false; neg = false;
            }
        } else {
            inNum = true;
            num = num*10 + (c - '0');
        }
    }
    if (inNum) out.push_back(neg ? -num : num);
    return out;
}

// Generate all states reachable by one split-and-merge from arr
static vector<string> neighbors(const vector<int>& arr) {
    int n = arr.size();
    vector<string> res;
    // For all L,R (0<=L<=R<n)
    for (int L = 0; L < n; ++L) {
        for (int R = L; R < n; ++R) {
            int len = R - L + 1;
            // Build remaining array (prefix + suffix)
            vector<int> remaining;
            remaining.reserve(n - len);
            for (int i = 0; i < L; ++i) remaining.push_back(arr[i]);
            for (int i = R+1; i < n; ++i) remaining.push_back(arr[i]);

            // We can insert the removed block at any position 0..remaining.size()
            // But inserting at position L (i.e., original spot) is a no-op; avoid it.
            for (int insertPos = 0; insertPos <= (int)remaining.size(); ++insertPos) {
                // No-op detection: original insert position is L (when you remove L..R, putting back before index L in original array)
                // However when R==n-1 or L==0 expressions change; simpler: reconstruct and skip if identical.
                vector<int> newArr;
                newArr.reserve(n);
                // Build new array = remaining[0..insertPos-1] + removed + remaining[insertPos..]
                for (int i = 0; i < insertPos; ++i) newArr.push_back(remaining[i]);
                for (int i = L; i <= R; ++i) newArr.push_back(arr[i]);
                for (int i = insertPos; i < (int)remaining.size(); ++i) newArr.push_back(remaining[i]);

                // Quick no-op check: if newArr equals arr, skip
                bool same = true;
                for (int i = 0; i < n; ++i) if (newArr[i] != arr[i]) { same = false; break; }
                if (same) continue;

                res.push_back(vecToKey(newArr));
            }
        }
    }
    return res;
}

class Solution {
public:
    int minSplitMerge(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
    if (n != (int)nums2.size()) return -1;
    if (nums1 == nums2) return 0;

    // Quick multiset check: if counts differ, impossible
    unordered_map<int,int> cnt;
    for (int x : nums1) cnt[x]++;
    for (int x : nums2) cnt[x]--;
    for (auto &p : cnt) if (p.second != 0) return -1;

    string start = vecToKey(nums1);
    string target = vecToKey(nums2);

    unordered_map<string,int> dist1, dist2;
    queue<string> q1, q2;

    dist1[start] = 0; q1.push(start);
    dist2[target] = 0; q2.push(target);

    // Bidirectional BFS
    while (!q1.empty() && !q2.empty()) {
        // Expand smaller frontier
        if (q1.size() <= q2.size()) {
            int sz = q1.size();
            while (sz--) {
                string curKey = q1.front(); q1.pop();
                int d = dist1[curKey];
                vector<int> cur = keyToVec(curKey);
                auto neigh = neighbors(cur);
                for (auto &nk : neigh) {
                    if (dist1.find(nk) != dist1.end()) continue;
                    dist1[nk] = d + 1;
                    // If other side visited -> meet in middle
                    if (dist2.find(nk) != dist2.end()) {
                        return dist1[nk] + dist2[nk];
                    }
                    q1.push(nk);
                }
            }
        } else {
            int sz = q2.size();
            while (sz--) {
                string curKey = q2.front(); q2.pop();
                int d = dist2[curKey];
                vector<int> cur = keyToVec(curKey);
                auto neigh = neighbors(cur);
                for (auto &nk : neigh) {
                    if (dist2.find(nk) != dist2.end()) continue;
                    dist2[nk] = d + 1;
                    if (dist1.find(nk) != dist1.end()) {
                        return dist1[nk] + dist2[nk];
                    }
                    q2.push(nk);
                }
            }
        }
    }

    return -1;
    }
};
