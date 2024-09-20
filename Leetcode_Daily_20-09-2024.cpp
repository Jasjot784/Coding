// https://leetcode.com/problems/shortest-palindrome/submissions/1396683242/?envType=daily-question&envId=2024-09-20
// length: This variable keeps track of the length of the longest prefix suffix found so far. It starts at 0 because initially, we haven't found any matches.
// lps[i]: This stores the length of the longest proper prefix which is also a suffix for the substring s[0:i].
class Solution {
public:
    // Function to compute the longest prefix which is also a suffix
    vector<int> computeLPSArray(const string& s) {
        int n = s.size();
        vector<int> lps(n, 0);
        int length = 0;
        int i = 1;

        while (i < n) {
            if (s[i] == s[length]) {
                length++;
                lps[i] = length;
                i++;
            } else {
                if (length != 0) {
                    length = lps[length - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
        return lps;
    }

    string shortestPalindrome(string s) {
        string ulta = s;
        reverse(ulta.begin(), ulta.end());
        
        // Create a new string to analyze
        string combined = s + "#" + ulta;
        vector<int> lps = computeLPSArray(combined);

        // The length of the longest palindromic prefix
        int longestPalindromicPrefixLength = lps.back();
        
        // Characters to be added
        string toAdd = ulta.substr(0, s.size() - longestPalindromicPrefixLength);
        
        return toAdd + s;
    }
};

