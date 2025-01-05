// https://leetcode.com/problems/maximum-coins-from-k-consecutive-bags/
class Solution {
public:
    long long maximumCoins(vector<vector<int>>& A, int k) {
        // Step 1: Sort the intervals in increasing order of their starting position.
        sort(A.begin(), A.end());

        int n = A.size(); // Get the number of ranges in the input.

        // Initialize result to keep track of the maximum coins we can collect.
        long long res = 0;
        
        // Variable `cur` will hold the total number of coins we are currently collecting.
        long long cur = 0;

        // Step 2: First loop - Start at `A[i][0]` (first element of the range)
        for (int i = 0, j = 0; i < n; ++i) {
            
            // While the `j`th range ends within the range that starts at `A[i][0] + k - 1`,
            // it is still part of the valid interval. We add the coins of this range to `cur`.
            while (j < n && A[j][1] <= A[i][0] + k - 1) {
                cur += 1L * (A[j][1] - A[j][0] + 1) * A[j][2];
                j++;  // Move to the next range.
            }

            // If `j` is still within bounds, that means the range starting from `A[i][0]`
            // has some overlap with the range `A[j]`. We try to add the coins from that overlap.
            if (j < n) {
                // `part` calculates the coins we can collect from the overlap between `A[i]` and `A[j]`.
                long long part = 1L * max(0, A[i][0] + k - 1 - A[j][0] + 1) * A[j][2];
                
                // We check if this current collection is the maximum we can collect so far.
                res = max(res, cur + part);
            }

            // After processing the `i`th range, we need to subtract it from `cur`
            // because we are moving to the next range.
            cur -= 1L * (A[i][1] - A[i][0] + 1) * A[i][2];
        }

        // Step 3: Second loop - Start at `A[i][1]` (end element of the range)
        cur = 0; // Reset `cur` for this new calculation.

        // Second loop looks for ranges starting from `A[i][1]`.
        for (int i = 0, j = 0; i < n; ++i) {
            // Add coins from the range `A[i]` to `cur`.
            cur += 1L * (A[i][1] - A[i][0] + 1) * A[i][2];

            // While the `j`th range ends before `A[i][1] - k + 1`, it's outside the valid range.
            // We need to remove it from `cur`.
            while (A[j][1] < A[i][1] - k + 1) {
                cur -= 1L * (A[j][1] - A[j][0] + 1) * A[j][2];
                j++;  // Move `j` to the next valid range.
            }

            // `part` calculates the coins we can collect from the valid range `A[j]` that overlaps with `A[i]`.
            long long part = 1L * max(0, A[i][1] - k - A[j][0] + 1) * A[j][2];
            
            // Check if the total coins collected after subtracting the overlap from `cur` is the maximum.
            res = max(res, cur - part);
        }

        return res;  // Return the maximum number of coins that can be collected.
    }
};
