// https://leetcode.com/problems/minimum-operations-to-make-character-frequencies-equal/
class Solution {
public:
    int makeStringGood(string s) {
        // Step 1: Initialize an array to count the frequencies of each character in the string
        vector<int> counter(26, 0);  // We have 26 characters ('a' to 'z'), so initialize an array to store counts for each of them.
        
        int n = s.size();  // Get the length of the string s.

        // Step 2: Count the frequency of each character in the string
        for (int i = 0; i < n; i++) {
            counter[s[i] - 'a']++;  // Convert character to an index (e.g., 'a' -> 0, 'b' -> 1, ..., 'z' -> 25) and increment the count.
        }

        int minele = 0, maxele = n;  // Initialize bounds for the target number of characters that need to be adjusted.
        int currmin = INT_MAX;  // Start with a large value to store the minimum result found.

        // Step 3: Try all possible target values for the number of occurrences of each character.
        for (int target = minele; target <= maxele; target++) {
            // Step 4: Initialize dp array. dp[c] will store the minimum cost to make the string good for character c.
            vector<int> dp(26, INT_MAX);  // Initialize the dp array with a large value (infinity).
            
            dp[0] = min(counter[0], abs(target - counter[0]));  // Handle the first character separately.
            
            // Step 5: Iterate through all the characters from 'b' to 'z' and calculate the minimum cost to make the string good.
            for (int c = 1; c < 26; c++) {
                // If the current character doesn't appear in the string, we can carry over the cost from the previous character.
                if (counter[c] == 0) {
                    dp[c] = dp[c - 1];  // If no occurrence of the current character, the cost remains the same as the previous one.
                } else {
                    // Otherwise, calculate the cost for adjusting the current character's frequency to match the target.
                    dp[c] = dp[c - 1] + min(counter[c], abs(target - counter[c]));
                    
                    // Step 6: Special case for adjusting both the current character and the previous one
                    if (c > 0 && counter[c] < target && counter[c - 1]) {
                        // Try to adjust the previous character and the current character simultaneously to minimize cost.
                        int adjust;
                        
                        // If the previous character count is greater than the target, reduce it to the target.
                        if (counter[c - 1] > target) {
                            adjust = min(abs(counter[c - 1] - target), abs(counter[c] - target));
                        } else {
                            // Otherwise, increase the current character to match the target.
                            adjust = min(counter[c - 1], abs(counter[c] - target));
                        }
                        
                        // Adjust the counts of both characters after making the change.
                        int newbefore = counter[c - 1] - adjust;  // Updated frequency of the previous character.
                        int newafter = counter[c] + adjust;  // Updated frequency of the current character.
                        
                        // Calculate the cost of making both of these adjusted frequencies match the target.
                        int b1 = min(newbefore, abs(target - newbefore));
                        int a1 = min(newafter, abs(target - newafter));

                        // Step 7: If we can adjust both characters, minimize the result based on the previous dp value.
                        if (c > 1) {
                            dp[c] = min(dp[c], dp[c - 2] + adjust + b1 + a1);  // Consider previous dp[c-2] to allow multiple character adjustments.
                        } else {
                            dp[c] = min(dp[c], adjust + b1 + a1);  // If we can't go back further, consider only the current dp[c].
                        }
                    }
                }
            }

            // Step 8: After processing all characters, update the minimum result found for the target.
            currmin = min(currmin, dp[25]);  // dp[25] represents the final result considering the 'z' character.
        }

        // Step 9: Return the minimum cost to make the string good
        return currmin;  // Return the smallest cost found after trying all possible targets.
    }
};
