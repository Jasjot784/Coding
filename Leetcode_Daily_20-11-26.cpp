// https://leetcode.com/problems/maximize-consecutive-elements-in-an-array-after-modification/
class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        vector<vector<int>> dp(n, vector<int>(2, 1));
        unordered_map<int, int> best;

        int ans = 1;

        for(int i = 0; i < n; i++) {
            int x = nums[i];

            // Don't increase current element: final value = x
            if(best.count(x - 1))
                dp[i][0] = max(dp[i][0], best[x - 1] + 1);

            // Increase current element: final value = x + 1
            if(best.count(x))
                dp[i][1] = max(dp[i][1], best[x] + 1);

            // Update best lengths for both possible final values
            best[x] = max(best[x], dp[i][0]);
            best[x + 1] = max(best[x + 1], dp[i][1]);

            ans = max({ans, dp[i][0], dp[i][1]});
        }

        return ans;
    }
};
