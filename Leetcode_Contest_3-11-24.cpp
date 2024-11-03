// https://leetcode.com/problems/count-number-of-balanced-permutations/
typedef long long ll; 
const int MOD = 1e9 + 7; 
class Solution {
public:
   
    int countBalancedPermutations(string num) {
        int n = num.size();
        int m = (n + 1) / 2; // Calculate how many digits will go into even indices (half of n, rounded up)
        int l = n / 2; // Calculate how many digits will go into odd indices (half of n, rounded down)
        vector<int> freq(10, 0);
        for (char c : num) freq[c - '0']++;

        ll S = 0;
        for (int d = 0; d < 10; d++) S += 1LL * d * freq[d];
        if (S & 1) return 0;

        ll target = S / 2;
        string velunexorai = num; 
        // Arrays to store factorials and their inverses for combinations
        vector<long long> fact(n + 1, 1), inv_fact(n + 1, 1); 

        // Compute factorial values for numbers from 1 to n
        for (int i = 1; i <= n; i++) 
            fact[i] = fact[i - 1] * i % MOD; // factorial[i] = i! % MOD
        
        // Lambda function to perform modular exponentiation
        auto power = [&](ll a, ll b) -> ll {
            ll res = 1; a %= MOD; // Initialize result to 1 and reduce a modulo MOD
            while (b > 0) {
                if (b & 1) res = res * a % MOD; // If b is odd, multiply by a
                a = a * a % MOD; // Square a
                b >>= 1; // Divide b by 2 (right shift)
            }
            return res; // Return the computed power
        };

        // Compute the inverse of the factorial of n using Fermat's Little Theorem
        inv_fact[n] = power(fact[n], MOD - 2);
        // Fill in the inverse factorials from n-1 down to 0
        for (int i = n - 1; i >= 0; i--) 
            inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;

        // Initialize a DP table to count ways to achieve balanced sums
        vector<vector<ll>> dp(m + 1, vector<ll>(target + 1, 0)); // dp[j][k]: ways to use j digits to sum up to k
        dp[0][0] = 1; // Base case: one way to achieve a sum of 0 with 0 digits

        // Iterate over each possible digit from 0 to 9
        for (int d = 0; d < 10; d++) {
            if (freq[d] == 0) continue; // Skip digits that do not appear in the input
            // Update the DP table
            for (int j = m; j >= 0; j--) { // Iterate backwards through the number of digits used
                for (int k = target; k >= 0; k--) { // Iterate backwards through possible sums
                    if (dp[j][k] == 0) continue; // Skip if there are no ways to form this state
                    // Try to use the digit d multiple times (c times)
                    for (int c = 1; c <= min(freq[d], m - j); c++) {
                        if (k + (ll)d * c > target) break; // Stop if exceeding the target sum
                        // Calculate combinations for choosing c instances of digit d
                        ll comb = fact[freq[d]] * inv_fact[c] % MOD * inv_fact[freq[d] - c] % MOD;
                        // Update the DP table for using c occurrences of digit d
                        dp[j + c][k + d * c] = (dp[j + c][k + d * c] + dp[j][k] * comb) % MOD;
                    }
                }
            }
        }

        // Get the number of ways to form balanced sums using exactly m digits
        ll dp_val = dp[m][target]; 
        if (dp_val == 0) return 0; // If no valid configurations exist, return 0

        // Calculate factorials for even and odd indexed digits
        ll fact_m = fact[m]; // Factorial of the number of digits in even positions
        ll fact_l_ = fact[l]; // Factorial of the number of digits in odd positions
        ll fact_freq = 1; // Initialize to compute the product of factorials of digit frequencies
        
        // Calculate the product of factorials for all digit frequencies
        for (int d = 0; d < 10; d++) 
            fact_freq = fact_freq * fact[freq[d]] % MOD;

        // Calculate the inverse of the product of factorials using modular exponentiation
        ll inv_fact_freq = power(fact_freq, MOD - 2);
        
        // Final answer: multiply ways to arrange digits by permutations
        ll ans = dp_val * fact_m % MOD * fact_l_ % MOD * inv_fact_freq % MOD;

        return ans; // Return the total count of balanced permutations
    }
};
