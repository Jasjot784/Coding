// https://leetcode.com/problems/minimum-changes-to-make-k-semi-palindromes/
class Solution {
public:
    int calci(string &s, int start, int len, int d) {
        int cnt = 0;

        for (int i = 0; i < d; i++) {
            int left = start + i;
            int right = start + i + ((len - 1 - i) / d) * d;

            while (left < right) {
                if (s[left] != s[right]) cnt++;

                left += d;
                right -= d;
            }
        }

        return cnt;
    }

    int minimumChanges(string s, int k) {
        int n = s.size();

        // cost[i][j] = minimum changes to make s[i...j]
        // a semi-palindrome.
        vector<vector<int>> cost(n, vector<int>(n, INT_MAX));

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int len = j - i + 1;

                for (int d = 1; d < len; d++) {
                    if (len % d == 0) {
                        cost[i][j] = min(cost[i][j],
                                         calci(s, i, len, d));
                    }
                }
            }
        }

        // dp[i][parts] = minimum changes needed
        // to partition first i characters into parts substrings.
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, INT_MAX));

        dp[0][0] = 0;

        for (int i = 1; i <= n; i++) {
            for (int parts = 1; parts <= k; parts++) {

                for (int j = i - 2; j >= 0; j--) {

                    if (dp[j][parts - 1] == INT_MAX) continue;

                    dp[i][parts] = min(
                        dp[i][parts],
                        dp[j][parts - 1] + cost[j][i - 1]
                    );
                }
            }
        }

        return dp[n][k];
    }
};
