// https://leetcode.com/problems/shortest-common-supersequence/?envType=daily-question&envId=2025-02-28
class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        int m = str1.length();
        int n = str2.length();

        // Create a 2D dp array
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        // Fill the dp array (LCS computation)
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (str1[i - 1] == str2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        // Reconstruct the Shortest Common Supersequence
        string scs = "";
        int i = m, j = n;

        while (i > 0 && j > 0) {
            // If characters match, include it in the result
            if (str1[i - 1] == str2[j - 1]) {
                scs = str1[i - 1] + scs;  // Add to the front of the result
                i--;
                j--;
            } 
            // Otherwise, add the larger character to the result
            else if (dp[i - 1][j] > dp[i][j - 1]) {
                scs = str1[i - 1] + scs;
                i--;
            } else {
                scs = str2[j - 1] + scs;
                j--;
            }
        }

        // If any characters remain in str1 or str2, add them
        while (i > 0) {
            scs = str1[i - 1] + scs;
            i--;
        }

        while (j > 0) {
            scs = str2[j - 1] + scs;
            j--;
        }

        return scs;
    }
};
