// https://leetcode.com/problems/count-the-number-of-winning-sequences/
class Solution {
public:
    const int mod = 1e9 + 7; // Define a constant for modulo to avoid overflow

    int countWinningSequences(string s) {
        int n = s.size(); // Get the length of Alice's sequence
        s = " " + s; // Add a space at the start to make the indexing easier (1-based indexing)
        
        // DP table to store the number of sequences
        // dp[i][j][k]: number of sequences for the first i rounds, with score difference j-n (to handle negative indices), and last move k
        int dp[n + 1][2 * n + 1][4]; 
        // Initialize the DP table to zero
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= 2 * n; j++) {
                for (int k = 0; k < 4; k++) {
                    dp[i][j][k] = 0; // Set each entry to 0
                }
            }
        }

        // Base case: At the start (0 rounds played), there's 1 way with score difference of 0 (j = n) and last move k = 0 (not yet played)
        dp[0][n][0] = 1;

        // Iterate through each round
        for (int i = 0; i < n; i++) {
            // Iterate through all possible score differences
            for (int j = n - i; j <= n + i; j++) {
                // Iterate through Bob's last move
                for (int k = 0; k < 4; k++) {
                    // Iterate through all possible moves for Bob (1: F, 2: W, 3: E)
                    for (int l = 1; l < 4; l++) {
                        if (k == l) continue; // Skip if Bob's last move is the same as the current move

                        int sc = j; // Copy the current score difference

                        // Adjust the score difference based on Alice's move and Bob's current move
                        if (s[i + 1] == 'F' && l == 2) sc++; // Alice plays F, Bob plays W (Bob scores)
                        else if (s[i + 1] == 'F' && l == 3) sc--; // Alice plays F, Bob plays E (Alice scores)
                        else if (s[i + 1] == 'W' && l == 3) sc++; // Alice plays W, Bob plays E (Bob scores)
                        else if (s[i + 1] == 'W' && l == 1) sc--; // Alice plays W, Bob plays F (Alice scores)
                        else if (s[i + 1] == 'E' && l == 1) sc++; // Alice plays E, Bob plays F (Bob scores)
                        else if (s[i + 1] == 'E' && l == 2) sc--; // Alice plays E, Bob plays W (Alice scores)

                        // Update the DP table for the next round
                        dp[i + 1][sc][l] += dp[i][j][k]; // Add the number of ways to achieve this configuration
                        dp[i + 1][sc][l] %= mod; // Take modulo to avoid overflow
                    }
                }
            }
        }

        int ans = 0; // Variable to store the final answer
        // Sum up the number of winning sequences where Bob's score is strictly greater than Alice's
        for (int i = n + 1; i <= 2 * n; i++) { // j must be greater than n (Alice's score)
            for (int j = 1; j <= 3; j++) { // Last move can be any of F, W, or E
                ans += dp[n][i][j]; // Add the count of winning sequences
                ans %= mod; // Take modulo
            }
        }

        return ans; // Return the final answer
    }
};
