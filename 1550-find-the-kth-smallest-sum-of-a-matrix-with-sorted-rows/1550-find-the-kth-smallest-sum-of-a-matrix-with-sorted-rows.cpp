class Solution {
public:
vector<int> mergeKSmallest(const vector<int>& A, const vector<int>& B, int k) {
    // result vector to store up to k smallest sums
    vector<int> res;
    // edge cases: if either is empty, return empty
    if (A.empty() || B.empty() || k <= 0) return res;

    // min-heap of tuples (sum, i, j)
    // Using tuple<int,int,int> and greater<> to make it a min-heap by sum (tuple compares lexicographically)
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> pq;

    // We'll push pairs (A[i] + B[0], i, 0) for i in [0 .. min(k-1, A.size()-1)]
    // This seeds the heap with the smallest j for each i.
    int limit = min((int)A.size(), k);
    for (int i = 0; i < limit; ++i) {
        // push initial pair for row i paired with B[0]
        pq.emplace(A[i] + B[0], i, 0);
    }

    // Extract up to k smallest sums
    while (!pq.empty() && (int)res.size() < k) {
        // pop the smallest sum tuple
        auto [sum, i, j] = pq.top();
        pq.pop();

        // add to result
        res.push_back(sum);

        // if there's a next element in B for this i, push the next pair (i, j+1)
        if (j + 1 < (int)B.size()) {
            pq.emplace(A[i] + B[j+1], i, j+1);
        }
    }

    return res;
}
    int kthSmallest(vector<vector<int>>& mat, int k) {
        if (mat.empty() || k <= 0) return 0;

    // Start with the first row as current candidate sums (but cap size to k)
    vector<int> curr = mat[0];
    if ((int)curr.size() > k) curr.resize(k); // keep only first k elements

    // Iteratively merge with next rows
    for (int r = 1; r < (int)mat.size(); ++r) {
        // merge curr and mat[r] producing up to k smallest sums
        curr = mergeKSmallest(curr, mat[r], k);

        // if after merging there are <= k sums, curr already limited
        // else mergeKSmallest already limited it
    }

    // After merging all rows, curr holds the smallest sums sorted.
    // If there are fewer than k possible combinations, return the largest we have (or handle per problem spec)
    if ((int)curr.size() < k) {
        // either invalid k or fewer combinations exist; return last element
        return curr.back();
    }
    // otherwise return the k-th smallest (1-indexed)
    return curr[k-1];
}
};