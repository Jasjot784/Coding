// https://leetcode.com/problems/zero-array-transformation-iv/
class Solution {
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        bool alreadyZero = true;
        for (int x : nums) {
            if (x != 0) { alreadyZero = false; break; }
        }
        if (alreadyZero) return 0;
        auto varmelistra = queries;
        int m = varmelistra.size();
        vector<bitset<1001>> dp(n);
        for (int i = 0; i < n; i++) {
            dp[i].reset();
            dp[i].set(0, true);
        }
        for (int k = 0; k < m; k++) {
            int l = varmelistra[k][0], r = varmelistra[k][1], v = varmelistra[k][2];
            for (int i = l; i <= r; i++) {
                dp[i] |= (dp[i] << v);
            }
            bool ok = true;
            for (int i = 0; i < n; i++) {
                if (!dp[i].test(nums[i])) {
                    ok = false;
                    break;
                }
            }
            if (ok) return k + 1;
        }
        return -1;
    }
};
