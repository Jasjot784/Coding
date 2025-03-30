// https://leetcode.com/problems/longest-palindrome-after-substring-concatenation-ii/
class Solution {
private:
    // Function to compute the longest palindrome starting from each index to the left
    vector<int> leftPalindrome(string s) {
        int n = s.length();
        vector<int> ans(n, 0);  // Stores the longest palindromic length starting at each index

        // Odd-length palindromes (centered at i)
        for (int i = 0; i < n; i++) {
            ans[i] = max(ans[i], 1);  // A single character is always a palindrome
            for (int k = 1; i - k >= 0 && i + k < n; k++) {
                if (s[i - k] == s[i + k]) 
                    ans[i - k] = max(ans[i - k], 2 * k + 1);  // Update the leftmost index with palindrome length
                else 
                    break;  // Stop if it’s not a palindrome
            }
        }

        // Even-length palindromes (centered between i-1 and i)
        for (int i = 1; i < n; i++) {
            for (int k = 0; i - k - 1 >= 0 && i + k < n; k++) {
                if (s[i - k - 1] == s[i + k]) 
                    ans[i - k - 1] = max(ans[i - k - 1], 2 * k + 2);  // Update leftmost index
                else 
                    break;  // Stop if it’s not a palindrome
            }
        }
        return ans;  // Return array with max palindrome lengths
    }

    // Function to compute the longest palindrome ending at each index to the right
    vector<int> rightPalindrome(string s) {
        int n = s.length();
        vector<int> ans(n, 0);  // Stores the longest palindromic length ending at each index

        // Odd-length palindromes (centered at i)
        for (int i = 0; i < n; i++) {
            ans[i] = max(ans[i], 1);  // A single character is always a palindrome
            for (int k = 1; i - k >= 0 && i + k < n; k++) {
                if (s[i - k] == s[i + k]) 
                    ans[i + k] = max(ans[i + k], 2 * k + 1);  // Update the rightmost index with palindrome length
                else 
                    break;  // Stop if it’s not a palindrome
            }
        }

        // Even-length palindromes (centered between i-1 and i)
        for (int i = 1; i < n; i++) {
            for (int k = 0; i - k - 1 >= 0 && i + k < n; k++) {
                if (s[i - k - 1] == s[i + k]) 
                    ans[i + k] = max(ans[i + k], 2 * k + 2);  // Update rightmost index
                else 
                    break;  // Stop if it’s not a palindrome
            }
        }
        return ans;  // Return array with max palindrome lengths
    }

public:
    int longestPalindrome(string s, string t) {
        int n = s.length(), m = t.length();

        // Compute the longest palindromic substrings for s (left) and t (right)
        vector<int> lp = leftPalindrome(s);
        vector<int> rp = rightPalindrome(t);

        // DP table to store the longest palindrome when merging substrings of s and t
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // Initialize DP table with longest palindromic lengths for s and t individually
        for (int i = 0; i < n; i++) 
            dp[i][0] = lp[i];  // Consider substring from s alone
        for (int j = 1; j <= m; j++) 
            dp[n][j] = rp[j - 1];  // Consider substring from t alone

        int ans = 0;  // Stores the maximum palindrome length

        // Fill the DP table in a bottom-up manner
        for (int i = n - 1; i >= 0; i--) {  // Iterate through s from end to start
            for (int j = 1; j <= m; j++) {  // Iterate through t from start to end
                dp[i][j] = max(lp[i], rp[j - 1]);  // Start with the max length from either s[i] or t[j-1]
                
                // If characters match, extend the palindrome
                if (s[i] == t[j - 1]) {
                    dp[i][j] = max(dp[i][j], dp[i + 1][j - 1] + 2);  
                }
                
                // Update the answer with the maximum palindrome found
                ans = max(ans, dp[i][j]);
            }
        }

        return ans;  // Return the length of the longest palindrome found
    }
};
