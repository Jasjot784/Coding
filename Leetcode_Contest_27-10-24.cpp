// https://leetcode.com/problems/total-characters-in-string-after-transformations-ii/
#include<bits/stdc++.h>
using namespace std;

// Define long long type for large integers
typedef long long ll;
// Define a constant for modulo operations
const int MOD = 1e9 + 7;

// Define a type for a matrix of long long integers
typedef vector<vector<ll>> matrix;

// Function to multiply two matrices A and B
matrix multiply(const matrix &A, const matrix &B) {
    // Create a result matrix C initialized with zeros
    matrix C(26, vector<ll>(26, 0));
    // Iterate over each row of A
    for(int i = 0; i < 26; i++) {
        // Iterate over each column of A (also row of B)
        for(int k = 0; k < 26; k++) {
            // If A[i][k] is zero, skip this element (optimization)
            if(A[i][k] == 0) continue;
            // Iterate over each column of B
            for(int j = 0; j < 26; j++) {
                // Update C[i][j] by adding the product of A[i][k] and B[k][j]
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return C; // Return the resultant matrix C
}

// Function to raise a matrix A to a power 'power'
matrix power_matrix(matrix A, ll power) {
    // Create a result matrix res initialized as the identity matrix
    matrix res(26, vector<ll>(26, 0));
    for(int i = 0; i < 26; i++) res[i][i] = 1;
    // While the power is greater than 0
    while(power > 0) {
        // If the current power is odd, multiply res by A
        if(power & 1) {
            res = multiply(res, A);
        }
        // Square the matrix A for the next iteration
        A = multiply(A, A);
        // Right shift the power by 1 (equivalent to dividing by 2)
        power >>= 1;
    }
    return res; // Return the resulting matrix raised to the desired power
}

class Solution {
public:
    // Function to calculate the length of the resulting string after t transformations
    int lengthAfterTransformations(string s, int t, vector<int>& nums) {
        // Initialize a transformation matrix M of size 26x26 (for each letter)
        matrix M(26, vector<ll>(26, 0));
        
        // Build the transformation matrix based on nums
        for(int c = 0; c < 26; c++) {
            if(nums[c] == 0) continue; // Skip if no transformation for character c
            // For each character c, determine its transformations
            for(int i = 1; i <= nums[c]; i++) {
                // Calculate the new character after transformation
                char new_c = 'a' + (c + i) % 26;
                // Increment the count of transformations in matrix M
                M[c][new_c - 'a'] = (M[c][new_c - 'a'] + 1) % MOD;
            }
        }
        
        // Store the original transformation counts in brivlento (not used further in the code)
        vector<int> brivlento = nums;

        // Raise the transformation matrix M to the power of t
        matrix Mt = power_matrix(M, t);
        
        // Initialize a vector to count occurrences of each character in the string s
        vector<ll> counts(26, 0);
        for(char ch : s) counts[ch - 'a']++; // Count occurrences of each character

        // Initialize a variable to store the total length after transformations
        ll total = 0;
        // For each character in the alphabet
        for(int c = 0; c < 26; c++) {
            if(counts[c] == 0) continue; // Skip if the character does not appear in the string
            ll ft = 0; // Initialize a variable to store the number of transformations for character c
            // Calculate the total transformations for character c
            for(int d = 0; d < 26; d++) {
                ft = (ft + Mt[c][d]) % MOD; // Sum up the transformations from M^t
            }
            // Update the total length after transformations
            total = (total + counts[c] * ft) % MOD;
        }
        return (int)total; // Return the final total length modulo MOD
    }
};
