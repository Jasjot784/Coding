// https://leetcode.com/problems/construct-the-lexicographically-largest-valid-sequence/?envType=daily-question&envId=2025-02-16
class Solution {
public:
    vector<int> constructDistancedSequence(int n) {
        vector<int> seq(2 * n - 1, 0);  // The sequence will have a length of 2n-1
        vector<bool> used(n + 1, false);  // Track if number is used
        if (backtrack(seq, used, n, 0)) {
            return seq;
        }
        return {};  // This will never be reached as a solution is guaranteed
    }

private:
    bool backtrack(vector<int>& seq, vector<bool>& used, int n, int idx) {
        if (idx == seq.size()) {
            return true;  // All positions are filled
        }
        
        if (seq[idx] != 0) {
            return backtrack(seq, used, n, idx + 1);  // Skip filled positions
        }

        for (int i = n; i >= 1; i--) {  // Try placing numbers in descending order
            if (!used[i]) {
                // Try to place number i in the sequence
                if (i == 1) {
                    seq[idx] = i;
                    used[i] = true;
                    if (backtrack(seq, used, n, idx + 1)) {
                        return true;
                    }
                    seq[idx] = 0;  // Backtrack
                    used[i] = false;
                } else {
                    // Try placing i at idx and idx + i
                    if (idx + i < seq.size() && seq[idx + i] == 0) {
                        seq[idx] = seq[idx + i] = i;
                        used[i] = true;
                        if (backtrack(seq, used, n, idx + 1)) {
                            return true;
                        }
                        seq[idx] = seq[idx + i] = 0;  // Backtrack
                        used[i] = false;
                    }
                }
            }
        }
        return false;  // No valid placement found
    }
};
