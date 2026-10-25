//https://leetcode.com/problems/count-frequency-staircase-subarrays-ii/

class Solution {
public:
    int countStaircase(vector<int>& A) {

        int n = A.size();  // Number of elements in the array

        vector<int> ind(n); 
        // ind[i] = occurrence index of A[i] among equal elements.
        // The first occurrence has index 0, the second has index 1, etc.

        unordered_map<int, vector<int>> pos;
        // pos[x] stores all positions where value x occurs.
        // Example: A = [4, 7, 4, 4]
        // pos[4] = [0, 2, 3]
        // pos[7] = [1]

        for (int i = 0; i < n; ++i) {

            ind[i] = pos[A[i]].size();
            // Before inserting i, the vector size tells us
            // which occurrence of A[i] this is.

            pos[A[i]].push_back(i);
            // Store the current index in the positions of A[i].
        }

        int res = 0;  // Total number of valid staircases

        // Try every index as the starting position of a subarray.
        for (int i = 0; i < n; ++i) {

            unordered_set<int> seen;
            // Stores distinct values encountered in A[i...j].
            // The first new value has order 1, the next order 2, etc.

            int L = i;
            // L = earliest possible endpoint satisfying
            // the frequency requirements processed so far.

            int R = n;
            // R = exclusive upper bound on valid endpoints.
            // Valid endpoints must be strictly less than R.

            for (int j = i; j < R; ++j) {

                int a = A[j];  // Current value

                if (seen.count(a)) continue;
                // If a has appeared before in this subarray,
                // its order is already known.
                // Process each distinct value only once.

                seen.insert(a);
                // Record this newly encountered distinct value.

                int k = seen.size();
                // Its order of first appearance is k.
                // It must occur exactly k times in a valid staircase.

                if (ind[j] + k - 1 >= pos[a].size()) {
                    // We need k occurrences of a, counting A[j].
                    // ind[j] is its current occurrence index.
                    // The required kth occurrence would be at
                    // ind[j] + k - 1.
                    // If it doesn't exist, no valid staircase
                    // can satisfy this requirement.
                    break;
                }

                int L2 = pos[a][ind[j] + k - 1];
                // Position of the kth occurrence of a,
                // counting from its first occurrence at j.
                // The subarray must end at or after L2
                // so that it contains all k occurrences.

                int R2 = ind[j] + k < pos[a].size()
                    ? pos[a][ind[j] + k]
                    : n;
                // Position of the next occurrence of a, if it exists.
                // The endpoint must be before R2; otherwise,
                // a would appear more than k times.
                // If no next occurrence exists, use n.

                L = max(L, L2);
                // Every processed value must occur enough times.
                // Therefore, take the strongest lower bound.

                R = min(R, R2);
                // Every processed value must not occur too often.
                // Therefore, take the strongest upper bound.

                if (L > R) {
                    // No endpoint can satisfy all requirements.
                    break;
                }

                int end_idx = i + k * (k + 1) / 2 - 1;
                // A staircase with k distinct values has length:
                // 1 + 2 + ... + k = k*(k+1)/2.
                // Convert that length into the ending index.

                if (L <= end_idx && end_idx < R) {
                    // The required triangular endpoint lies
                    // within the valid endpoint interval.
                    // Therefore, this subarray is a staircase.
                    res++;
                }
            }
        }

        return res;  // Return the total count
    }
};
